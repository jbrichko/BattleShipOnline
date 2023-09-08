#pragma once

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#endif


#ifdef _WIN32

/*! \class Music
*   \brief Jest to klasa odpowiedzialna za muzyk� s�yszan� w tle podczas rozgrywki.
*/
class AudioVisual
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

    /**
    *   \brief �aduje grafik� ASCII w konsoli.
    */
    static void loadMenuGraphic()
    {
        std::ifstream file("resources/cover-art-2.txt"); // nazwa pliku .txt

        if (file.is_open())
        {
            std::string line;

            while (std::getline(file, line))
            {
                std::cout << line << '\n';
            }

            file.close();
        }
        else
        {
            std::cout << "Could not open file.\n";
        }
    }
};

#endif