#pragma once

#define DEBUG

#include "Ship.hpp"

class Board
{
public:

	static const int size = { 10 };						//d�ugo�� mapy - sta�a warto�� r�wna 10

	enum FieldStatus : char							//status jednego pola mapy
	{
		empty = '~',
		miss = '*',
		hit = 'H',
		sunk = 'X',
		ship = 'S', 
	}; 

	FieldStatus** board;

	void print(const char* title);					//metoda macierzysta, kt�ra drukuje plansze w terminalu

	Board();
	~Board();
};

class PlayerBoard : public Board					//klasa obs�uguj�ca plansze ze statkami gracza 
{
public: 

	static const int NO_OF_BATTLESHIPS = { 2 };		//ilo�� statk�w danego typu
	static const int NO_OF_CRUISERS = { 3 };		//
	static const int NO_OF_DESTROYERS = { 4 };		//

	Ship** ships;
	int noOfShips;

	void print();									//drukowanie planszy ze statkami gracza
	int getShipsCount();							//liczy ilo�� statk�w niezatopionych gracza
	void placeShips();								//umieszcza staki na planszy
	bool isPlacementGood(int currentShipID);		//sprawdza czy wylosowane wsp�rz�dne s� odpowiednie, by statek si� nie dotyka� z innymi ju� umieszczonymi na planszy

	PlayerBoard(); 
	~PlayerBoard();
};

class EnemyBoard : public Board						//klasa obs�uguj�ca plansze ze statkami wroga (twoje strza�y)
{
public: 

	void print();									//drukowanie planszy ze statkami wroga (twoimi strza�ami) 
};
