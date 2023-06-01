#include "Board.hpp"
#include "Ship.hpp"
#include <iostream>
#include <fstream>
#include <string>


// sound
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class Game
{
public: 
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

class NetworkManager
{
public:

    static int ipAdress;
    SOCKET socket;
};

class NetworkSlave : public NetworkManager
{

};

class NetworkMaster : public NetworkManager
{

};

class Music
{
public: 

    //const std::string menuMusicFilePath = "resources/menu-soundtrack-01.wav";

    static void playMenuMuisc()
    {
        PlaySound(TEXT("resources/menu-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    static void playGameMusic() 
    {

    }

    static void stopMusic()
    {
        PlaySound(nullptr, nullptr, 0);
    }
};





int main(void)
{

    char a;
    /*
    std::ifstream file("resources/cover-art.txt"); // nazwa pliku .txt

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
    

    Music::playMenuMuisc(); 
    

    
    std::cin >> a;
    */


    EnemyBoard enemyBoard; 
    PlayerBoard playerBoard; 

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

    std::cin >> a;

	return 0;
}