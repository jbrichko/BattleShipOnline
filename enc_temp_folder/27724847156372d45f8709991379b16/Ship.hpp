#pragma once

#define DEBUG

class Ship
{
public:

	static const int BATTLESHIP_SIZE = { 4 };
	static const int CRUISER_SIZE = { 3 };
	static const int DESTROYER_SIZE = { 2 };

	enum Orientation : bool
	{
		horizontal = true,
		vertical = false,
	};

	const int size;
	char* deck;

	int locationX, locationY;
	Orientation orientation;

	bool checkIfSunk();  //zmieniæ nazwê na ma³¹ literê
	void randomPlace(int boardSize); 

	Ship(int length);
	~Ship();

};


class Battleship : public Ship
{
public:

	Battleship()
		: Ship(BATTLESHIP_SIZE)
	{
	}
};

class Cruiser : public Ship
{
public:

	Cruiser()
		: Ship(CRUISER_SIZE)
	{
	}
};

class Destroyer : public Ship
{
public:

	Destroyer()
		: Ship(DESTROYER_SIZE)
	{
	}
};
