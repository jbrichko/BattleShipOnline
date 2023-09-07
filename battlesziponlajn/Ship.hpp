#pragma once

/*!	\class Ship
*	\brief Jest to klasa, w kt�rej s� przechowywane najwa�niejsze informacje o statkach.
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
	enum ShipSize : unsigned int
	{
		BATTLESHIP_SIZE = 4,
		CRUISER_SIZE = 3,
		DESTROYER_SIZE = 2,
	};


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
	const ShipSize size;
	
	/**
	*	Informacja o stanie jednego pola statku, czy jest ca�y, trafiony lub zatopiony.
	*/
	char* deck;

	/**
	*	Wsp�rz�dne po�o�enia pocz�tku statku oraz jego orientacja na mapie.
	*/
	int locationX, locationY;
	Orientation orientation;

	/**
	*	\brief Jest to funkcja, kt�ra sprawdza czy dany statek nie zosta� zatopiony.
	*	\return Zwraca jedynk� w przypadku zatopionego statku.
	*/
	bool checkIfSinking();

	/**
	*	\brief Pseudolosowo dobiera wsp�rz�dne po�o�enia pocz�tku statku oraz jego orientacj�.
	*	\param boardSize D�ugo�� boku mapy.
	*/
	void randomPlace(int boardSize);

	/**
	*	\brief Konstruktor obiekt�w klasy Ship.
	*	\param length D�ugo�� statku.
	*/
	Ship(ShipSize length);

	/**
	*	\brief Destruktor obiekt�w klasy Ship.
	*/
	~Ship();

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
