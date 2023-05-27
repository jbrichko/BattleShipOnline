#include "Board.hpp"
#include <iostream>


void Board::print(const char* title)
{
	std::cout << std::endl << std::endl;
	std::cout << "\t" << title << std::endl;
	std::cout << "\t" << "    0  1  2  3  4  5  6  7  8  9" << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "\t" << i << " | ";

		for (int j = 0; j < size; j++)
		{
			std::cout << board[i][j] << "  ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void PlayerBoard::print()
{



	

	Board::print("YOUR SHIPS: ");
}

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
	int minX1, maxX1, minX2, maxX2, minY1, maxY1, minY2, maxY2;
	bool separatedX, separatedY; 

	minX1 = maxX1 = ships[currentShipID]->locationX; 
	minY1 = maxY1 = ships[currentShipID]->locationY; 
	
	if (ships[currentShipID]->orientation == Ship::horizontal)
	{
		maxX1 += ships[currentShipID]->size - 1;
	}
	else
	{
		maxY1 += ships[currentShipID]->size - 1;
	}

	for (int i = 0; i < currentShipID; i++)
	{
		minX2 = maxX2 = ships[i]->locationX;
		minY2 = maxY2 = ships[i]->locationY;

		if (ships[i]->orientation == Ship::horizontal)
		{
			maxX2 += ships[i]->size - 1;
		}
		else
		{
			maxY2 += ships[i]->size - 1;
		}

		separatedX = (minX1 >= minX2 && maxX1 + 1 > minX2) || (minX2 > minX1 && maxX2 + 1 > minX1); 
		separatedY = (minY1 >= minY2 && maxY1 + 1 > minY2) || (minY2 > minY1 && maxY2 + 1 > minY1); 

		if (separatedX && separatedY == false) return false; 
	}

	return true; 
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


void EnemyBoard::print()
{
	Board::print("YOUR SHOTS: ");
}


