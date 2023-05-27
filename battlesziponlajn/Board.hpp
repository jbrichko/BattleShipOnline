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

	Board();
	~Board();
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

	PlayerBoard(); 
	~PlayerBoard();
};

class EnemyBoard : public Board
{
public: 

	void print();
};
