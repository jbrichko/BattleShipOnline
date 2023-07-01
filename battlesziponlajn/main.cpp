#include "Board.hpp"
#include "Ship.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")


class Game
{
public: 

    static void clearConsole()
    {
        system("CLS");
    }

    static void getButtonPress()
    {
        system("pause");
    }

    static void loadMenuGraphic()
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
            std::cout << "nie mo¿na otworzyæ pliku.\n";
        }
    }
};

class Actions
{
public:
    static int shootCoordX;
    static int shootCoordY;
    
    static void getShootCoords()
    {
        std::cout << std::endl << "WHAT ARE COORDINATES OF YOUR SHOT? " << std::endl;
        std::cout << "X: ";
        while (shootCoordX < Board::size && shootCoordX >= 0)
        {
            std::cin >> shootCoordX;
        }
        std::cout << " Y: ";
        while (shootCoordY < Board::size && shootCoordY >= 0)
        {
            std::cin >> shootCoordY;
        }
    }

    static void playerShot()
    {

    }
};

class Music
{
public: 

    static void playMenuMusic()
    {
        PlaySound(TEXT("resources/menu-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    static void playGameMusic() 
    {
        PlaySound(TEXT("resources/game-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    static void stopMusic()
    {
        PlaySound(nullptr, nullptr, 0);
    }
};



int main(void)
{
    /*
    EnemyBoard enemyBoard; 
    PlayerBoard playerBoard;


    Game::loadMenuGraphic();
    Music::playMenuMusic();
    Game::getButtonPress();
    Game::clearConsole();
    Music::stopMusic();
    Music::playGameMusic();

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

    */

    Game::getButtonPress();

	return 0;
}