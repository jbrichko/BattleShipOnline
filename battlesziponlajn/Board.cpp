#include "Board.hpp"

int PlayerBoard::getShipsCount(void)
{
	int shipCount = 0;

	for (int i = 0; i < noOfShips; i++)
	{
		if (ships[i]->CheckIfSunk() == false) shipCount++; 
	}

	return shipCount; 
}

bool PlayerBoard::isPlacementGood(int currentShipID)
{
	for (int i = 0; i < currentShipID; i++)
	{

	}
}

void PlayerBoard::placeShips(void)
{

	for (int i = 0; i < noOfShips; i++)
	{
		do
		{
			ships[i]->randomPlace(size);

		} while (isPlacementGood(i) == false);
	}
}


