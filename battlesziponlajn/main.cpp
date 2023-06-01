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

class Music
{
public: 

    //const std::string menuMusicFilePath = "resources/menu-soundtrack-01.wav";

    static void playMenuMuisc()
    {
        PlaySound(TEXT("resources/menu-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_ASYNC);
    }

    static void stopMusic()
    {
        PlaySound(nullptr, nullptr, SND_FILENAME | SND_ASYNC);
    }
};





int main(void)
{

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

    char a;
    std::cin >> a;

    EnemyBoard enemyBoard; 
    PlayerBoard playerBoard; 

    enemyBoard.print(); 

    playerBoard.placeShips(); 
    playerBoard.print();

    std::cout << std::endl; 

    for (int i = 0; i < playerBoard.noOfShips; i++)
    {
        std::cout << "id:  " << i << " x = " << playerBoard.ships[i]->locationX << " y = " << playerBoard.ships[i]->locationY << std::endl;
    }

    std::cin >> a;

	return 0;
}