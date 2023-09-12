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

	/**
	*	\brief Metoda zwracaj¹ca wielkoœæ statku.
	*/
	ShipSize getSize();
	/**
	*	\brief Metoda zwracaj¹ca status pól statku.
	*/
	std::vector<char> getDeck();
	/**
	*	\brief Metoda zwracaj¹ca wartoœæ pola statku.
	*/
	char getDeck(unsigned int position);
	/**
	*	\brief Metoda zwracaj¹ca wspó³rzêdn¹ X.
	*/
	int getLocationX();
	/**
	*	\brief Metoda zwracaj¹ca wspó³rzêdn¹ Y.
	*/
	int getLocationY();
	/**
	*	\brief Metoda zwracaj¹ca orientacjê statku..
	*/
	Orientation getOrientation(); 
	/**
	*	\brief Metoda zwracaj¹ca przez referencjê wartoœci wspó³rzêdnych.
	*/
	void getAllCords(std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);

	/**
	*	\brief Pseudolosowo dobiera wspó³rzêdne po³o¿enia pocz¹tku statku oraz jego orientacjê.
	*	\param boardSize D³ugoœæ boku mapy.
	*/
	void randomPlace(int boardSize);
	/**
	*	\brief Metoda zwracaj¹ca informacjê czy podana wspó³rzêdna znajduje siê w statku.
	*	\param deckID ID danego pola.
	*	\param x Wspó³rzêdna X.
	*	\param y Wspó³rzêdna Y.
	*	\return Zwraca inforamcjê czy w polu o podanych wspó³rzêdnych znajduje siê statek i zmienia wartoœæ deckID jeœli jest to prawda.
	*/
	bool isInShip(int& deckID, unsigned int x, unsigned int y);
	/**
	*	\brief Metoda zmieniaj¹ca wartoœæ pola na Hit.
	*	\param deckID ID danego pola.
	*	\return Przy trafieniu w statek zwraca true.
	*/
	bool isHit(int deckID);
	/**
	*	\brief Jest to funkcja, która sprawdza czy dany statek nie zosta³ zatopiony.
	*	\return Zwraca jedynkê w przypadku zatopionego statku.
	*/
	bool isSinking();

	void inputShipCords(int boardSize);

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
