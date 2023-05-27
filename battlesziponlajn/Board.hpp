#pragma once

#include "Ship.hpp"

class Board
{
public:

	const int size = { 10 }; 

	enum FieldStatus : char
	{
		empty = '~',
		shot = '*',
		hit = 'H',
	};

	FieldStatus** board;

	void print(const char* title);

	Board()
	{
		board = new FieldStatus * [size];

		for (int i = 0; i < size; i++)
		{
			board[i] = new FieldStatus[size];

			for (int j = 0; j < size; j++)
				board[i][j] = empty;

		}
	}

	~Board()
	{
		for (int i = 0; i < size; i++)
			delete[] board[i];

		delete[] board;
	}

};

class PlayerBoard : public Board
{
public: 

	static const int NO_OF_BATTLESHIPS = { 2 };
	static const int NO_OF_CRUISERS = { 3 };
	static const int NO_OF_DESTROYERS = { 4 };

	Ship** ships;
	int noOfShips;

	void print(); 
	int getShipsCount();
	void placeShips(); 
	bool isPlacementGood(int currentShipID);

	PlayerBoard()
	{
		noOfShips = NO_OF_BATTLESHIPS + NO_OF_CRUISERS + NO_OF_DESTROYERS;

		ships = new Ship* [noOfShips];

		int i = 0;
		for (; i < NO_OF_BATTLESHIPS; i++)
			ships[i] = new Battleship();

		for (; i < NO_OF_BATTLESHIPS + NO_OF_CRUISERS; i++)
			ships[i] = new Cruiser();

		for (; i < noOfShips; i++)
			ships[i] = new Destroyer();

	}

	~PlayerBoard()
	{
		for (int i = 0; i < noOfShips; i++)
			delete[] ships[i];

		delete[] ships;
	}
};

class EnemyBoard : public Board
{
public: 

	void print();
};
