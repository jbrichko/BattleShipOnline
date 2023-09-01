#include "Ship.hpp"
#include <cstdlib>
#include <ctime>

#ifdef DEBUG

#include <iostream>

#endif // DEBUG


///	Funkcja sprawdzaj¹ca czy statek jest zatopiony
bool Ship::checkIfSunk(void)
{
	///	Iteracja po wszystkich polach statku, która sprawdza czy któraœ z nich jest oznaczona liter¹ "S", co oznacza,
	///	¿e statek jest zatopiony.
	for (int i = 0; i < size; i++)
	{
		///	Zwraca true jeœli jest zatopiony.
		if (deck[i] == 'X') return true;
	}
	/// Zwraca false jeœli nie jest zatopiony.
	return false;
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

#ifdef DEBUG

	std::cout << "guess:  x = " << locationX << "  y = " << locationY << "  orientation: " << orientation << std::endl;

#endif // DEBUG

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