#pragma once

#define DEBUG


/*!	\class Ship
*	\brief Jest to klasa, w kt�rej s� przechowywane najwa�niejsze informacje o statkach.
*
*/

class Ship
{
public:

	/**
	*	Klasa ta zawiera wszelkie potrzebne informacje, kt�re s� potrzebne do prawid�owego umieszczenia statku
	*	na planszy.
	*/

	/**
	*	\enum Ship_size
	*	Enumerator opisuj�cy d�ugo�� statk�w. S� ich trzy rodzaje.
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
	*	Enumerator s�uz�cy do okre�lenia orientacji statku na mapie - poziomo lub pionowo.
	* 
	*/
	enum Orientation : bool
	{
		horizontal = true,
		vertical = false,
	};

	/**
	*	D�ugo�� statku.
	*/
	const int size;								//d�ugo�� statku
	char* deck;									//informacja o stanie jednego pola statku - ca�y, trafiony i zatopiony

	int locationX, locationY;					//wsp�rz�dne po�o�enia pocz�tku statku
	Orientation orientation;

	bool checkIfSunk();							//funkcja sprawdza czy statek jest ca�y czy zatopiony	jak zwr�ci "true" to statek jest zatopiony

	void randomPlace(int boardSize);			//wylosowanie losowego po�o�enia statku

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
