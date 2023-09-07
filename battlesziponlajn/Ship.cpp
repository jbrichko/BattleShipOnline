#include "Ship.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Board.hpp"


bool Ship::checkIfSinking(void)
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (deck[i] == Board::FieldStatus::ship)
		{
			return false; 
		}
	}

	for (unsigned int i = 0; i < size; i++)
	{
		deck[i] = Board::FieldStatus::sunk; 
	}

	return true;
}

///	Funkcja losuj�ca pseudolosowe wsp�rz�dne pocz�tku statku.
void Ship::randomPlace(int boardSize)
{
	///	Zmienna, kt�ra okre�la czy funkcja srand() zosta�a ju� wykonana. Pocz�tkowo ustalona na warto�� false.
	static bool didSrandExecute = false; 

	if(didSrandExecute == false)
	{
		///	Wywo�anie funkcji srand(), po jej wykonaniu zmienia warto�� znacznika didSrandExecute na true. Oznacza to, �e funkcja ta zosta�a wywo�ana.
		srand(time(nullptr)); 
		didSrandExecute = true; 
	}

	///	Losowanie orientacji statku.
	orientation = static_cast<Orientation>(rand() % 2); 

	///	Losowanie wsp�rz�dnych w zale�no�ci od orientacji statku.
	if (orientation == horizontal)
	{
		locationX = rand() % (boardSize - size + 1);
		locationY = rand() % boardSize; 
	}
	else
	{
		locationY = rand() % (boardSize - size + 1);
		locationX = rand() % boardSize;
	}

}

///	Domy�lny konstruktor klasy Ship. Tworzony jest w nim statek o polu "S".
Ship::Ship(ShipSize length)
	: size(length)
{
	deck = new	char[size];

	///	Iteruje po d�ugo�ci statku.
	for (int i = 0; i < size; i++)
		deck[i] = 'S'; 

	///	Przypisuje warto�ci, kt�re s� nieprawid�owe w kontek�cie planszy gry.
	locationX = -1;
	locationY = -1;
}

///	Domy�lny dekonstruktor klasy Ship.
Ship::~Ship()
{
	delete[] deck;
}