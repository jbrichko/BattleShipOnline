#include "Ship.hpp"
#include <cstdlib>
#include <ctime>

bool Ship::CheckIfSunk(void)
{
	for (int i = 0; i < size; i++)
	{
		if (deck[i] == false) return false;
	}

	return true;
}

void Ship::randomPlace(int boardSize)
{
	srand(time(0));

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
}

Ship::Ship(int length)
	: size(length)
{
	deck = new	int[size];

	for (int i = 0; i < size; i++)
		deck[i] = 0;

	locationX = -1;
	locationY = -1;
}

Ship::~Ship()
{
	delete[] deck;
}