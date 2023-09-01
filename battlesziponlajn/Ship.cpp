#include "Ship.hpp"
#include <cstdlib>
#include <ctime>

#ifdef DEBUG

#include <iostream>

#endif // DEBUG


///	Funkcja sprawdzaj�ca czy statek jest zatopiony
bool Ship::checkIfSunk(void)
{
	///	Iteracja po wszystkich polach statku, kt�ra sprawdza czy kt�ra� z nich jest oznaczona liter� "S", co oznacza,
	///	�e statek jest zatopiony.
	for (int i = 0; i < size; i++)
	{
		///	Zwraca true je�li jest zatopiony.
		if (deck[i] == 'X') return true;
	}
	/// Zwraca false je�li nie jest zatopiony.
	return false;
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

#ifdef DEBUG

	std::cout << "guess:  x = " << locationX << "  y = " << locationY << "  orientation: " << orientation << std::endl;

#endif // DEBUG

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