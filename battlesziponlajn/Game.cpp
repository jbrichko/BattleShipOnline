#pragma once

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#endif

#include "Game.hpp"

void Game::mainLoop()
{

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