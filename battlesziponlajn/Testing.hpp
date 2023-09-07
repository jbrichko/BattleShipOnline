#pragma once

//pozwala u�y� scanf zamiast scanf_s w Visual Studio
#define _CRT_SECURE_NO_WARNINGS

#include "Board.hpp"
#include "Ship.hpp"
#include "NetworkManager.hpp"   
#include "Game.hpp"
#include "Actions.hpp"


#include <string>
#include <iostream>

//dodaje makra do czytania uint8_t przez funkcj� scanf
#include <cinttypes>
//zawiera scanf
#include <cstdio>

//Klasa u�ywana do testowania i debugowania kodu
class Testing
{
private: 
    Network* netObject; 
    char hostSelect;
    std::string message;
    std::string ipAddr = "127.0.0.1";
    int argCount; 
    char** argStrings; 
    bool myTurn = false; 

    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;

public: 
    void shootingOverNetScenario();
    void yourTurn();
    void youWait();
    void roleSelector();
    bool hostRunner();
    bool guestRunner(); 
    

    static void gameStartScenario();
    static void convertResponseScenario();

    Testing(int argc, char** argv) 
    : argCount(argc), argStrings(argv) {}

    ~Testing()
    {
        delete netObject; 
    }
};