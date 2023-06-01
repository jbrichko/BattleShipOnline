#pragma once

#define DEBUG

#include "Ship.hpp"

class Board
{
public:

	static const int size = { 10 };						//d³ugoœæ mapy - sta³a wartoœæ równa 10

	enum FieldStatus : char							//status jednego pola mapy
	{
		empty = '~',
		miss = '*',
		hit = 'H',
		sunk = 'X',
		ship = 'S', 
	}; 

	FieldStatus** board;

	void print(const char* title);					//metoda macierzysta, która drukuje plansze w terminalu

	Board();
	~Board();
};

class PlayerBoard : public Board					//klasa obs³uguj¹ca plansze ze statkami gracza 
{
public: 

	static const int NO_OF_BATTLESHIPS = { 2 };		//iloœæ statków danego typu
	static const int NO_OF_CRUISERS = { 3 };		//
	static const int NO_OF_DESTROYERS = { 4 };		//

	Ship** ships;
	int noOfShips;

	void print();									//drukowanie planszy ze statkami gracza
	int getShipsCount();							//liczy iloœæ statków niezatopionych gracza
	void placeShips();								//umieszcza staki na planszy
	bool isPlacementGood(int currentShipID);		//sprawdza czy wylosowane wspó³rzêdne s¹ odpowiednie, by statek siê nie dotyka³ z innymi ju¿ umieszczonymi na planszy

	PlayerBoard(); 
	~PlayerBoard();
};

class EnemyBoard : public Board						//klasa obs³uguj¹ca plansze ze statkami wroga (twoje strza³y)
{
public: 

	void print();									//drukowanie planszy ze statkami wroga (twoimi strza³ami) 
};
