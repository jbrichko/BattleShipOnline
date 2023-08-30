#pragma once

#define DEBUG

#include "Ship.hpp"

/*!	\class Board
*	\brief Jest to klasa, która jest odpowiedzialna za planszê gry.
*/
class Board
{
public:

	/**
	*	Klasa ta posiada najwa¿niesze informacje o tym co znajduje siê w danym polu planszy oraz
	*	drukuje planszê w terminalu.
	*/


	/**
	*	D³ugoœæ mapy - sta³a wartoœc równa 10.
	*/
	static const int size = { 10 };

	/**
	*	\enum FieldStatus
	*	Enumerator opisuj¹cy wszystkie mo¿liwe opcje jakie mo¿e przybraæ pole planszy. W danym momencie pole mo¿e 
	*	mieæ przypisan¹ tylko jedn¹ opcjê.
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
	*	Status pola planszy.
	*/
	FieldStatus** board;

	/**
	*	\brief Drukuje planszê.
	*	\param title Tytu³ danej planszy, "YOUR SHIPS" lub "YOUR SHOTS".
	*	Metoda macierzysta, która drukuje planszê w terminalu. Jest rozbudowywana w klasach pochodnych.
	*/
	void print(const char* title);

	/**
	*	Domyœlny konstruktor obiektów tej klasy.
	*/
	Board();

	/**
	*	Domyœlny dekonstruktor obiektów tej klasy.
	*/
	~Board();
};


/*!	\class PlayerBoard
*	\brief Jest to pochodna klasy Board. Odpowiada g³ównie za prawid³owe umieszczenie statków na planszy.
*/
class PlayerBoard : public Board
{
public: 

	/**
	*	Klasa ta umieszcza odpowiada za odpowiednie u³o¿enie statków na planszy, tj. nie mog¹ siê na siebie
	*	nak³adaæ lub dotykaæ. Nastêpnie wedle tego warunku ustawia statki na planszy. W klasie tej jest równie¿
	*	metoda, która zlicza niezatopione statki gracza.
	*/

	/**
	*	Sta³e opisuj¹ce iloœæ statków danego typu.
	*/
	static const int NO_OF_BATTLESHIPS = { 2 };
	static const int NO_OF_CRUISERS = { 3 };
	static const int NO_OF_DESTROYERS = { 4 };

	/**
	*	WskaŸnik na wskaŸnik do obiektu klasy Ship.
	*/
	Ship** ships;

	/**
	*	Sumaryczna iloœæ statków jednego gracza.
	*/
	int noOfShips;

	/**
	*	Drukuje w terminalu planszê ze statkami gracza.
	*/
	void print();

	/**
	*	\brief Liczy iloœæ niezatopionych statków gracza na planszy.
	*	\return Zwraca liczbê statków niezatopionych.
	*/
	int getShipsCount();

	/**
	*	Umieszcza statki na planszy pseudolosowym po³o¿eniu za pomoc¹ pêtli. Warunkiem dobrego po³o¿enia jest 
	*	metoda "isPlacementGood".
	*/
	void placeShips();

	/**
	*	\brief Sprawdza wylosowane wspó³rzêdne i orientacje statku pod k¹tem poprawnoœci umieszczenia na planszy.
	*	\param currentShipID Indywidulany numer danego statku.
	*	\return Zwraca "false" w przypadku b³êdnego umieszczenia.
	*/
	bool isPlacementGood(int currentShipID);
	
	/**
	*	Domyœlny konstruktor obiektów tej klasy.
	*/
	PlayerBoard();

	/**
	*	Domyœlny dekonstruktor obiektów tej klasy.
	*/
	~PlayerBoard();
};

/*!	\class EnemyBoard
*	\brief Jest to pochodna klasy Board. Odpowiada g³ównie za obs³ugê planszy ze statkami wroga - strza³ami gracza.
*/
class EnemyBoard : public Board	
{
public: 

	/**
	*	Drukuje w terminalu planszê ze statkami wroga - strza³ami gracza.
	*/
	void print(); 
};
