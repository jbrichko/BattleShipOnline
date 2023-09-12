#pragma once

#include <vector>
#include <cinttypes>

#include "Ship.hpp"

/*!	\class Board
*	\brief Jest to klasa, kt�ra jest odpowiedzialna za plansz� gry.
*/
class Board
{
	/**
	*	Klasa ta posiada najwa�niesze informacje o tym co znajduje si� w danym polu planszy oraz
	*	drukuje plansz� w terminalu.
	*/

public:
	/**
	*	\enum FieldStatus
	*	Enumerator opisuj�cy wszystkie mo�liwe opcje jakie mo�e przybra� pole planszy. W danym momencie pole mo�e 
	*	mie� przypisan� tylko jedn� opcj�.
	*/
	enum FieldStatus : char
	{
		empty = '~',
		miss = '*',
		hit = 'H',
		sunk = 'X',
		ship = 'S', 
	}; 

	/**
	*	\brief Drukuje plansz�.
	*	\param title Tytu� danej planszy, "YOUR SHIPS" lub "YOUR SHOTS".
	*	Metoda macierzysta, kt�ra drukuje plansz� w terminalu. Jest rozbudowywana w klasach pochodnych.
	*/
	void print(const char* title);

	static int getSize(); 
	int getRemainingShips();
	void oneShipLess(); 

	/**
	*	Domy�lny konstruktor obiekt�w tej klasy.
	*/
	Board();
	/**
	*	Domy�lny destruktor obiekt�w tej klasy.
	*/
	~Board();

protected: 
	/**
	*	D�ugo�� mapy - sta�a warto�c r�wna 10.
	*/
	static const int size = { 10 };

	/**
	*	Sta�e opisuj�ce ilo�� statk�w danego typu.
	*/
	static const int NO_OF_BATTLESHIPS = { 2 };
	static const int NO_OF_CRUISERS = { 3 };
	static const int NO_OF_DESTROYERS = { 4 };

	/**
	*	Status pola planszy.
	*/
	FieldStatus** board;

	int shipsRemaining;
};


/*!	\class PlayerBoard
*	\brief Jest to pochodna klasy Board. Odpowiada g��wnie za prawid�owe umieszczenie statk�w na planszy.
*/
class PlayerBoard : public Board
{
	/**
	*	Klasa ta umieszcza odpowiada za odpowiednie u�o�enie statk�w na planszy, tj. nie mog� si� na siebie
	*	nak�ada� lub dotyka�. Nast�pnie wedle tego warunku ustawia statki na planszy. W klasie tej jest r�wnie�
	*	metoda, kt�ra zlicza niezatopione statki gracza.
	*/

private: 
	/**
	*	Wska�nik na wska�nik do obiektu klasy Ship.
	*/
	Ship** ships;

	/**
	*	Sumaryczna ilo�� statk�w jednego gracza wraz z zatopionymi.
	*/
	int noOfShips;

	/**
	*	\brief Sprawdza wylosowane wsp�rz�dne i orientacje statku pod k�tem poprawno�ci umieszczenia na planszy.
	*	\param currentShipID Indywidulany numer danego statku.
	*	\return Zwraca "false" w przypadku b��dnego umieszczenia.
	*/
	bool isPlacementGood(int currentShipID);

public: 
	/**
	*	Drukuje w terminalu plansz� ze statkami gracza.
	*/
	void print();

	/**
	*	Umieszcza statki na planszy pseudolosowym po�o�eniu za pomoc� p�tli. Warunkiem dobrego po�o�enia jest 
	*	metoda "isPlacementGood".
	*/
	void placeShips();

	/**
	*	\brief Sprawdza oraz zmienia status planszy po strzale.
	*	\param status Wyjściowy status.
	*	\param cordsX Współrzędna wejściowa X.
	*	\param cordsY Współrzędna wejściowa Y
	*/
	void checkShotStatus(FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY);
	
	/**
	*	\brief Domy�lny konstruktor obiekt�w tej klasy.
	*/
	PlayerBoard();

	/**
	*	\brief Domy�lny destruktor obiekt�w tej klasy.
	*/
	~PlayerBoard();
};

/*!	\class EnemyBoard
*	\brief Jest to pochodna klasy Board. Odpowiada g��wnie za obs�ug� planszy ze statkami wroga - strza�ami gracza.
*/
class EnemyBoard : public Board	
{
public: 

	/**
	*	\brief Drukuje w terminalu plansz� ze statkami wroga - strza�ami gracza.
	*/
	void print(); 

	/**
	*	\brief Zmienia status danego pola planszy.
	*	\param status
	*	\param cordsX
	*	\param cordsY
	*/
	void update(FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY); 
};
