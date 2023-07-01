#include <iostream>
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif  


#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>



class Network
{
public:

    const static uint32_t DEFAULT_HOST_PORT = { 62137 };

    asio::io_context context;

    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::socket socket;

    enum MessageType : uint16_t
    {
        string, //for testing
        game_start,
        shot,
        shot_response,
    };

    struct MessageHeader
    {
        MessageType type;
        uint16_t payloadSize;
    };

    struct ShotMessage
    {
        MessageHeader header = { shot, sizeof(ShotMessage) };
        uint8_t x;
        uint8_t y;
    };

    Network() : socket(context) {}

    bool isConnected()
    {
        return socket.is_open();
    }

    bool send(MessageHeader& header, std::vector<uint8_t>& message)
    {
        try
        {
            asio::write(socket, asio::buffer(&header, sizeof(MessageHeader)));
            asio::write(socket, asio::buffer(message));
        }
        catch (const std::exception& exception)
        {
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }

    bool recive(MessageHeader& header, std::vector<uint8_t>& message)
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
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }

    void disconnect()
    {
        try
        {
            socket.close();
        }
        catch (const std::exception& exception)
        {
            std::cout << "Exception: " << exception.what() << std::endl;
        }
    }

};

class NetworkHost : public Network
{
public:

    asio::ip::tcp::acceptor acceptor;

    std::string getLocalIP();

    bool waitForConnection(uint16_t port = DEFAULT_HOST_PORT) {

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
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }

    NetworkHost() : acceptor(context, asio::ip::tcp::v4())
    {
        acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    }

};

class NetworkGuest : public Network
{
public:
    bool connect(const std::string hostIP, uint16_t hostPort = DEFAULT_HOST_PORT)
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
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }
};