#pragma once

#include "NetworkManager.hpp"
#include "Board.hpp"

/*! \class Game
*   \brief Jest to klasa odpowiedzialna za g��wn� p�tl� gry.
*/
class Game
{
private: 
    Network::NetRole netRole; 
    Network* netObject; 

    bool isPlayerTurn = false; 

    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;

public:

    /**
    *   Klasa posiada metody obs�uguj�ce konsol� takie jak: �adowanie grafiki lub czyszczenie widoku w konsoli.
    *   R�wnie� klasa odpowiada za prawid�owy przebieg rozgrywki - jest w niej g��wna p�tla gry.
    */

    ~Game(); 

    void mainLoop(int argCount, char** argStrings);

    void netRoleSelector(int argCount, char** argStrings);

    bool hostConnectDialog();
    bool guestConnectDialog(int argCount, char** argStrings);

    void playerTurn();
    void enemyTurn(); 
    
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
};

