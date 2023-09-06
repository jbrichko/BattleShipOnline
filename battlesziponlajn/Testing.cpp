#include "Testing.hpp"

void Testing::recieveText(Network *netObject)
{
    std::string message;

    std::vector<uint8_t> payload;
    Message::Header header;

    netObject->recive(header, payload);

    message.resize(static_cast<size_t>(payload.size()));

    std::copy(payload.begin(), payload.end(), message.begin());

    // for(int i = 0; i < payload.size(); i++) printf("%c", payload[i]);

    std::cout << message << std::endl;
}

void Testing::recieveShot(Network *netObject)
{
    std::vector<uint8_t> payload;
    Message::Header header;

    netObject->recive(header, payload);

    if (header.type == Message::shot && header.payloadSize == sizeof(Message::ShotPayload))
    {
        Message::ShotPayload recStruct;
        std::copy(payload.begin(), payload.end(), reinterpret_cast<uint8_t *>(&recStruct));

        printf("Cords: x= %d, y= %d \n", recStruct.x, recStruct.y);
    }
    else
    {
        printf("Chuj ci w kasztan, nie wiem co to jest! \n");
    }
}

void Testing::communicationScenario()
{
    if (argCount > 1 && (strcmp(argStrings[1], "-h") == 0 || strcmp(argStrings[1], "--host") == 0))
    {
        hostSelect = 'h';
    }
    else if (argCount > 1 && (strcmp(argStrings[1], "-g") == 0 || strcmp(argStrings[1], "--guest") == 0))
    {
        hostSelect = 'g';
    }
    else
    {
        std::cout << "Select host [h] or guest [g]: ";
        std::cin >> hostSelect;
        std::cin.ignore();
    }

    if (hostSelect == 'g')
    {
        guestRunner();
    }
    else if (hostSelect == 'h')
    {
        hostRunner();
    }
    else
    {
        std::cout << "Bad argument, exiting. \n";
    }
}

void Testing::hostRunner()
{
    NetworkHost host;

    std::cout << "Your local IP address is: " << host.getLocalIP() << std::endl;

    if (host.waitForConnection())
    {
        std::cout << "Connected \n";

        Testing::recieveText(&host);

        std::cout << "Send cords: ";
        scanf("%" SCNu8 " %" SCNu8, &x, &y);

        Message::send(&host, x, y);
    }
}

void Testing::guestRunner()
{
    NetworkGuest guest;
    std::string tempIP;

    if (argCount > 2)
    {
        tempIP = argStrings[2];
        std::cout << argStrings[2] << std::endl;
    }
    else
    {
        std::cout << "Host IP address [127.0.0.1]: ";
        std::getline(std::cin, tempIP);
    }

    try
    {
        asio::ip::make_address_v4(tempIP);

        ipAddr = tempIP;
    }
    catch (const std::exception &exception)
    {
        std::cout << "Bad IP Address, reverting to default. \n";
    }

    if (guest.connect(ipAddr))
    {
        std::cout << "Connected to " << ipAddr << std::endl;

        std::getline(std::cin, message);

        Message::send(&guest, message);

        Testing::recieveShot(&guest);
    }
}

Testing::gameStartScenario(void)
{
    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;


    Game::loadMenuGraphic();
    Music::playMenuMusic();
    Game::getButtonPress();
    Game::clearConsole();
    Music::stopMusic();
    Music::playGameMusic();

    enemyBoard.print();

    playerBoard.placeShips();
    playerBoard.print();


    std::cout << std::endl;

    for (int i = 0; i < playerBoard.noOfShips; i++)
    {
        std::cout << "main id:  " << i << " x = " << playerBoard.ships[i]->locationX
            << " y = " << playerBoard.ships[i]->locationY
            << " orientation: " << playerBoard.ships[i]->orientation
            << " len = " << playerBoard.ships[i]->size << std::endl;
    }

}