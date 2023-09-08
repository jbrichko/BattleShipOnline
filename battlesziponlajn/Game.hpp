#pragma once

#include "NetworkManager.hpp"
#include "Board.hpp"
#include "AudioVisual.hpp"

/*! \class Game
*   \brief Jest to klasa odpowiedzialna za g��wn� p�tl� gry.
*/
class Game
{
    /**
    *   Klasa posiada metody obs�uguj�ce konsolę.
    *   R�wnie� klasa odpowiada za prawid�owy przebieg rozgrywki - jest w niej g��wna p�tla gry i wiekszość funkcji pomocniczych do niej.
    */

private: 
    Network::NetRole netRole; 
    Network* netObject; 
    std::string ipAddr = ""; 

    std::vector<uint8_t> messageCoordX, messageCoordY;
    Board::FieldStatus messageFieldStatus;

    /// Utworzenie obiektów klas EnemyBoard i PlayerBoard
    EnemyBoard enemyBoard;
    PlayerBoard playerBoard;

    /// Flaga, która odpowiada za kolejność tur graczy.
    bool isPlayerTurn = false;

    /// Flagi dla handleArgs
    bool skipNetRoleSelect = false; 
    bool skipGetIP = false; 

    /**
    *   \brief Wybór roli: host czy guest.
    */
    void netRoleSelector();

    /**
    *   \brief Łączenie się - strona hosta.
    */
    bool hostConnectDialog();
    /**
    *   \brief Łączenie się - strona guesta.
    */
    bool guestConnectDialog();

    /**
    *   \brief Tura gracza - strzelanie.
    *   \return Zwraca informacje, która zdefiniuje kto będzie wykonywał następną turę.
    */
    bool playerTurn();
    /**
    *   \brief Tura gracza - czekanie na strzał przeciwnika.
    *   \return Zwraca informacje, która zdefiniuje kto będzie wykonywał następną turę.
    */
    bool enemyTurn();

    /**
    *   \brief Pobranie od gracza współrzędnych strzelania.
    *   \param shootCoordX Współrzędna X.
    *   \param shootCoordY Współrzędna Y.
    */
    void inputShootCords(uint8_t& shootCoordX, uint8_t& shootCoordY);

    /**
    *   \brief Sprawdza czy ktoś przypadkiem nie wygrał lub przegrał.
    *   \return Zwraca informacje czy ktoś wygrał lub przegrał.
    */
    bool isEndingCondition();

    /**
    *   \brief Czy�ci konsol� z informacji na niej wy�wietlanych.
    */
    static void clearConsole();

    /**
    *   \brief Pauzuje gr� do momentu wci�ni�cia jakiegokolwiek przycisku.
    */
    static void getButtonPress();


public:


    /**
    *   \brief Domyślny destruktor obiektów klasy Game.
    */
    ~Game(); 

    /**
    *   \brief Główna pętla gry.
    */
    void run();

    /**
    *   \brief Funkcja pomocnicza do testowania w systemie Linux.
    */
    void handleArgs(int argCount, char** argStrings); 
};

