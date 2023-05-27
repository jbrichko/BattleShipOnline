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





int main(void)
{

    std::ifstream file("cover-art.txt"); // Nazwa pliku .txt

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }

        file.close();
    }
    else {
        std::cout << "Nie mo�na otworzy� pliku.\n";
    }

    // Odtwarzanie pliku MP3 w tle
    PlaySound(TEXT("menu-soundtrack-01.wav"), NULL, SND_FILENAME | SND_ASYNC);

    char a;
    std::cin >> a;

    EnemyBoard enemyBoard; 
    PlayerBoard playerBoard; 

    enemyBoard.print(); 
    playerBoard.print();

    std::cin >> a;

	return 0;
}