#pragma once

#include <vector>

/*!	\class Ship
*	\brief Jest to klasa, w której s¹ przechowywane najwa¿niejsze informacje o statkach.
*/
class Ship
{
	/**
	*	Klasa ta zawiera wszelkie potrzebne informacje, które s¹ potrzebne do prawid³owego umieszczenia statku
	*	na planszy.
	*/

public: 

	/**
	*	\enum Ship_size
	*	Enumerator opisuj¹cy d³ugoœæ statków. S¹ ich trzy rodzaje.
	*/
	enum ShipSize : unsigned int
	{
		BATTLESHIP_SIZE = 4,
		CRUISER_SIZE = 3,
		DESTROYER_SIZE = 2,
	};

	/**
	*	\enum Orientation
	*	Enumerator s³uz¹cy do okreœlenia orientacji statku na mapie - poziomo lub pionowo.
	*/
	enum Orientation : bool
	{
		horizontal = true,
		vertical = false,
	};

	ShipSize getSize(); 
	std::vector<char> getDeck(); 
	char getDeck(unsigned int position);
	int getLocationX();
	int getLocationY();
	Orientation getOrientation(); 
	void getAllCords(std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);

	/**
	*	\brief Pseudolosowo dobiera wspó³rzêdne po³o¿enia pocz¹tku statku oraz jego orientacjê.
	*	\param boardSize D³ugoœæ boku mapy.
	*/
	void randomPlace(int boardSize);
	bool isInShip(int& deckID, unsigned int x, unsigned int y); 
	bool isHit(int deckID);
	/**
	*	\brief Jest to funkcja, która sprawdza czy dany statek nie zosta³ zatopiony.
	*	\return Zwraca jedynkê w przypadku zatopionego statku.
	*/
	bool isSinking();

	/**
	*	\brief Konstruktor obiektów klasy Ship.
	*	\param length D³ugoœæ statku.
	*/
	Ship(ShipSize length);

private:

	/**
*	D³ugoœæ statku.
*/
	const ShipSize size;

	/**
*	Informacja o stanie jednego pola statku, czy jest ca³y, trafiony lub zatopiony.
*/
	std::vector<char> deck; 


	/**
	*	Wspó³rzêdne po³o¿enia pocz¹tku statku oraz jego orientacja na mapie.
	*/
	int locationX, locationY;
	Orientation orientation;
};


/*!	\class Battleship
*	\brief Jest to klasa pochodna od klasy Ship. 
*/
class Battleship : public Ship
{
public:

	/**
	*	Klasa pochodna, która konstruuje obiekt Ship, ale o d³ugoœci statku typu: Battleship.
	*/

	Battleship()
		: Ship(BATTLESHIP_SIZE)
	{
	}
};

/*!	\class Cruiser
*	\brief Jest to klasa pochodna od klasy Ship.
*/
class Cruiser : public Ship
{
public:

	/**
	*	Klasa pochodna, która konstruuje obiekt Ship, ale o d³ugoœci statku typu: Cruiser.
	*/

	Cruiser()
		: Ship(CRUISER_SIZE)
	{
	}
};

/*!	\class Destroyer
*	\brief Jest to klasa pochodna od klasy Ship.
*/
class Destroyer : public Ship
{
public:

	/**
	*	Klasa pochodna, która konstruuje obiekt Ship, ale o d³ugoœci statku typu: Destroyer.
	*/

	Destroyer()
		: Ship(DESTROYER_SIZE)
	{
	}
};
