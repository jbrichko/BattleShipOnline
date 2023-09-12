#include "Ship.hpp"

#include <cstdlib>
#include <iostream>
#include <chrono>

#include "Board.hpp"

Ship::ShipSize Ship::getSize()
{
	return size;
}

std::vector<char> Ship::getDeck()
{
	return deck; 
}

char Ship::getDeck(unsigned int position)
{
	return deck[position]; 
}

int Ship::getLocationX()
{
	return locationX; 
}

int Ship::getLocationY()
{
	return locationY; 
}

Ship::Orientation Ship::getOrientation()
{
	return orientation; 
}

void Ship::getAllCords(std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
	cordsX.resize(size); 
	cordsY.resize(size); 

	for (unsigned int i = 0; i < size; i++)
	{
		cordsX[i] = locationX + i * static_cast<unsigned int>(orientation); 
		cordsY[i] = locationY + i * static_cast<unsigned int>(!orientation); 
	}
}

///	Funkcja losująca pseudolosowe współrzędne początku statku.
void Ship::randomPlace(int boardSize)
{
	///	Zmienna, która określa czy funkcja srand() została już wykonana. Początkowo ustalona na wartość false.
	static bool didSrandExecute = false;

	if (didSrandExecute == false)
	{
		///	Wywołanie funkcji srand(), po jej wykonaniu zmienia wartość znacznika didSrandExecute na true. Oznacza to, że funkcja ta została wywołana.
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		didSrandExecute = true;
	}

	///	Losowanie orientacji statku.
	orientation = static_cast<Orientation>(rand() % 2);

	///	Losowanie współrzędnych w zależności od orientacji statku.
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

bool Ship::isInShip(int& deckID, unsigned int x, unsigned int y)
{
	if ((orientation == horizontal) && (locationY == y))
	{
		deckID = x - locationX;
	}
	else if ((orientation == vertical) && (locationX == x))
	{
		deckID = y - locationY;
	}
	else
	{
		return false;
	}

	if (deckID >= 0 && deckID < size)
	{
		return true;
	}

	return false;
}

bool Ship::isHit(int deckID)
{
	if (deckID >= 0 && deckID < size && deck[deckID] == Board::FieldStatus::ship)
	{
		deck[deckID] = Board::FieldStatus::hit; 

		return true;
	}

	return false; 
}

bool Ship::isSinking(void)
{
	///	Sprawdzenie statusu pola planszy i opowiednia reakcja.
	for (unsigned int i = 0; i < size; i++)
	{
		if (deck[i] == Board::FieldStatus::ship)
		{
			///	Badane pole jest statkiem.
			return false; 
		}
	}

	for (unsigned int i = 0; i < size; i++)
	{
		///	Badane pole jest zatopionym statkiem.
		deck[i] = Board::FieldStatus::sunk; 
	}

	return true;
}

void Ship::inputShipCords(int boardSize)
{
	char inputChar = '\n';

	std::cout << "Current ship size is: " << size << std::endl; 

	while (inputChar != 'h' && inputChar != 'v')
	{
		std::cout << "Enter ship orientation: horizontal [h] or vertical [v]: ";
		std::cin >> inputChar;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (inputChar == 'h')
	{
		orientation = Orientation::horizontal;
	}
	else
	{
		orientation = Orientation::vertical;
	}

	while (true)
	{
		std::cout << "Enter ship coordinates in following format: X Y \n";

		if (std::cin >> locationX >> locationY && 0 <= locationX && locationX < boardSize + static_cast<int>(orientation) * (1 - size) && 0 <= locationY && locationY < boardSize + static_cast<int>(!orientation) * (1 - size))
		{
			return;
		}
		else
		{
			std::cin.clear();                                                   // clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
			std::cout << "Invalid input or wrong coordinates. Please try again. \n";
		}
	}

	std::cin.ignore(); 
}

///	Domyślny konstruktor klasy Ship. Tworzony jest w nim statek o polu "S".
Ship::Ship(ShipSize length)
	: size(length)
{
	deck.resize(length, Board::FieldStatus::ship);

	///	Przypisuje wartości, które są nieprawidłowe w kontekście planszy gry.
	locationX = -1;
	locationY = -1;
}