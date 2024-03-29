﻿#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#endif

void Game::netRoleSelector()
{
    if (skipNetRoleSelect == false)
    {
        char inputChar = '\n';

        while (inputChar != 'h' && inputChar != 'g')
        {
            std::cout << "Select host [h] or guest [g]: ";
            std::cin >> inputChar;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            netRole = static_cast<Network::NetRole>(inputChar);
        }
    }

    if (netRole == Network::NetRole::host)
    {
        if (hostConnectDialog())
            return; 
    }
    else
    {
        isPlayerTurn = true;
        if (guestConnectDialog())
            return; 
    }

    throw std::runtime_error("Connection failed. Exiting. ");
}

bool Game::hostConnectDialog()
{
    NetworkHost *host = new NetworkHost;
    netObject = host;

    std::cout << "Your local IP address is: " << host->getLocalIP() << std::endl;
    std::cout << "Waiting for connection. \n";

    if (host->waitForConnection())
    {
        std::cout << "Connected! \n";

        return true;
    }

    return false;
}

bool Game::guestConnectDialog()
{
    NetworkGuest *guest = new NetworkGuest;
    netObject = guest;

    if (skipGetIP == false)
    {
        std::cout << "Host IP address [" << Network::getDefaultIP() << "]: ";
        std::getline(std::cin, ipAddr);

        if (Network::isValidIP(ipAddr) == false)
        {
            if (ipAddr.empty() == false)
                std::cout << "Wrong IP Address, reverting to default. \n";

            ipAddr = Network::getDefaultIP();
        }
    }

    if (guest->connect(ipAddr))
    {
        std::cout << "Connected to: " << ipAddr << std::endl;

        return true;
    }

    return false;
}

bool Game::playerTurn()
{
    messageCoordX.resize(1);
    messageCoordY.resize(1);

    inputShootCords(messageCoordX[0], messageCoordY[0]);
    if (Message::sendShot(netObject, messageCoordX[0], messageCoordY[0]) == false)
        return false;

    if (Message::reciveResponse(netObject, messageFieldStatus, messageCoordX, messageCoordY) == false)
        return false;

    enemyBoard.update(messageFieldStatus, messageCoordX, messageCoordY);

    clearConsole();

    switch (messageFieldStatus)
    {
    case Board::FieldStatus::miss:
        isPlayerTurn = false;

        std::cout << "Missed! \n";
        break;
    case Board::FieldStatus::hit:
        std::cout << "Hit! \n";
        break;
    case Board::FieldStatus::sunk:
        enemyBoard.oneShipLess();

        std::cout << "Sunk! \n";
        break;
    }

    return true;
}

bool Game::enemyTurn()
{
    messageCoordX.resize(1);
    messageCoordY.resize(1);

    if (Message::reciveShot(netObject, messageCoordX[0], messageCoordY[0]) == false)
        return false;

    playerBoard.checkShotStatus(messageFieldStatus, messageCoordX, messageCoordY);

    clearConsole();

    switch (messageFieldStatus)
    {
    case Board::FieldStatus::miss:
        isPlayerTurn = true;

        std::cout << "Without a scrach! \n";
        break;
    case Board::FieldStatus::hit:
        std::cout << "Your ship got hit! \n";
        break;
    case Board::FieldStatus::sunk:
        playerBoard.oneShipLess();

        std::cout << "One ship less! \n";
        break;
    }

    if (Message::sendResponse(netObject, messageFieldStatus, messageCoordX, messageCoordY) == false)
        return false;

    return true;
}

void Game::inputShootCords(uint8_t &shootCoordX, uint8_t &shootCoordY)
{
    int x, y;

    std::cout << "Where do you want to shoot? \n";

    while (true)
    {
        std::cout << "Enter coordinates in following format: X Y \n";

        if (std::cin >> x >> y && 0 <= x && x < Board::getSize() && 0 <= y && y < Board::getSize())
        {
            shootCoordX = static_cast<uint8_t>(x);
            shootCoordY = static_cast<uint8_t>(y);

            return;
        }
        else
        {
            std::cin.clear();                                                   // clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
            std::cout << "Invalid input. Please try again. \n";
        }
    }
}

bool Game::isEndingCondition()
{
    if (playerBoard.getRemainingShips() <= 0)
    {
        std::cout << "You lost! \n";

        return true;
    }

    if (enemyBoard.getRemainingShips() <= 0)
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

Game::~Game()
{
    delete netObject;
}

void Game::run()
{
    if (showMenu)
    {
        AudioVisual::loadMenuGraphic();

        if (playMusic)
            AudioVisual::playMenuMusic();

        getButtonPress();
        clearConsole();

        if (playMusic)
            AudioVisual::stopMusic();
    }

    netRoleSelector();
    playerBoard.placeShips();

    if (playMusic)
        AudioVisual::playGameMusic();

    clearConsole();

    while (true)
    {

        enemyBoard.print();
        playerBoard.print();

        if (isPlayerTurn)
        {
            if (playerTurn() == false)
                break;
        }
        else
        {
            if (enemyTurn() == false)
                break;
        }

        if (isEndingCondition())
        {
            return;
        }
    }

    throw std::runtime_error("Connection failed. Exiting. ");
}

void Game::handleArgs(int argCount, char **argStrings)
{
    for (int i = 1; i < argCount; i++)
    {
        if (strcmp(argStrings[i], "-h") == 0 || strcmp(argStrings[i], "--host") == 0)
        {
            netRole = Network::NetRole::host;
            skipNetRoleSelect = true;
        }
        else if (strcmp(argStrings[i], "-g") == 0 || strcmp(argStrings[i], "--guest") == 0)
        {
            netRole = Network::NetRole::guest;
            skipNetRoleSelect = true;

            if (i + 1 < argCount && Network::isValidIP(argStrings[i + 1]))
            {
                i++;
                ipAddr = argStrings[i];
                skipGetIP = true;
            }
        }
        else
        {
            throw std::runtime_error("Bad input argument."); 
        }
    }
}
