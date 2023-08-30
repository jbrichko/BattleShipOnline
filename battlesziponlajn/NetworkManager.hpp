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

    bool isConnected();
    bool send(MessageHeader& header, std::vector<uint8_t>& message); 
    bool recive(MessageHeader& header, std::vector<uint8_t>& message);
    void disconnect(); 

};

class NetworkHost : public Network
{
public:

    asio::ip::tcp::acceptor acceptor;

    std::string getLocalIP();

    bool waitForConnection(uint16_t port = DEFAULT_HOST_PORT);

    NetworkHost();

};

class NetworkGuest : public Network
{
public:

    bool connect(const std::string hostIP, uint16_t hostPort = DEFAULT_HOST_PORT);

};