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
private: 

    struct Payload {};

    /*!
  *   \struct StringPayload
  *   \brief Struktura posiadaj�ca wszelkie dane by wys�a� lub odczyta� informacje tekstowe.
  */
    struct StringPayload : Payload
    {
        /// Przetwarzany tekst.
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

    /*!
    *   \struct ResponsePayload
    *   \brief Struktura posiadaj�ca wszelkie dane by wys�a� lub odczyta� informacje o skutku strzału.
    */
    struct ResponsePayload : Payload
    {
        /// Aktualny status danego pola planszy.
        Board::FieldStatus status;
        /// Współrzędna X pola planszy.
        std::vector<uint8_t> cordsX;
        /// Współrzędna Y pola planszy.
        std::vector<uint8_t> cordsY;
    };

public: 
    /**
    *	\enum Type
    *	Enumerator opisuj�cy dane jakie mog� zosta� wys�ane pomi�dzy graczami.
    *   Typem danych jest unsigned integer 16-bit.
    */
    enum Type : uint16_t
    {
        /// empty - pusta informacja, nic
        empty, 
        /// string - tekst
        string,
        /// game_start - informacja o rozpocz�ciu gry
        game_start,
        /// shot - informacja o strzale gracza
        shot,
        /// shot_response - informacja o efekcie strza�u (pud�o lub trafienie)
        response,
        /// end_game - informacja o końcu gry
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

    /**
    *   \brief Wysyłanie pustej wiadomości.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool sendEmpty(Network* netObject);
    /**
    *   \brief Wysyłanie wiadomości tekstowej.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    *   \param string Wysyłany tekst.
    */
    static bool sendString(Network *netObject, std::string& string);
    /**
    *   \brief Wysyłanie informacji o rozpoczęciu gry.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool sendGameStart(Network* netObject);
    /**
    *   \brief Wysyłanie współrzędnych strzału.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    *   \param x Współrzędna X.
    *   \param y Współrzędna Y.
    */
    static bool sendShot(Network *netObject, uint8_t x, uint8_t y);
    /**
    *   \brief Wysyłanie odpowiedzi po strzale.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    *   \param status Aktualny stan danego pola planszy.
    *   \param cordsX Współrzędna X pola planszy.
    *   \param cordsY Współrzędna Y pola planszy.
    */
    static bool sendResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY); 
    /**
    *   \brief Wysyłanie informacji o zakończeniu gry.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool sendEndGame(Network* netObject);


    /**
    *   \brief Otrzymanie pustej wiadomości.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool reciveEmpty(Network* netObject);
    /**
    *   \brief Otrzymanie wiadomości tekstowej.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    *   \param string Otrzymany tekst.
    */
    static bool reciveString(Network* netObject, std::string& string);
    /**
    *   \brief Otrzymanie informacji o rozpoczęciu gry.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool reciveGameStart(Network* netObject);
    /**
   *   \brief Otrzymanie współrzędnych strzału.
   *   \param netObject Wskaźnik do obiektu klasy Network.
   *   \param x Współrzędna X.
   *   \param y Współrzędna Y.
   */
    static bool reciveShot(Network* netObject, uint8_t& x, uint8_t& y);
    /**
   *   \brief Otrzymanie odpowiedzi po strzale.
   *   \param netObject Wskaźnik do obiektu klasy Network.
   *   \param status Aktualny stan danego pola planszy.
   *   \param cordsX Współrzędna X pola planszy.
   *   \param cordsY Współrzędna Y pola planszy.
   */
    static bool reciveResponse(Network* netObject, Board::FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);
    /**
    *   \brief Otrzymanie informacji o zakończeniu gry.
    *   \param netObject Wskaźnik do obiektu klasy Network.
    */
    static bool reciveEndGame(Network* netObject);
}; 


/*! \class Network
*   \brief Jest to klasa macierzysta odpowiadaj�ca za obs�ug� modu�u sieciowego gry.
*/
class Network
{
    /**
    *   Klasa posiada metody, struktury i enumerator s�u��c� do prawid�owego przebiegu gry przez sie�.
    *
    *   Modu� sieciowy gry statki wykorzystuje bibliotek� ASIO do multiplatformowej obs�ugi operacji sieciowych.
    *   ASIO (Asynchronous Input/Output) to pot�na biblioteka C++, kt�ra umo�liwia asynchroniczn� obs�ug�
    *   operacji wej�cia/wyj�cia, co jest kluczowe dla wydajnej komunikacji sieciowej w grze.
    */
protected:
    asio::io_context context;

    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::socket socket;

    /// Domyślny port służący do bycia hostem.
    static const uint32_t DEFAULT_HOST_PORT = { 62137 };
    /// Domyślny adres IP dla hosta.
    static constexpr const char* DEFAULT_HOST_IP = "127.0.0.1";

public:
    /**
    *	\enum NetRole
    *	Enumerator słuzący do określenia statusu gracza. Czy jest hostem czy guestem rozgrywki.
    */
    enum NetRole : char
    {
        host = 'h',
        guest = 'g',
    };

    Network() : socket(context) {}

    static uint32_t getDefaultPort();
    static const char* getDefaultIP();

    /**
    *	\brief Sprawdza poprawność podanego adresu IP
    *   \param ip Sprawdzany adres IP.
    *	\return Zwraca true jeśli adres jest prawidłowy.
    */
    static bool isValidIP(std::string ip);
    /**
    *	\brief Sprawdza status po��czenia.
    *	\return Zwraca informacj� czy zosta�o zawarte po��czenie.
    */
    bool isConnected();
    /**
 *	\brief Wysy�a informacje do innego gracza.
 *	\return Zwraca inforamcj� czy informacja zosta�a wys�ana.
 */
    bool send(Message::Header& header);
    bool send(Message::Header& header, std::vector<uint8_t>& message);
    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a odebrana.
     */
    bool recive(Message::Header& header);
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
private:
    asio::ip::tcp::acceptor acceptor;

public:
    
    /**
    *	\brief Domyślny konstruktor.
    */
    NetworkHost();

    /**
    *	\brief Odbiera informacje od innego gracza.
    *	\return Zwraca inforamcj� czy informacja zosta�a odebrana.
    */
    std::string getLocalIP();

    /**
    *	\brief Czeka na uzyskanie połączenia.
    *	\return Zwraca inforamcj� czy zostało nawiązane połączenie.
    */
    bool waitForConnection(uint16_t port = DEFAULT_HOST_PORT);
};

class NetworkGuest : public Network
{
public:

    /**
    *	\brief Nawiązuje połącznie z hostem.
    *	\return Zwraca inforamcj� czy zostało nawiązane połączenie.
    */
    bool connect(const std::string hostIP = DEFAULT_HOST_IP, uint16_t hostPort = DEFAULT_HOST_PORT);
};

