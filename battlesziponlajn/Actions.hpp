#pragma once

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#endif

#include "Board.hpp"

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


#ifdef _WIN32

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

#endif