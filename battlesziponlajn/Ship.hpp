#pragma once

#include <vector>

/*!	\class Ship
*	\brief Jest to klasa, w kt�rej s� przechowywane najwa�niejsze informacje o statkach.
*/
class Ship
{
	/**
	*	Klasa ta zawiera wszelkie potrzebne informacje, kt�re s� potrzebne do prawid�owego umieszczenia statku
	*	na planszy.
	*/

public: 

	/**
	*	\enum Ship_size
	*	Enumerator opisuj�cy d�ugo�� statk�w. S� ich trzy rodzaje.
	*/
	enum ShipSize : unsigned int
	{
		BATTLESHIP_SIZE = 4,
		CRUISER_SIZE = 3,
		DESTROYER_SIZE = 2,
	};

	/**
	*	\enum Orientation
	*	Enumerator s�uz�cy do okre�lenia orientacji statku na mapie - poziomo lub pionowo.
	*/
	enum Orientation : bool
	{
		horizontal = true,
		vertical = false,
	};

	/**
	*	\brief Metoda zwracaj�ca wielko�� statku.
	*/
	ShipSize getSize();
	/**
	*	\brief Metoda zwracaj�ca status p�l statku.
	*/
	std::vector<char> getDeck();
	/**
	*	\brief Metoda zwracaj�ca warto�� pola statku.
	*/
	char getDeck(unsigned int position);
	/**
	*	\brief Metoda zwracaj�ca wsp�rz�dn� X.
	*/
	int getLocationX();
	/**
	*	\brief Metoda zwracaj�ca wsp�rz�dn� Y.
	*/
	int getLocationY();
	/**
	*	\brief Metoda zwracaj�ca orientacj� statku..
	*/
	Orientation getOrientation(); 
	/**
	*	\brief Metoda zwracaj�ca przez referencj� warto�ci wsp�rz�dnych.
	*/
	void getAllCords(std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);

	/**
	*	\brief Pseudolosowo dobiera wsp�rz�dne po�o�enia pocz�tku statku oraz jego orientacj�.
	*	\param boardSize D�ugo�� boku mapy.
	*/
	void randomPlace(int boardSize);
	/**
	*	\brief Metoda zwracaj�ca informacj� czy podana wsp�rz�dna znajduje si� w statku.
	*	\param deckID ID danego pola.
	*	\param x Wsp�rz�dna X.
	*	\param y Wsp�rz�dna Y.
	*	\return Zwraca inforamcj� czy w polu o podanych wsp�rz�dnych znajduje si� statek i zmienia warto�� deckID je�li jest to prawda.
	*/
	bool isInShip(int& deckID, unsigned int x, unsigned int y);
	/**
	*	\brief Metoda zmieniaj�ca warto�� pola na Hit.
	*	\param deckID ID danego pola.
	*	\return Przy trafieniu w statek zwraca true.
	*/
	bool isHit(int deckID);
	/**
	*	\brief Jest to funkcja, kt�ra sprawdza czy dany statek nie zosta� zatopiony.
	*	\return Zwraca jedynk� w przypadku zatopionego statku.
	*/
	bool isSinking();

	void inputShipCords(int boardSize);

	/**
	*	\brief Konstruktor obiekt�w klasy Ship.
	*	\param length D�ugo�� statku.
	*/
	Ship(ShipSize length);

private:

	/**
*	D�ugo�� statku.
*/
	const ShipSize size;

	/**
*	Informacja o stanie jednego pola statku, czy jest ca�y, trafiony lub zatopiony.
*/
	std::vector<char> deck; 


	/**
	*	Wsp�rz�dne po�o�enia pocz�tku statku oraz jego orientacja na mapie.
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
	*	Klasa pochodna, kt�ra konstruuje obiekt Ship, ale o d�ugo�ci statku typu: Battleship.
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
	*	Klasa pochodna, kt�ra konstruuje obiekt Ship, ale o d�ugo�ci statku typu: Cruiser.
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
	*	Klasa pochodna, kt�ra konstruuje obiekt Ship, ale o d�ugo�ci statku typu: Destroyer.
	*/

	Destroyer()
		: Ship(DESTROYER_SIZE)
	{
	}
};
