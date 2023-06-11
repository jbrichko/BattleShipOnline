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
        game_start,
        shot,
        shot_response,
    };

    struct MessageHeader
    {
        MessageType type;
        uint16_t size;
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

    template <typename T>
    bool send(T& message)
    {
        try
        {
            asio::write(socket, asio::buffer(message, sizeof(T)));
        }
        catch (const std::exception& exception)
        {
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }

    template <typename T>
    T recive()
    {
        T message;
        std::vector<uint8_t> buffer(sizeof(MessageHeader));

        try
        {
            std::cout << "bytes recieved: " << asio::read(socket, asio::buffer(buffer, sizeof(MessageHeader)) << std::endl;

            buffer

                std::cout << "bytes recieved: " << asio::read(socket, asio::buffer(buffer, )) << std::endl;
        }
        catch (const std::exception& exception)
        {
            std::cout << "Exception: " << exception.what() << std::endl;

            return nullptr;
        }

        return message;
    }

    std::string receiveString()
    {
        std::string receivedString;

        try {
            // Receive the size of the string
            std::size_t size;
            std::cout << "bytes recieved: " << asio::read(socket, asio::buffer(&size, sizeof(std::size_t))) << std::endl;

            // Create a buffer to hold the string data
            std::vector<char> buffer(size);

            // Receive the string data
            std::cout << "bytes recieved: " << asio::read(socket, asio::buffer(buffer)) << std::endl;

            // Create a string from the received data
            receivedString = std::string(buffer.begin(), buffer.end());
        }
        catch (const std::exception& ex) {
            std::cout << "Exception while receiving string: " << ex.what() << std::endl;
        }

        return receivedString;
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
        }
        catch (const std::exception& exception)
        {
            std::cout << "Exception: " << exception.what() << std::endl;

            return false;
        }

        return true;
    }
};