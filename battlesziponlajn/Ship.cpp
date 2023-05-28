#include "Ship.hpp"
#include <cstdlib>
#include <ctime>

#ifdef DEBUG

#include <iostream>

#endif // DEBUG



bool Ship::checkIfSunk(void)
{
	for (int i = 0; i < size; i++)
	{
		if (deck[i] == 'S') return true;
	}

	return false;
}

void Ship::randomPlace(int boardSize)
{

	orientation = static_cast<Orientation>(rand() % 2); 

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
	std::cout << "guess:  x = " << locationX << "  y = " << locationY << std::endl; 
#endif // DEBUG

}

Ship::Ship(int length)
	: size(length)
{
	deck = new	char[size];

	for (int i = 0; i < size; i++)
		deck[i] = 'S'; 

	locationX = -1;
	locationY = -1;
}

Ship::~Ship()
{
	delete[] deck;
}