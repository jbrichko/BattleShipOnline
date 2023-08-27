#pragma once

#define DEBUG

class Ship
{
public:

	static const int BATTLESHIP_SIZE = { 4 };	//rozmiar statku 
	static const int CRUISER_SIZE = { 3 };		//rozmiar statku
	static const int DESTROYER_SIZE = { 2 };	//rozmiar statku

	static int srandInitCunt; //todo

	enum Orientation : bool						//orientacja statku na mapie - poziomo lub pionowo
	{
		horizontal = true,
		vertical = false,
	};

	const int size;								//d�ugo�� statku
	char* deck;									//informacja o stanie jednego pola statku - ca�y, trafiony i zatopiony

	int locationX, locationY;					//wsp�rz�dne po�o�enia pocz�tku statku
	Orientation orientation;

	bool checkIfSunk();							//funkcja sprawdza czy statek jest ca�y czy zatopiony	jak zwr�ci "true" to statek jest zatopiony

	void randomPlace(int boardSize);			//wylosowanie losowego po�o�enia statku

	Ship(int length);
	~Ship();

};

/*!	\class Ship
*	\brief Jest to klasa, w kt�rej s� przechowywane najwa�niejsze informacje o statkach.
*
*	Klasa ta zawiera wszelkie potrzebne informacje, kt�re s� potrzebne do prawid�owego umieszczenia statku
*	na planszy.
*/


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
