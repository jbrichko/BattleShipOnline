#include <iostream>
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif  


#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


/*! \class Network
*   \brief Jest to klasa macierzysta odpowiadaj¹ca za obs³ugê modu³u sieciowego gry.
*/
class Network
{
public:

    /**
    *   Klasa posiada metody, struktury i enumerator s³u¿¹cê do prawid³owego przebiegu gry przez sieæ.
    *   
    *   Modu³ sieciowy gry statki wykorzystuje bibliotekê ASIO do multiplatformowej obs³ugi operacji sieciowych.
    *   ASIO (Asynchronous Input/Output) to potê¿na biblioteka C++, która umo¿liwia asynchroniczn¹ obs³ugê
    *   operacji wejœcia/wyjœcia, co jest kluczowe dla wydajnej komunikacji sieciowej w grze.
    */

    const static uint32_t DEFAULT_HOST_PORT = { 62137 };

    asio::io_context context;

    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::socket socket;



    Network() : socket(context) {}

    /**
    *	\brief Sprawdza status po³¹czenia.
    *	\return Zwraca informacjê czy zosta³o zawarte po³¹czenie.
    */
    bool isConnected();
    /**
    *	\brief Wysy³a informacje do innego gracza.
    *	\return Zwraca inforamcjê czy informacja zosta³a wys³ana.
    */
    bool send(Message::Header& header, std::vector<uint8_t>& message);
    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcjê czy informacja zosta³a odebrana.
     */
    bool recive(Message::Header& header, std::vector<uint8_t>& message);
    /**
     *	\brief Zamyka po³¹czenie pomiêdzy graczami.
     */
    void disconnect(); 

};

/*! \class NetworkHost
*   \brief Jest to klasa pochodna od klasy Network. Ob³uguje hosta po³¹czenia.
*/
class NetworkHost : public Network
{
public:

    asio::ip::tcp::acceptor acceptor;

    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcjê czy informacja zosta³a odebrana.
     */
    std::string getLocalIP();

    bool waitForConnection(uint16_t port = DEFAULT_HOST_PORT);

    NetworkHost();

};

class NetworkGuest : public Network
{
public:

    bool connect(const std::string hostIP, uint16_t hostPort = DEFAULT_HOST_PORT);

};

class Message
{
public: 
    /**
    *	\enum Type
    *	Enumerator opisuj¹cy dane jakie mog¹ zostaæ wys³ane pomiêdzy graczami.
    *   Typem danych jest unsigned integer 16-bit.
    */
    enum Type : uint16_t
    {
        empty, 
        /// string - dla testów i komunikacji miêdzy graczami (to do)
        string,
        /// game_start - informacja o rozpoczêciu gry
        game_start,
        /// shot - informacja o strzale gracza
        shot,
        /// shot_response - informacja o efekcie strza³u (pud³o lub trafienie)
        shot_response,
    };

    /*!
    *   \struct Header
    *   \brief Header wysy³anej lub odbieranej informacji.
    */
    struct Header
    {
        /// Typ informacji.
        Type type = empty;
        /// Rozmiar informacji.
        uint16_t payloadSize = 0;
    };

    virtual struct Payload {};

    struct StringPayload : Payload
    {
        std::string string; 
    };

    /*!
    *   \struct ShotPayload
    *   \brief Struktura posiadaj¹ca wszelkie dane by wys³aæ lub odczytaæ informacje o strzale.
    */
    struct ShotPayload : Payload
    {
        /// Wspó³rzêdna X strza³u.
        uint8_t x;
        /// Wspó³rzêdna Y strza³u.
        uint8_t y;
    };

    Header header; 
    Payload* payload = nullptr; 

    void setType(Type type); 
    Type getType(); 
    Header getHeader();
    void setPayload(std::vector<uint8_t>& payload);
    std::vector<uint8_t> getPayload();

};