#include "NetworkManager.hpp"

bool Network::isConnected()
{
    return socket.is_open();
}

bool Network::send(Message::Header& header, std::vector<uint8_t>& message)
{
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(Message::Header)));
        asio::write(socket, asio::buffer(message));
    }
    catch (const asio::system_error& error)
    {
        if (error.code() == asio::error::broken_pipe)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        else
        {
            std::cerr << "Exception: " << error.what() << std::endl;
        }

        return false;
    }

    return true;
}

bool Network::recive(Message::Header& header, std::vector<uint8_t>& message)
{
    try
    {
        asio::read(socket, asio::buffer(&header, sizeof(Message::Header)));

        message.resize(header.payloadSize);
        socket.wait(socket.wait_read);

        asio::read(socket, asio::buffer(message.data(), message.size()));
    }
    catch (const asio::system_error& error)
    {
        if (error.code() == asio::error::eof)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        else
        {
            std::cerr << "Exception: " << error.what() << std::endl;
        }

        return false;
    }

    return true;
}

void Network::disconnect()
{
    try
    {
        socket.close();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}

std::string NetworkHost::getLocalIP()
{
    std::string localIP; 

    try
    {
        std::string hostName = asio::ip::host_name();
        asio::ip::tcp::resolver resolver(context);
        asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(), hostName, "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
        asio::ip::tcp::endpoint ipAddr = *endpoints; 

        localIP = ipAddr.address().to_string();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return std::string();
    }

    return localIP; 
}

bool NetworkHost::waitForConnection(uint16_t port)
{

    try
    {
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);

        acceptor.bind(endpoint);
        acceptor.listen();

        std::cout << "Waiting for connection on port " << port << std::endl;

        socket = asio::ip::tcp::socket(context);

        asio::steady_timer timer(context);
        timer.expires_from_now(std::chrono::minutes(7));

        bool timerExpired = false;

        timer.async_wait([&](const asio::error_code& error)
        {
            if (!error)
            {
                std::cerr << "Waiting time exceeded." << std::endl;
                timerExpired = true;
                acceptor.cancel();
            }
         });

        context.run();

        if (timerExpired)
        {
            return false;
        }

        acceptor.accept(socket);
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}

NetworkHost::NetworkHost() : acceptor(context, asio::ip::tcp::v4())
{
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
}

bool NetworkGuest::connect(const std::string hostIP, uint16_t hostPort)
{
    try
    {
        endpoint = asio::ip::tcp::endpoint(asio::ip::make_address_v4(hostIP), hostPort);

        socket.connect(endpoint);

#ifdef DEBUG
        std::cout << "Local port: " << socket.local_endpoint().port() << std::endl;
#endif

    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}


void Message::setType(Type type)
{
    header.type = type; 
}

Message::Type Message::getType()
{
    return header.type; 
}

Message::Header Message::getHeader()
{
    return header; 
}

void Message::setPayload(std::vector<uint8_t>& payload)
{

}

std::vector<uint8_t> Message::getPayload()
{
    if (payload == nullptr)
    {
        return std::vector<uint8_t>(); 
    }

    if (header.type == string)
    {
        return std::vector<uint8_t>(reinterpret_cast<StringPayload*>(payload)->string.begin(), reinterpret_cast<StringPayload*>(payload)->string.end());
    }

    return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(payload), reinterpret_cast<uint8_t*>(payload) + header.payloadSize);
}