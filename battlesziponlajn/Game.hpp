#pragma once

#include "NetworkManager.hpp"
#include "Board.hpp"
#include "Actions.hpp"

/*! \class Game
*   \brief Jest to klasa odpowiedzialna za g��wn� p�tl� gry.
*/
class Game
{
private: 
    Network::NetRole netRole; 
    Network* netObject; 
    std::string ipAddr = ""; 

    std::vector<uint8_t> messageCoordX, messageCoordY;
    Board::FieldStatus messageFieldStatus;

    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;

    bool isPlayerTurn = false;

    /// flagi dla handleArgs
    bool skipNetRoleSelect = false; 
    bool skipGetIP = false; 

    void netRoleSelector();

    bool hostConnectDialog();
    bool guestConnectDialog();

    bool playerTurn();
    bool enemyTurn();
    void inputShootCords(uint8_t& shootCoordX, uint8_t& shootCoordY);

    bool isEndingCondition();

    /**
    *   \brief Czy�ci konsol� z informacji na niej wy�wietlanych.
    */
    static void clearConsole();

    /**
    *   \brief Pauzuje gr� do momentu wci�ni�cia jakiegokolwiek przycisku.
    */
    static void getButtonPress();

    /**
    *   \brief �aduje grafik� ASCII w konsoli.
    */
    static void loadMenuGraphic();

public:

    /**
    *   Klasa posiada metody obs�uguj�ce konsol� takie jak: �adowanie grafiki lub czyszczenie widoku w konsoli.
    *   R�wnie� klasa odpowiada za prawid�owy przebieg rozgrywki - jest w niej g��wna p�tla gry.
    */

    ~Game(); 

    void run();

    void handleArgs(int argCount, char** argStrings); 
};

