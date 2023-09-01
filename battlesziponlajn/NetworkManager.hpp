#include <iostream>
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif  


#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


/*! \class Network
*   \brief Jest to klasa macierzysta odpowiadaj�ca za obs�ug� modu�u sieciowego gry.
*/
class Network
{
public:

    /**
    *   Klasa posiada metody, struktury i enumerator s�u��c� do prawid�owego przebiegu gry przez sie�.
    *   
    *   Modu� sieciowy gry statki wykorzystuje bibliotek� ASIO do multiplatformowej obs�ugi operacji sieciowych.
    *   ASIO (Asynchronous Input/Output) to pot�na biblioteka C++, kt�ra umo�liwia asynchroniczn� obs�ug�
    *   operacji wej�cia/wyj�cia, co jest kluczowe dla wydajnej komunikacji sieciowej w grze.
    */

    const static uint32_t DEFAULT_HOST_PORT = { 62137 };

    asio::io_context context;

    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::socket socket;


    /**
    *	\enum MessageType
    *	Enumerator opisuj�cy dane jakie mog� zosta� wys�ane pomi�dzy graczami.
    *   Typem danych jest unsigned integer 16-bit. 
    */
    enum MessageType : uint16_t
    {
        /// string - dla test�w i komunikacji mi�dzy graczami (to do)
        string,
        /// game_start - informacja o rozpocz�ciu gry
        game_start,
        /// shot - informacja o strzale gracza
        shot,
        /// shot_response - informacja o efekcie strza�u (pud�o lub trafienie)
        shot_response,
    };

    /*!
    *   \struct MessageHeader
    *   \brief Header wysy�anej lub odbieranej informacji.
    */
    struct MessageHeader
    {
        /// Typ informacji.
        MessageType type;
        /// Rozmiar informacji.
        uint16_t payloadSize;
    };

    /*!
    *   \struct ShotMessage
    *   \brief Struktura posiadaj�ca wszelkie dane by wys�a� lub odczyta� informacje o strzale.
    */
    struct ShotMessage
    {
        /// Header strza�u.
        MessageHeader header = { shot, sizeof(ShotMessage) };
        /// Wsp�rz�dna X strza�u.
        uint8_t x;
        /// Wsp�rz�dna Y strza�u.
        uint8_t y;
    };

    Network() : socket(context) {}

    /**
    *	\brief Sprawdza status po��czenia.
    *	\return Zwraca informacj� czy zosta�o zawarte po��czenie.
    */
    bool isConnected();
    /**
    *	\brief Wysy�a informacje do innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a wys�ana.
    */
    bool send(MessageHeader& header, std::vector<uint8_t>& message);
    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a odebrana.
     */
    bool recive(MessageHeader& header, std::vector<uint8_t>& message);
    /**
     *	\brief Zamyka po��czenie pomi�dzy graczami.
     */
    void disconnect(); 

};

/*! \class NetworkHost
*   \brief Jest to klasa pochodna od klasy Network. Ob�uguje hosta po��czenia.
*/
class NetworkHost : public Network
{
public:

    asio::ip::tcp::acceptor acceptor;

    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a odebrana.
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