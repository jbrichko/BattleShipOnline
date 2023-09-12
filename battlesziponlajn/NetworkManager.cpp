#include "NetworkManager.hpp"

bool Message::sendEmpty(Network* netObject)
{
    /// Tworzenie headera wiadomo�ci.
    Header header;
    /// Wybranie typu headera - empty.
    header.type = Message::empty;
    /// Okre�lenie rozmiaru headera - 0.
    header.payloadSize = 0;

    /// Wys�anie pustej wiadomo�ci.
    return netObject->send(header);
}

bool Message::sendString(Network* netObject, std::string& string)
{
    /// Tworzenie headera wiadomo�ci.
    Header header;
    /// Wybranie typu headera - string.
    header.type = Message::string;
    /// Zamiana stringa na wektor.
    std::vector<uint8_t> payload(string.begin(), string.end());
    /// Okre�lenie rozmiaru nowego wektora przechowuj�cego wiadomo��.
    header.payloadSize = payload.size();

    /// Wys�anie wiadomo�ci "string".
    return netObject->send(header, payload);
}

bool Message::sendGameStart(Network* netObject)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - game_start
    header.type = Message::game_start;
    /// Okre�lenie rozmiaru headera - 0. 
    header.payloadSize = 0;

    /// Wys�anie informacji - game_start.
    return netObject->send(header);
}

bool Message::sendShot(Network* netObject, uint8_t x, uint8_t y)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - shot.
    header.type = Message::shot;
    /// Okre�lenie rozmiaru headera - zgodnie z rozmiarem struktruty ShotPayload.
    header.payloadSize = sizeof(ShotPayload);

    /// Inicjacja struktuty ShotPayload.
    ShotPayload payloadStruct;
    /// Przypisanie warto�ci wsp�rz�dnej X do struktury.
    payloadStruct.x = x;
    /// Przypisanie warto�ci wsp�rz�dnej Y do struktury.
    payloadStruct.y = y;

    /// Tworzenie wektora o okre�lonym rozmiarze.
    std::vector<uint8_t> payload(header.payloadSize);
    /// Kopiowanie informacji ze struktury do wektora.
    std::copy(reinterpret_cast<uint8_t*>(&payloadStruct), reinterpret_cast<uint8_t*>(&payloadStruct) + header.payloadSize, payload.begin());

    /// Wysy�anie wsp�rz�dnych strza�u.
    return netObject->send(header, payload);
}

bool Message::sendResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - response.
    header.type = Message::response;

    /// Okre�lenie rozmiaru headera - informacja o statusie pola planszy + wsp�rz�dne tego pola.
    header.payloadSize = sizeof(Board::FieldStatus) + cordsX.size() + cordsY.size();
    /// Tworzenie wektora o okre�lonym rozmiarze.
    std::vector<uint8_t> payload(header.payloadSize);
    /// Tworzenie iteratora "it" dla wektora i ustawienie go na jego pocz�tku.
    std::vector<uint8_t>::iterator it = payload.begin();

    /// Kopiowanie do wektora inforamcji o statusie pola planszy.
    std::copy(reinterpret_cast<uint8_t*>(&status), reinterpret_cast<uint8_t*>(&status) + sizeof(Board::FieldStatus), it);

    /// Kopiowanie do wektora wsp�rz�dnych pola planszy.
    if (cordsX.size() == cordsY.size() && cordsX.size() > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(cordsX.begin(), cordsX.end(), it);
        it += cordsX.size();
        std::copy(cordsY.begin(), cordsY.end(), it);
    }

    /// Wys�anie odpowiedzi.
    return netObject->send(header, payload);
}

bool Message::sendEndGame(Network* netObject)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - end_game.
    header.type = Message::end_game;
    /// Okre�lenie rozmiaru headera - 0.
    header.payloadSize = 0;

    /// Wys�anie informacji o zako�czeniu gry.
    return netObject->send(header);
}

bool Message::reciveEmpty(Network* netObject)
{
    /// Tworzenie headera
    Header header;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y header to zwr�ci false.
    if (header.type != Message::empty)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid�owe otrzymanie pustej wiadomo�ci.
    return true;
}

bool Message::reciveString(Network* netObject, std::string& string)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y header to zwr�ci false.
    if (header.type != Message::string)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Przepisuje otrzymane informacje z wektora do string.
    string.resize(static_cast<size_t>(payload.size()));
    std::copy(payload.begin(), payload.end(), string.begin());

    /// Prawid�owe otrzymanie wiadomo�ci.
    return true;
}

bool Message::reciveGameStart(Network* netObject)
{
    /// Tworzenie headera.
    Header header;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y header to zwr�ci false.
    if (header.type != Message::game_start)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid�owe otrzymanie informacji o rozpocz�ciu gry.
    return true;
}

bool Message::reciveShot(Network* netObject, uint8_t& x, uint8_t& y)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y rodzaj danych to zwr�ci false.
    if (header.type != Message::shot || header.payloadSize != sizeof(ShotPayload))
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Tworzenie struktury ShotPayload.
    ShotPayload recStruct;
    /// Przepisanie z wektora do struktury.
    std::copy(payload.begin(), payload.end(), reinterpret_cast<uint8_t*>(&recStruct));

    /// Odpowiednie przypisanie danych.
    x = recStruct.x;
    y = recStruct.y;

    /// Prawid�owe otrzymanie informacji o strzale.
    return true;
}

bool Message::reciveResponse(Network* netObject, Board::FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y rodzaj danych to zwr�ci false.
    if (header.type != Message::response || header.payloadSize < sizeof(Board::FieldStatus))
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Obliczenie nowego rozmiaru wsp�rz�dnych i zamiana tego rozmiaru.
    size_t vecSize = (header.payloadSize - sizeof(Board::FieldStatus)) / 2;
    cordsX.resize(vecSize);
    cordsY.resize(vecSize);

    /// Tworzenie iteratora "it" dla wektora i ustawienie go na jego pocz�tku.
    std::vector<uint8_t>::iterator it = payload.begin();

    /// Kopiowanie z Payload do status informacji o polu planszy.
    std::copy(it, it + sizeof(Board::FieldStatus), reinterpret_cast<uint8_t*>(&status));

    /// Kopiowanie informacji o wsp�rz�dnych pola planszy.
    if (vecSize > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(it, it + vecSize, cordsX.begin());
        it += vecSize;
        std::copy(it, it + vecSize, cordsY.begin());
    }

    /// Prawid�owe otrzymanie odpowiedzi.
    return true;
}

bool Message::reciveEndGame(Network* netObject)
{
    /// Tworzenie headera.
    Header header;

    /// Jak nie otrzyma to zwr�ci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z�y rodzaj danych to zwr�ci false.
    if (header.type != Message::end_game)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid�owe otrzymanie inforamcji o ko�cu gry.
    return true;
}

uint32_t Network::getDefaultPort()
{
    return DEFAULT_HOST_PORT; 
}

const char* Network::getDefaultIP()
{
    return DEFAULT_HOST_IP; 
}

bool Network::isValidIP(std::string ip)
{
    /// Sprawdzenie poprawno�ci adresu IP
    try
    {
        asio::ip::make_address_v4(ip);
    }
    /// �apanie b��du.
    catch (const std::exception& exception)
    {
        return false; 
    }

    /// Podanie prawid�owego adresu IP.
    return true;
}

bool Network::isConnected()
{
    /// Sprwadzenie po��czenia.
    return socket.is_open();
}

bool Network::send(Message::Header& header)
{
    /// Wysy�anie samego headera
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(Message::Header)));
    }
    /// �apanie b��d�w
    catch (const asio::system_error& error)
    {
        /// B��d braku po��cznia.
        if (error.code() == asio::error::broken_pipe)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta�e
        else
        {
            std::cerr << "Exception: " << error.what() << std::endl;
        }

        return false;
    }

    return true;
}

bool Network::send(Message::Header& header, std::vector<uint8_t>& message)
{
    /// Wysy�anie headera wraz z jak�� wiadomo�ci�.
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(Message::Header)));
        asio::write(socket, asio::buffer(message));
    }
    /// �apanie b��d�w
    catch (const asio::system_error& error)
    {
        /// B��d braku po��cznia.
        if (error.code() == asio::error::broken_pipe)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta�e.
        else
        {
            std::cerr << "Exception: " << error.what() << std::endl;
        }

        return false;
    }

    return true;
}

bool Network::recive(Message::Header& header)
{
    /// Otrzymanie headera.
    try
    {
        asio::read(socket, asio::buffer(&header, sizeof(Message::Header)));
    }
    /// �apanie b��d�w.
    catch (const asio::system_error& error)
    {
        /// B��d braku po��czenia.
        if (error.code() == asio::error::eof)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta�e.
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
    /// Otrzymanie headera i jakiej� wiadomo�ci.
    try
    {
        asio::read(socket, asio::buffer(&header, sizeof(Message::Header)));

        message.resize(header.payloadSize);
        socket.wait(socket.wait_read);

        asio::read(socket, asio::buffer(message.data(), message.size()));
    }
    /// �apanie b��d�w.
    catch (const asio::system_error& error)
    {
        /// B��d braku po��czenia.
        if (error.code() == asio::error::eof)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta�e.
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
    /// Roz��czenie.
    try
    {
        socket.close();
    }
    /// �apanie b��d�w.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}

std::string NetworkHost::getLocalIP()
{
    /// Zmienna przechowuj�ca IP.
    std::string localIP; 

    try
    {
        /// Dostanie nazwy komputera u�ytkownika.
        std::string hostName = asio::ip::host_name();
        /// Odpalenie resolvera.
        asio::ip::tcp::resolver resolver(context);
        /// Wy�uskanie adres�w IP komputera. Stworzenie zapytanie do resolvera.
        asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(), hostName, "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
        /// Zapis pierwszego wy�uskanego adresu IP do naszej zmiennej.
        asio::ip::tcp::endpoint ipAddr = *endpoints; 

        /// Zamiana na string.
        localIP = ipAddr.address().to_string();
    }
    /// �apanie b��d�w.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return std::string();
    }

    return localIP; 
}

bool NetworkHost::waitForConnection(uint16_t port)
{
    /// Czekanie na po��czenie pomi�dzy Hostem a Guestem.
    try
    {
        /// Przypisanie portu i wszystkich adres�w IP do endpoint'a
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);

        /// Bindowanie endpoint'a do akceptora po��cze�.
        acceptor.bind(endpoint);
        /// Uruchomienie akceptora.
        acceptor.listen();

        /// Tworzenie socket'u, do kt�rego p�niej zostanie przypisane po��czenie.
        socket = asio::ip::tcp::socket(context);
        /// Czekanie na nawi�zanie po��czenia.
        acceptor.accept(socket);
    }
    /// �apanie b��d�w.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}

NetworkHost::NetworkHost() : acceptor(context, asio::ip::tcp::v4())
{
    /// Ustawia opdowiednio opcje akceptora.
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
}

bool NetworkGuest::connect(const std::string hostIP, uint16_t hostPort)
{
    /// Nawi�zuje po��czenie.
    try
    {
        endpoint = asio::ip::tcp::endpoint(asio::ip::make_address_v4(hostIP), hostPort);

        socket.connect(endpoint);
    }
    /// �apanie b��d�w.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}
