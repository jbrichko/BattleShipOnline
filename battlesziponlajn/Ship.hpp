#pragma once

#define DEBUG


/*!	\class Ship
*	\brief Jest to klasa, w której s¹ przechowywane najwa¿niejsze informacje o statkach.
*
*/

class Ship
{
public:

	/**
	*	Klasa ta zawiera wszelkie potrzebne informacje, które s¹ potrzebne do prawid³owego umieszczenia statku
	*	na planszy.
	*/

	/**
	*	\enum Ship_size
	*	Enumerator opisuj¹cy d³ugoœæ statków. S¹ ich trzy rodzaje.
	*/
	enum Ship_size : int
	{
		BATTLESHIP_SIZE = 4,
		CRUISER_SIZE = 3,
		DESTROYER_SIZE = 2,
	};

	//static const int BATTLESHIP_SIZE = { 4 };
	//static const int CRUISER_SIZE = { 3 };
	//static const int DESTROYER_SIZE = { 2 };

	static int srandInitCunt; //todo

	/**
	*	\enum Orientation
	*	Enumerator s³uz¹cy do okreœlenia orientacji statku na mapie - poziomo lub pionowo.
	* 
	*/
	enum Orientation : bool
	{
		horizontal = true,
		vertical = false,
	};

	/**
	*	D³ugoœæ statku.
	*/
	const int size;								//d³ugoœæ statku
	char* deck;									//informacja o stanie jednego pola statku - ca³y, trafiony i zatopiony

	int locationX, locationY;					//wspó³rzêdne po³o¿enia pocz¹tku statku
	Orientation orientation;

	bool checkIfSunk();							//funkcja sprawdza czy statek jest ca³y czy zatopiony	jak zwróci "true" to statek jest zatopiony

	void randomPlace(int boardSize);			//wylosowanie losowego po³o¿enia statku

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
