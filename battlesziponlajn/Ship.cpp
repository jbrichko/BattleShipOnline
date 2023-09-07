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

///	Funkcja losuj¹ca pseudolosowe wspó³rzêdne pocz¹tku statku.
void Ship::randomPlace(int boardSize)
{
	///	Zmienna, która okreœla czy funkcja srand() zosta³a ju¿ wykonana. Pocz¹tkowo ustalona na wartoœæ false.
	static bool didSrandExecute = false; 

	if(didSrandExecute == false)
	{
		///	Wywo³anie funkcji srand(), po jej wykonaniu zmienia wartoœæ znacznika didSrandExecute na true. Oznacza to, ¿e funkcja ta zosta³a wywo³ana.
		srand(time(nullptr)); 
		didSrandExecute = true; 
	}

	///	Losowanie orientacji statku.
	orientation = static_cast<Orientation>(rand() % 2); 

	///	Losowanie wspó³rzêdnych w zale¿noœci od orientacji statku.
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

///	Domyœlny konstruktor klasy Ship. Tworzony jest w nim statek o polu "S".
Ship::Ship(ShipSize length)
	: size(length)
{
	deck = new	char[size];

	///	Iteruje po d³ugoœci statku.
	for (int i = 0; i < size; i++)
		deck[i] = 'S'; 

	///	Przypisuje wartoœci, które s¹ nieprawid³owe w kontekœcie planszy gry.
	locationX = -1;
	locationY = -1;
}

///	Domyœlny dekonstruktor klasy Ship.
Ship::~Ship()
{
	delete[] deck;
}