#pragma once

#define DEBUG


/*!	\class Ship
*	\brief Jest to klasa, w której s¹ przechowywane najwa¿niejsze informacje o statkach.
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
	enum ShipSize : int
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
	const ShipSize size;
	
	/**
	*	Informacja o stanie jednego pola statku, czy jest ca³y, trafiony lub zatopiony.
	*/
	char* deck;

	/**
	*	Wspó³rzêdne po³o¿enia pocz¹tku statku oraz jego orientacja na mapie.
	*/
	int locationX, locationY;
	Orientation orientation;

	/**
	*	\brief Jest to funkcja, która sprawdza czy dany statek nie zosta³ zatopiony.
	*	\return Zwraca jedynkê w przypadku zatopionego statku.
	*/
	bool checkIfSunk();

	/**
	*	\brief Pseudolosowo dobiera wspó³rzêdne po³o¿enia pocz¹tku statku oraz jego orientacjê.
	*	\param boardSize D³ugoœæ boku mapy.
	*/
	void randomPlace(int boardSize);

	/**
	*	\brief Konstruktor obiektów klasy Ship.
	*	\param length D³ugoœæ statku.
	*/
	Ship(ShipSize length);

	/**
	*	\brief Dekonstruktor obiektów klasy Ship.
	*/
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
