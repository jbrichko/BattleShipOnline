#include "Testing.hpp"

void Testing::shootingOverNetScenario()
{
    roleSelector(); 

    playerBoard.placeShips();

    while (true)
    {
        enemyBoard.print();
        playerBoard.print();

        if (myTurn)
        {
            yourTurn();
        }
        else
        {
            youWait();
        }

        if (playerBoard.shipsRemaining <= 0)
        {
            std::cout << "You lose! \n"; 

            return; 
        }

        if (enemyBoard.shipsRemaining <= 0)
        {
            std::cout << "You win! Congratulations! \n";

            return;
        }
    }
}

void Testing::communicationScenario()
{
    uint8_t x, y; 

    roleSelector();

    if (myTurn)
    {
        Actions::getShootCoords(x, y);
        Message::sendShot(netObject, x, y);
        netObject->disconnect(); 
    }
    else
    {
        Message::reciveShot(netObject, x, y);
        printf("x= %u, y= %u \n", x, y); 
    }
}

void Testing::yourTurn()
{
    std::vector<uint8_t> resCoordX(1), resCoordY(1);
    Board::FieldStatus fieldStatus; 

    Actions::getShootCoords(resCoordX[0], resCoordY[0]);
    Message::sendShot(netObject, resCoordX[0], resCoordY[0]);

    Message::reciveResponse(netObject, fieldStatus, resCoordX, resCoordY); 
    
    enemyBoard.update(fieldStatus, resCoordX, resCoordY);

    switch (fieldStatus)
    {
    case Board::FieldStatus::miss:
        myTurn = false; 

        std::cout << "Missed! \n"; 
        break;
    case Board::FieldStatus::hit:
        std::cout << "Hit! \n";
        break;
    case Board::FieldStatus::sunk:
        enemyBoard.shipsRemaining--; 

        std::cout << "Sunk! \n";
        break;
    }
    
}

void Testing::youWait()
{
    std::vector<uint8_t> resCoordX(1), resCoordY(1);
    Board::FieldStatus fieldStatus;

    Message::reciveShot(netObject, resCoordX[0], resCoordY[0]);

    playerBoard.checkShotStatus(fieldStatus, resCoordX, resCoordY);

    switch (fieldStatus)
    {
    case Board::FieldStatus::miss:
        myTurn = true; 

        std::cout << "Without a scrach! \n";
        break;
    case Board::FieldStatus::hit:
        std::cout << "Your ship got hit! \n";
        break;
    case Board::FieldStatus::sunk:
        playerBoard.shipsRemaining--;

        std::cout << "One ship less! \n";
        break;
    }

    Message::sendResponse(netObject, fieldStatus, resCoordX, resCoordY);
}

void Testing::roleSelector()
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

bool Testing::hostRunner()
{
    NetworkHost* host = new NetworkHost; 
    netObject = host; 

    std::cout << "Your local IP address is: " << host->getLocalIP() << std::endl;

    if (host->waitForConnection())
    {
        std::cout << "Connected \n";

        return true;
    }

    delete host; 

    return false; 
}

bool Testing::guestRunner()
{
    NetworkGuest* guest = new NetworkGuest;
    netObject = guest; 

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

    if (guest->connect(ipAddr))
    {
        std::cout << "Connected to " << ipAddr << std::endl;

        myTurn = true; 

        return true; 
    }

    delete guest; 

    return false; 
}

void Testing::newRandomScenario()
{
    try 
    {
        playerBoard.placeShips();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return; 
    }

    playerBoard.print();
}

void Testing::convertResponseScenario()
{
    std::vector<uint8_t> payload;
    Message::Header header;


    {
        uint8_t x, y;
        std::vector<uint8_t> cordsX, cordsY;
        Board::FieldStatus status;
        char statusChar;
        std::string message;

        std::cin >> statusChar;
        std::cin.ignore();
        status = static_cast<Board::FieldStatus>(statusChar);

        while (true)
        {
            std::getline(std::cin, message);

            if (sscanf(message.c_str(), "%" SCNu8 " %" SCNu8, &x, &y) != 2)
            {
                break;
            }

            cordsX.push_back(x);
            cordsY.push_back(y);
        }


        header.type = Message::response;

        header.payloadSize = sizeof(Board::FieldStatus) + cordsX.size() + cordsY.size();
        payload.resize(header.payloadSize);
        std::vector<uint8_t>::iterator it = payload.begin();

        std::copy(reinterpret_cast<uint8_t*>(&status), reinterpret_cast<uint8_t*>(&status) + sizeof(Board::FieldStatus), it);


            it += sizeof(Board::FieldStatus);
            std::copy(cordsX.begin(), cordsX.end(), it);
            it += cordsX.size();
            std::copy(cordsY.begin(), cordsY.end(), it);
    }
    


    {
        std::vector<uint8_t> cordsX, cordsY;
        Board::FieldStatus status;

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

        std::cout << "Status: " << status << std::endl;

        for (unsigned int i = 0; i < cordsX.size(); i++)
        {
            printf("x = %u  y = %u \n", cordsX[i], cordsY[i]);
        }
    }
}

void Testing::gameStartScenario()
{
    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;

#ifdef _WIN32
    Game::loadMenuGraphic();
    Music::playMenuMusic();
    Game::getButtonPress();
    Game::clearConsole();
    Music::stopMusic();
    Music::playGameMusic();
#endif
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
