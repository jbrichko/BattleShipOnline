#pragma once

//pozwala u�y� scanf zamiast scanf_s w Visual Studio
#define _CRT_SECURE_NO_WARNINGS

#include "Board.hpp"
#include "Ship.hpp"
#include "NetworkManager.hpp"   


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
    char hostSelect;
    std::string message;
    std::string ipAddr = "127.0.0.1";
    uint8_t x, y; 
    int argCount; 
    char** argStrings; 

public: 
	static void recieveText(Network* netObject); 
    static void recieveShot(Network* netObject);

    void communicationScenario();
    void hostRunner();
    void guestRunner(); 

    static void gameStartScenario();

    Testing(int argc, char** argv) 
    : argCount(argc), argStrings(argv) {}
};