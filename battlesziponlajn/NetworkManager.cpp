#include "NetworkManager.hpp"

bool Message::sendEmpty(Network* netObject)
{
    /// Tworzenie headera wiadomoœci.
    Header header;
    /// Wybranie typu headera - empty.
    header.type = Message::empty;
    /// Okreœlenie rozmiaru headera - 0.
    header.payloadSize = 0;

    /// Wys³anie pustej wiadomoœci.
    return netObject->send(header);
}

bool Message::sendString(Network* netObject, std::string& string)
{
    /// Tworzenie headera wiadomoœci.
    Header header;
    /// Wybranie typu headera - string.
    header.type = Message::string;
    /// Zamiana stringa na wektor.
    std::vector<uint8_t> payload(string.begin(), string.end());
    /// Okreœlenie rozmiaru nowego wektora przechowuj¹cego wiadomoœæ.
    header.payloadSize = payload.size();

    /// Wys³anie wiadomoœci "string".
    return netObject->send(header, payload);
}

bool Message::sendGameStart(Network* netObject)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - game_start
    header.type = Message::game_start;
    /// Okreœlenie rozmiaru headera - 0. 
    header.payloadSize = 0;

    /// Wys³anie informacji - game_start.
    return netObject->send(header);
}

bool Message::sendShot(Network* netObject, uint8_t x, uint8_t y)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - shot.
    header.type = Message::shot;
    /// Okreœlenie rozmiaru headera - zgodnie z rozmiarem struktruty ShotPayload.
    header.payloadSize = sizeof(ShotPayload);

    /// Inicjacja struktuty ShotPayload.
    ShotPayload payloadStruct;
    /// Przypisanie wartoœci wspó³rzêdnej X do struktury.
    payloadStruct.x = x;
    /// Przypisanie wartoœci wspó³rzêdnej Y do struktury.
    payloadStruct.y = y;

    /// Tworzenie wektora o okreœlonym rozmiarze.
    std::vector<uint8_t> payload(header.payloadSize);
    /// Kopiowanie informacji ze struktury do wektora.
    std::copy(reinterpret_cast<uint8_t*>(&payloadStruct), reinterpret_cast<uint8_t*>(&payloadStruct) + header.payloadSize, payload.begin());

    /// Wysy³anie wspó³rzêdnych strza³u.
    return netObject->send(header, payload);
}

bool Message::sendResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - response.
    header.type = Message::response;

    /// Okreœlenie rozmiaru headera - informacja o statusie pola planszy + wspó³rzêdne tego pola.
    header.payloadSize = sizeof(Board::FieldStatus) + cordsX.size() + cordsY.size();
    /// Tworzenie wektora o okreœlonym rozmiarze.
    std::vector<uint8_t> payload(header.payloadSize);
    /// Tworzenie iteratora "it" dla wektora i ustawienie go na jego pocz¹tku.
    std::vector<uint8_t>::iterator it = payload.begin();

    /// Kopiowanie do wektora inforamcji o statusie pola planszy.
    std::copy(reinterpret_cast<uint8_t*>(&status), reinterpret_cast<uint8_t*>(&status) + sizeof(Board::FieldStatus), it);

    /// Kopiowanie do wektora wspó³rzêdnych pola planszy.
    if (cordsX.size() == cordsY.size() && cordsX.size() > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(cordsX.begin(), cordsX.end(), it);
        it += cordsX.size();
        std::copy(cordsY.begin(), cordsY.end(), it);
    }

    /// Wys³anie odpowiedzi.
    return netObject->send(header, payload);
}

bool Message::sendEndGame(Network* netObject)
{
    /// Tworzenie headera.
    Header header;
    /// Wybranie typu headera - end_game.
    header.type = Message::end_game;
    /// Okreœlenie rozmiaru headera - 0.
    header.payloadSize = 0;

    /// Wys³anie informacji o zakoñczeniu gry.
    return netObject->send(header);
}

bool Message::reciveEmpty(Network* netObject)
{
    /// Tworzenie headera
    Header header;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y header to zwróci false.
    if (header.type != Message::empty)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid³owe otrzymanie pustej wiadomoœci.
    return true;
}

bool Message::reciveString(Network* netObject, std::string& string)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y header to zwróci false.
    if (header.type != Message::string)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Przepisuje otrzymane informacje z wektora do string.
    string.resize(static_cast<size_t>(payload.size()));
    std::copy(payload.begin(), payload.end(), string.begin());

    /// Prawid³owe otrzymanie wiadomoœci.
    return true;
}

bool Message::reciveGameStart(Network* netObject)
{
    /// Tworzenie headera.
    Header header;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y header to zwróci false.
    if (header.type != Message::game_start)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid³owe otrzymanie informacji o rozpoczêciu gry.
    return true;
}

bool Message::reciveShot(Network* netObject, uint8_t& x, uint8_t& y)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y rodzaj danych to zwróci false.
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

    /// Prawid³owe otrzymanie informacji o strzale.
    return true;
}

bool Message::reciveResponse(Network* netObject, Board::FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    /// Tworzenie headera.
    Header header;
    /// Tworzenie wektora.
    std::vector<uint8_t> payload;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y rodzaj danych to zwróci false.
    if (header.type != Message::response || header.payloadSize < sizeof(Board::FieldStatus))
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Obliczenie nowego rozmiaru wspó³rzêdnych i zamiana tego rozmiaru.
    size_t vecSize = (header.payloadSize - sizeof(Board::FieldStatus)) / 2;
    cordsX.resize(vecSize);
    cordsY.resize(vecSize);

    /// Tworzenie iteratora "it" dla wektora i ustawienie go na jego pocz¹tku.
    std::vector<uint8_t>::iterator it = payload.begin();

    /// Kopiowanie z Payload do status informacji o polu planszy.
    std::copy(it, it + sizeof(Board::FieldStatus), reinterpret_cast<uint8_t*>(&status));

    /// Kopiowanie informacji o wspó³rzêdnych pola planszy.
    if (vecSize > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(it, it + vecSize, cordsX.begin());
        it += vecSize;
        std::copy(it, it + vecSize, cordsY.begin());
    }

    /// Prawid³owe otrzymanie odpowiedzi.
    return true;
}

bool Message::reciveEndGame(Network* netObject)
{
    /// Tworzenie headera.
    Header header;

    /// Jak nie otrzyma to zwróci false.
    if (netObject->recive(header) != true)
    {
        return false;
    }

    /// Jak otrzyma z³y rodzaj danych to zwróci false.
    if (header.type != Message::end_game)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    /// Prawid³owe otrzymanie inforamcji o koñcu gry.
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
    /// Sprawdzenie poprawnoœci adresu IP
    try
    {
        asio::ip::make_address_v4(ip);
    }
    /// £apanie b³êdu.
    catch (const std::exception& exception)
    {
        return false; 
    }

    /// Podanie prawid³owego adresu IP.
    return true;
}

bool Network::isConnected()
{
    /// Sprwadzenie po³¹czenia.
    return socket.is_open();
}

bool Network::send(Message::Header& header)
{
    /// Wysy³anie samego headera
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(Message::Header)));
    }
    /// £apanie b³êdów
    catch (const asio::system_error& error)
    {
        /// B³¹d braku po³¹cznia.
        if (error.code() == asio::error::broken_pipe)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta³e
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
    /// Wysy³anie headera wraz z jak¹œ wiadomoœci¹.
    try
    {
        asio::write(socket, asio::buffer(&header, sizeof(Message::Header)));
        asio::write(socket, asio::buffer(message));
    }
    /// £apanie b³êdów
    catch (const asio::system_error& error)
    {
        /// B³¹d braku po³¹cznia.
        if (error.code() == asio::error::broken_pipe)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta³e.
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
    /// £apanie b³êdów.
    catch (const asio::system_error& error)
    {
        /// B³¹d braku po³¹czenia.
        if (error.code() == asio::error::eof)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta³e.
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
    /// Otrzymanie headera i jakiejœ wiadomoœci.
    try
    {
        asio::read(socket, asio::buffer(&header, sizeof(Message::Header)));

        message.resize(header.payloadSize);
        socket.wait(socket.wait_read);

        asio::read(socket, asio::buffer(message.data(), message.size()));
    }
    /// £apanie b³êdów.
    catch (const asio::system_error& error)
    {
        /// B³¹d braku po³¹czenia.
        if (error.code() == asio::error::eof)
        {
            std::cerr << "The connection is lost." << std::endl;
        }
        /// Pozosta³e.
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
    /// Roz³¹czenie.
    try
    {
        socket.close();
    }
    /// £apanie b³êdów.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}

std::string NetworkHost::getLocalIP()
{
    /// Zmienna przechowuj¹ca IP.
    std::string localIP; 

    try
    {
        /// Dostanie nazwy komputera u¿ytkownika.
        std::string hostName = asio::ip::host_name();
        /// Odpalenie resolvera.
        asio::ip::tcp::resolver resolver(context);
        /// Wy³uskanie adresów IP komputera. Stworzenie zapytanie do resolvera.
        asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(), hostName, "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
        /// Zapis pierwszego wy³uskanego adresu IP do naszej zmiennej.
        asio::ip::tcp::endpoint ipAddr = *endpoints; 

        /// Zamiana na string.
        localIP = ipAddr.address().to_string();
    }
    /// £apanie b³êdów.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return std::string();
    }

    return localIP; 
}

bool NetworkHost::waitForConnection(uint16_t port)
{
    /// Czekanie na po³¹czenie pomiêdzy Hostem a Guestem.
    try
    {
        /// Przypisanie portu i wszystkich adresów IP do endpoint'a
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);

        /// Bindowanie endpoint'a do akceptora po³¹czeñ.
        acceptor.bind(endpoint);
        /// Uruchomienie akceptora.
        acceptor.listen();

        /// Tworzenie socket'u, do którego póŸniej zostanie przypisane po³¹czenie.
        socket = asio::ip::tcp::socket(context);
        /// Czekanie na nawi¹zanie po³¹czenia.
        acceptor.accept(socket);
    }
    /// £apanie b³êdów.
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
    /// Nawi¹zuje po³¹czenie.
    try
    {
        endpoint = asio::ip::tcp::endpoint(asio::ip::make_address_v4(hostIP), hostPort);

        socket.connect(endpoint);
    }
    /// £apanie b³êdów.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}
