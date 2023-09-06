#include "NetworkManager.hpp"

/// Sprwadzenie po³¹czenia.
bool Network::isConnected()
{
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

        std::cout << "Waiting for connection on port " << port << std::endl;

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

#ifdef DEBUG
        std::cout << "Local port: " << socket.local_endpoint().port() << std::endl;
#endif

    }
    /// £apanie b³êdów.
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return false;
    }

    return true;
}


bool Message::sendEmpty(Network* netObject)
{
    Header header; 
    header.type = Message::empty; 
    header.payloadSize = 0; 
    
    return netObject->send(header); 
}

bool Message::sendString(Network *netObject, std::string &string)
{
    Header header;
    header.type = Message::string;

    std::vector<uint8_t> payload(string.begin(), string.end());
    header.payloadSize = payload.size();

    return netObject->send(header, payload);
}

bool Message::sendGameStart(Network* netObject)
{
    Header header;
    header.type = Message::game_start;
    header.payloadSize = 0;

    return netObject->send(header);
}

bool Message::sendShot(Network *netObject, uint8_t x, uint8_t y)
{
    Header header;
    header.type = Message::shot;
    header.payloadSize= sizeof(ShotPayload);

    ShotPayload payloadStruct; 
    payloadStruct.x = x; 
    payloadStruct.y = y; 

    std::vector<uint8_t> payload(header.payloadSize);
    std::copy(reinterpret_cast<uint8_t*>(&payloadStruct), reinterpret_cast<uint8_t*>(&payloadStruct) + header.payloadSize, payload.begin());

    return netObject->send(header, payload);
}

bool Message::sendResponse(Network* netObject, Board::FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    Header header;
    header.type = Message::response;

    header.payloadSize = sizeof(Board::FieldStatus) + cordsX.size() + cordsY.size(); 
    std::vector<uint8_t> payload(header.payloadSize);
    std::vector<uint8_t>::iterator it = payload.begin(); 
    
    std::copy(reinterpret_cast<uint8_t*>(&status), reinterpret_cast<uint8_t*>(&status) + sizeof(Board::FieldStatus), it);
    
    if (cordsX.size() == cordsY.size() && cordsX.size() > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(cordsX.begin(), cordsX.end(), it);
        it += cordsX.size();
        std::copy(cordsY.begin(), cordsY.end(), it);
    }

    return netObject->send(header, payload);
}

bool Message::sendEndGame(Network* netObject)
{
    Header header;
    header.type = Message::end_game;
    header.payloadSize = 0;

    return netObject->send(header);
}

bool Message::reciveEmpty(Network* netObject)
{
    Header header;

    if (netObject->recive(header) != true)
    {
        return false; 
    }

    if (header.type != Message::empty)
    {
        std::cerr << "Received message does not match expected type. \n"; 
        return false; 
    }

    return true;
}

bool Message::reciveString(Network* netObject, std::string& string)
{
    Header header;
    std::vector<uint8_t> payload;

    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    if (header.type != Message::string)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    string.resize(static_cast<size_t>(payload.size())); 
    std::copy(payload.begin(), payload.end(), string.begin());

    return true;
}

bool Message::reciveGameStart(Network* netObject)
{
    Header header;

    if (netObject->recive(header) != true)
    {
        return false;
    }

    if (header.type != Message::game_start)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    return true;
}

bool Message::reciveShot(Network* netObject, uint8_t& x, uint8_t& y)
{
    Header header;
    std::vector<uint8_t> payload;

    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    if (header.type != Message::shot || header.payloadSize != sizeof(ShotPayload))
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    ShotPayload recStruct; 
    std::copy(payload.begin(), payload.end(), reinterpret_cast<uint8_t*>(&recStruct));

    x = recStruct.x; 
    y = recStruct.y; 

    return true;
}

bool Message::reciveResponse(Network* netObject, Board::FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
    Header header;
    std::vector<uint8_t> payload;

    if (netObject->recive(header, payload) != true)
    {
        return false;
    }

    if (header.type != Message::response || header.payloadSize < sizeof(Board::FieldStatus))
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    size_t vecSize = (header.payloadSize - sizeof(Board::FieldStatus)) / 2; 
    cordsX.resize(vecSize);
    cordsY.resize(vecSize);

    std::vector<uint8_t>::iterator it = payload.begin();

    std::copy(it, it + sizeof(Board::FieldStatus), reinterpret_cast<uint8_t*>(&status));

    if (vecSize > 0)
    {
        it += sizeof(Board::FieldStatus);
        std::copy(it, it + vecSize, cordsX.begin());
        it += vecSize;
        std::copy(it, it + vecSize, cordsY.begin());
    }
    
    return true; 
}

bool Message::reciveEndGame(Network* netObject)
{
    Header header;

    if (netObject->recive(header) != true)
    {
        return false;
    }

    if (header.type != Message::end_game)
    {
        std::cerr << "Received message does not match expected type. \n";
        return false;
    }

    return true;
}