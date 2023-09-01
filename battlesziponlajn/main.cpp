#include "Board.hpp"
#include "Ship.hpp"
#include "NetworkManager.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

/*! \class Game
*   \brief Jest to klasa odpowiedzialna za g��wn� p�tl� gry.
*/
class Game
{
public: 

    /**
    *   Klasa posiada metody obs�uguj�ce konsol� takie jak: �adowanie grafiki lub czyszczenie widoku w konsoli.
    *   R�wnie� klasa odpowiada za prawid�owy przebieg rozgrywki - jest w niej g��wna p�tla gry.
    */

    /**
    *   \brief Czy�ci konsol� z informacji na niej wy�wietlanych.
    */
    static void clearConsole()
    {
        system("CLS");
    }

    /**
    *   \brief Pauzuje gr� do momentu wci�ni�cia jakiegokolwiek przycisku.
    */
    static void getButtonPress()
    {
        system("pause");
    }

    /**
    *   \brief �aduje grafik� ASCII w konsoli.
    */
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
            std::cout << "nie mo�na otworzy� pliku.\n";
        }
    }
};

/*! \class Action
*   \brief Jest to klasa odpowiedzialna za podstawowe akcje wykorzystywane w rozgrywce.
*/
class Actions
{
public:

    /** 
    *   W klasie tej znajduj� si� metody, kt�re odpowiadaj� za prawid�owy spos�b gry w statki.
    */  

    /**
    *   Wsp�rz�dne strza�u gracza.
    */
    static int shootCoordX;
    static int shootCoordY;
    
    /**
    *   Pobiera od gracza wsp�rz�dne strza�u za pomoc� klawiatury. Iteracje nast�puj� do momentu otrzymania od gracza
    *   prawid�owych danych. Wspo�rz�dna musi by� wi�ksza, r�wna 0 i mniejsza ni� d�ugo�� boku planszy. 
    */
    static void getShootCoords()
    {
        /// Estetyka rozgrywki.
        std::cout << std::endl << "WHAT ARE COORDINATES OF YOUR SHOT? " << std::endl;
        std::cout << "X: ";
        /// Podanie wsp�rz�dnej X.
        while (shootCoordX < Board::size && shootCoordX >= 0)
        {
            std::cin >> shootCoordX;
        }
        std::cout << " Y: ";
        /// Podanie wsp�rz�dnej Y.
        while (shootCoordY < Board::size && shootCoordY >= 0)
        {
            std::cin >> shootCoordY;
        }
    }

    static void playerShot()
    {

    }
};

/*! \class Music
*   \brief Jest to klasa odpowiedzialna za muzyk� s�yszan� w tle podczas rozgrywki.
*/
class Music
{
public: 

    /**
    *   W��cznie muzyki menu gry.
    */
    static void playMenuMusic()
    {
        PlaySound(TEXT("resources/menu-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    /**
    *   W��czenie muzyki w trakcie rozgrwyki.
    */
    static void playGameMusic() 
    {
        PlaySound(TEXT("resources/game-soundtrack-01.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    /**
    *   Wy��czenie muzyki.
    */
    static void stopMusic()
    {
        PlaySound(nullptr, nullptr, 0);
    }
};



int main(int argc, char** argv)
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

    /*

    char a;
    std::string message;

    if (argc > 1)
    {
        a = argv[1][0];
        printf("%c\n", a);
    }
    else
    {
        std::cin >> a;
    }


    if (a == '1')
    {
        NetworkGuest guest;

        if (guest.connect("127.0.0.1"))
        {
            std::cout << "Connected \n";

            if (argc > 2)
            {
                message = argv[2];
                std::cout << message << std::endl;
            }
            else
            {
                std::cin.ignore();
                std::getline(std::cin, message);
            }

            std::vector<uint8_t> payload(message.begin(), message.end());
            Network::MessageHeader header;

            header.type = Network::string;
            header.payloadSize = payload.size();

            guest.send(header, payload);
        }

    }
    else
    {
        NetworkHost host;

        if (host.waitForConnection())
        {
            std::cout << "Connected \n";

            std::vector<uint8_t> payload;
            Network::MessageHeader header;

            host.recive(header, payload);

            message.resize(static_cast<size_t>(payload.size()));

            std::copy(payload.begin(), payload.end(), message.begin());

            //for(int i = 0; i < payload.size(); i++) printf("%c", payload[i]);

            std::cout << message << std::endl;
        }

    }

    */

    NetworkHost host; 
    host.getLocalIP(); 

	return 0;
}