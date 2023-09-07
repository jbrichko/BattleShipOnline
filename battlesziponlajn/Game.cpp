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

void Game::mainLoop()
{

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
        hostRunner();
    }
    else if (netRole == Network::NetRole::host)
    {
        guestRunner();
    }
    else
    {
        std::cout << "Bad argument, exiting. \n";
    }
}

void Game::clearConsole()
{
    system("CLS");
}

void Game::getButtonPress()
{
    system("pause");
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