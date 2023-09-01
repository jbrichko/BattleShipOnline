#include "NetworkManager.hpp"

bool Network::isConnected()
{
    return socket.is_open();
}

bool Network::send(MessageHeader& header, std::vector<uint8_t>& message)
{
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(MessageHeader)));
        asio::write(socket, asio::buffer(message));
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}

bool Network::recive(MessageHeader& header, std::vector<uint8_t>& message)
{
    try
    {
        asio::read(socket, asio::buffer(&header, sizeof(MessageHeader)));

        message.resize(header.payloadSize);
        socket.wait(socket.wait_read);

        asio::read(socket, asio::buffer(message.data(), message.size()));
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

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
    try
    {
        std::string host_name = asio::ip::host_name();
        std::cout << "Host name: " << host_name << std::endl;

        asio::ip::tcp::resolver resolver(context);
        asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(), host_name, "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

        std::vector<asio::ip::tcp::endpoint> ip_addresses;
        for (asio::ip::tcp::resolver::iterator it = endpoints; it != asio::ip::tcp::resolver::iterator(); ++it) {
            ip_addresses.push_back(*it);
        }

        for (const asio::ip::tcp::endpoint& endpoint : ip_addresses) {
            std::cout << "IP Address: " << endpoint.address().to_string() << std::endl;
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return nullptr;
    }

    return nullptr; 
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
