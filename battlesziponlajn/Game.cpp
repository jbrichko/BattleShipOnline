#pragma once

#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#endif

Game::~Game()
{
    delete netObject; 
}

void Game::mainLoop(int argCount, char** argStrings)
{
    netRoleSelector(argCount, argStrings);

    playerBoard.placeShips();

    while (true)
    {
        enemyBoard.print();
        playerBoard.print();

        if (isPlayerTurn)
        {
            playerTurn();
        }
        else
        {
            enemyTurn(); 
        }

        if (isEndingCondition())  
            return; 
    }
}

void Game::netRoleSelector(int argCount, char** argStrings)
{
    char inputChar; 

    if (argCount > 1 && (strcmp(argStrings[1], "-h") == 0 || strcmp(argStrings[1], "--host") == 0))
    {
        netRole = Network::NetRole::host;
    }
    else if (argCount > 1 && (strcmp(argStrings[1], "-g") == 0 || strcmp(argStrings[1], "--guest") == 0))
    {
        netRole = Network::NetRole::guest;
    }
    else
    {
        while (true)
        {
            try
            {
                std::cout << "Select host [h] or guest [g]: ";
                std::cin >> inputChar;
                std::cin.ignore();

                netRole = static_cast<Network::NetRole>(inputChar);
            }
            catch (const std::bad_cast& except)
            {
                std::cerr << "Invalid input: " << except.what() << std::endl;

                continue; 
            }

            break; 
        }
    }

    if (netRole == Network::NetRole::host)
    {
        hostConnectDialog();
    }
    else if (netRole == Network::NetRole::host)
    {
        guestConnectDialog(argCount, argStrings);
    }
}

bool Game::hostConnectDialog()
{
    NetworkHost* host = new NetworkHost;
    netObject = host;

    std::cout << "Your local IP address is: " << host->getLocalIP() << std::endl;
    std::cout << "Waiting for connection. \n";

    if (host->waitForConnection())
    {
        std::cout << "Connected! \n";

        return true;
    }

    delete host;

    return false; 
}

bool Game::guestConnectDialog(int argCount, char** argStrings)
{
    NetworkGuest* guest = new NetworkGuest;
    netObject = guest;

    std::string ipAddr; 

    if (argCount > 2)
    {
        ipAddr = argStrings[2];
        std::cout << argStrings[2] << std::endl;
    }
    else
    {
        std::cout << "Host IP address [" << Network::DEFAULT_HOST_IP << "]: ";
        std::getline(std::cin, ipAddr);
    }

    if (Network::isValidIP(ipAddr) == false)
    {
        if(ipAddr.empty() == false)
            std::cout << "Wrong IP Address, reverting to default. \n";

        ipAddr = Network::DEFAULT_HOST_IP; 
    }

    if (guest->connect(ipAddr))
    {
        std::cout << "Connected to: " << ipAddr << std::endl;

        return true;
    }

    delete guest;

    return false;
}

void Game::playerTurn()
{

}

void Game::enemyTurn() 
{

}

bool Game::isEndingCondition()
{
    if (playerBoard.shipsRemaining <= 0)
    {
        std::cout << "You lost! \n";

        return true;
    }

    if (enemyBoard.shipsRemaining <= 0)
    {
        std::cout << "You won! Congratulations! \n";

        return true;
    }

    return false; 
}

void Game::clearConsole()
{
#ifdef _WIN32
    /// Dla systemu Windows.
    system("CLS");
#else
    /// Dla systemu Linux.
    system("clear");
#endif
}

void Game::getButtonPress()
{
    std::cout << "Press Enter to continue...";
    /// Oczekiwanie na Enter.
    std::cin.get();
}

void Game::loadMenuGraphic()
{
    std::ifstream file("resources/cover-art-2.txt"); // nazwa pliku .txt

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }

        file.close();
    }
    else {
        std::cout << "nie mo�na otworzy� pliku.\n";
    }
}