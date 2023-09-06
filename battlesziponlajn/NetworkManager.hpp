#pragma once

#include <iostream>
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif  


#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "Board.hpp"

// forward declaration of Network class to solve circular dependencies
class Network; 

class Message
{
public: 
    /**
    *	\enum Type
    *	Enumerator opisuj�cy dane jakie mog� zosta� wys�ane pomi�dzy graczami.
    *   Typem danych jest unsigned integer 16-bit.
    */
    enum Type : uint16_t
    {
        empty, 
        /// string - dla test�w i komunikacji mi�dzy graczami (to do)
        string,
        /// game_start - informacja o rozpocz�ciu gry
        game_start,
        /// shot - informacja o strzale gracza
        shot,
        /// shot_response - informacja o efekcie strza�u (pud�o lub trafienie)
        response,
        end_game,
    };

    /*!
    *   \struct Header
    *   \brief Header wysy�anej lub odbieranej informacji.
    */
    struct Header
    {
        /// Typ informacji.
        Type type = empty;
        /// Rozmiar informacji.
        uint16_t payloadSize = 0;
    };

    struct Payload {};

    struct StringPayload : Payload
    {
        std::string string; 
    };

    /*!
    *   \struct ShotPayload
    *   \brief Struktura posiadaj�ca wszelkie dane by wys�a� lub odczyta� informacje o strzale.
    */
    struct ShotPayload : Payload
    {
        /// Wsp�rz�dna X strza�u.
        uint8_t x;
        /// Wsp�rz�dna Y strza�u.
        uint8_t y;
    };

    struct ResponsePayload : Payload
    {
        Board::FieldStatus status; 
        std::vector<uint8_t> cordsX;
        std::vector<uint8_t> cordsY; 
    };


    static bool sendEmpty(Network* netObject);
    static bool sendString(Network *netObject, std::string& string);
    static bool sendGameStart(Network* netObject);
    static bool sendShot(Network *netObject, uint8_t x, uint8_t y);  
    static bool sendResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY); 
    static bool sendEndGame(Network* netObject);

    static bool reciveEmpty(Network* netObject);
    static bool reciveString(Network* netObject, std::string& string);
    static bool reciveGameStart(Network* netObject);
    static bool reciveShot(Network* netObject, uint8_t x, uint8_t y);
    static bool reciveResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);
    static bool reciveEndGame(Network* netObject);

#ifdef MESSSAGE_TEST_IMPLEMENTATION


    Header header; 
    Payload* payload = nullptr; 

    void setType(Type type); 
    Type getType(); 
    Header getHeader();
    void setPayload(std::vector<uint8_t>& payload);
    std::vector<uint8_t> getPayload();
    Payload* getStruct(); 

    ~Message(); 

#endif

}; 


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
    bool send(Message::Header& header, std::vector<uint8_t>& message);
    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a odebrana.
     */
    bool recive(Message::Header& header, std::vector<uint8_t>& message);
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

