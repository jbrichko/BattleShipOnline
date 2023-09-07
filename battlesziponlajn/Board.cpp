#include "Board.hpp"
#include <iostream>


///	Ogólny szablon planszy. Jest to wzór, który w klasach pochodnych zostanie tak zmodyfikowany
///	by odpowiednio i czytelnie wyœwietlane by³y obie plansze.
void Board::print(const char* title)
{
	///	Formatowanie
	std::cout << std::endl << std::endl;
	std::cout << "\t" << title << std::endl;
	std::cout << "\t" << "    0  1  2  3  4  5  6  7  8  9" << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "\t" << i << " | ";

		for (int j = 0; j < size; j++)
		{
			std::cout << board[j][i] << "  ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

///	Dynamiczne stworzenie pustej planszy. Definicja konstruktora klasy.
Board::Board()
{
	board = new FieldStatus * [size];

	for (int i = 0; i < size; i++)
	{
		board[i] = new FieldStatus[size];

		for (int j = 0; j < size; j++)
			board[i][j] = empty;
	}
}

///	Usuniêcie z pamiêci planszy. Definicja dekonstruktora klasy.
Board::~Board()
{
	for (int i = 0; i < size; i++)
		delete[] board[i];

	delete[] board;
}

///	Wy³uskuje informacje o statku i na ich podstawie modyfikuje planszê gracza.
void PlayerBoard::print()
{
	///	Wspó³rzêdne planszy, które bêd¹ modyfikowane.
	int x, y; 

	///	Podwójna pêtla, która przechodzi po wszystkich statkach i ich polach i wy³uskuje z nich dane o statku.
	for (int i = 0; i < noOfShips; i++)
	{
		for (int j = 0; j < ships[i]->size; j++)
		{
			x = ships[i]->locationX + j * static_cast<int>(ships[i]->orientation); 
			y = ships[i]->locationY + j * static_cast<int>(!ships[i]->orientation); 

			board[x][y] = static_cast<FieldStatus>( ships[i]->deck[j] ); 
		}
	}

	/// Drukowanie planszy ze statkami gracza.
	Board::print("YOUR SHIPS: ");
}

///	Liczy statki niezatopione.
int PlayerBoard::getShipsCount(void)
{
	/// Pocz¹tkowa iloœæ niezatopionych statków.
	int shipCount = 0;

	///	Pêtla for przechodz¹ca po statkach i sprawdzaj¹ca ich status.
	for (int i = 0; i < noOfShips; i++)
	{
		if (ships[i]->checkIfSinking() == false) shipCount++; 
	}

	///	Zwraca iloœæ statków niezatopionych.
	return shipCount; 
}

bool PlayerBoard::isPlacementGood(int currentShipID)
{
	///	Minimalne i maksymalne po³o¿enia statku 1 i 2 w obu osiach planszy
	int minX1, maxX1, minX2, maxX2, minY1, maxY1, minY2, maxY2;
	///	Czy statki s¹ odseparowane od siebie w obu osiach planszy.
	bool separatedX, separatedY; 

	///	Przypisanie pocz¹tkowych wartoœci dla statku 1.
	minX1 = maxX1 = ships[currentShipID]->locationX;
	minY1 = maxY1 = ships[currentShipID]->locationY;

#ifdef DEBUG
	std::cout << "placementGood:  id = " << currentShipID << std::endl; 
#endif // DEBUG

	///	Sprawdzenie orientacji
	if (ships[currentShipID]->orientation == Ship::horizontal)
	{
		///	Jeœli pozioma to dodanie d³ugoœci statku - 1 w celu ustalenia maksymalnego po³o¿enia w osi X.
		maxX1 += ships[currentShipID]->size - 1;
	}
	else
	{
		///	Jeœli pozioma to dodanie d³ugoœci statku - 1 w celu ustalenia maksymalnego po³o¿enia w osi Y.
		maxY1 += ships[currentShipID]->size - 1;
	}

	///	Pêtla po iteruj¹ca po wczeœniej po³o¿onych statkach.
	for (int i = 0; i < currentShipID; i++)
	{
		///	Przypisanie pocz¹tkowych wartoœci dla statku 2.
		minX2 = maxX2 = ships[i]->locationX;
		minY2 = maxY2 = ships[i]->locationY;

		if (ships[i]->orientation == Ship::horizontal)
		{
			///	Jeœli pozioma to dodanie d³ugoœci statku - 1 w celu ustalenia maksymalnego po³o¿enia w osi X.
			maxX2 += ships[i]->size - 1;
		}
		else
		{
			///	Jeœli pozioma to dodanie d³ugoœci statku - 1 w celu ustalenia maksymalnego po³o¿enia w osi Y.
			maxY2 += ships[i]->size - 1;
		}

		/// Sprawdzenie w osi X warunku separacji i przypisanie go to tej wartoœci.
		separatedX = (minX1 <= minX2 && maxX1 + 1 < minX2) || (minX2 < minX1 && maxX2 + 1 < minX1);
		/// Sprawdzenie w osi Y warunku separacji i przypisanie go to tej wartoœci.
		separatedY = (minY1 <= minY2 && maxY1 + 1 < minY2) || (minY2 < minY1 && maxY2 + 1 < minY1); 

		/// Jeœli w obu osiach s¹ nieodseparowane to po³o¿enie nie jest odpowiednie i zwraca false.
		if ( !separatedX && !separatedY ) return false; 
	}

	///	Jeœli wszystkie iteracje siê powiod³y to zwraca true.
	return true; 
}

///	Ustawia statki na planszy.
void PlayerBoard::placeShips(void)
{
	///	Pêtla for przechodz¹ca po wszystkich dostêpnych statkach.
	for (int i = 0; i < noOfShips; i++)
	{
		///	Pêtla do-while, która losuje po³o¿enie statku do momentu spe³nienia warunków 
		///	prawid³owego rozmieszczenia
		do
		{
			ships[i]->randomPlace(size);

		} while (isPlacementGood(i) == false);
	}
}

void PlayerBoard::checkShotStatus(FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
	if (cordsX.size() != 1 || cordsY.size() != 1)
	{
		std::cerr << "Bad shot size \n"; 
	}

	board[cordsX[0]][cordsY[0]] = FieldStatus::miss; 

	unsigned int hitShipID = 0;
	int hitDeckID = 0; 

	while (true)
	{
		if (hitShipID >= noOfShips)
		{
			status = FieldStatus::miss;

			return;
		}

		if (ships[hitShipID]->orientation == Ship::Orientation::horizontal && ships[hitShipID]->locationY == cordsY[0])
		{
			hitDeckID = static_cast<int>(cordsX[0]) - ships[hitShipID]->locationX;

			if (hitDeckID >= 0 && hitDeckID < ships[hitShipID]->size)
			{
				break; 
			}
		}
		else if (ships[hitShipID]->orientation == Ship::Orientation::vertical && ships[hitShipID]->locationX == cordsX[0])
		{
			hitDeckID = static_cast<int>(cordsY[0]) - ships[hitShipID]->locationY;

			if (hitDeckID >= 0 && hitDeckID < ships[hitShipID]->size)
			{
				break; 
			}
		}

		hitShipID++;
	}

	if (ships[hitShipID]->deck[hitDeckID] != FieldStatus::ship)
	{
		status = FieldStatus::miss; 
		cordsX.clear();
		cordsY.clear(); 

		return; 
	}

	ships[hitShipID]->deck[hitDeckID] = FieldStatus::hit; 

	if (ships[hitShipID]->checkIfSinking())
	{
		status = FieldStatus::sunk;

		cordsX[0] = ships[hitShipID]->locationX;
		cordsY[0] = ships[hitShipID]->locationY; 

		for (unsigned int i = 1; i < ships[hitShipID]->size; i++)
		{
			cordsX.push_back(cordsX[0] + i * static_cast<unsigned int>(ships[hitShipID]->orientation));
			cordsY.push_back(cordsY[0] + i * static_cast<unsigned int>(!ships[hitShipID]->orientation));
		}

		return; 
	}

	status = FieldStatus::hit;

	return; 
}


///	Domyœlny konstruktor klasy PlayerBoard. Tworzone s¹ w nim kolejne obiekty - statki.
PlayerBoard::PlayerBoard()
{
	noOfShips = NO_OF_BATTLESHIPS + NO_OF_CRUISERS + NO_OF_DESTROYERS;

	ships = new Ship* [noOfShips];

	int i = 0;
	for (; i < NO_OF_BATTLESHIPS; i++)
		ships[i] = new Battleship();

	for (; i < NO_OF_BATTLESHIPS + NO_OF_CRUISERS; i++)
		ships[i] = new Cruiser();

	for (; i < noOfShips; i++)
		ships[i] = new Destroyer();

}
///	Domyœlny dekonstruktor klasy PlayerBoard. Niszczone s¹ w nim stworzone statki.
PlayerBoard::~PlayerBoard()
{
	for (int i = 0; i < noOfShips; i++)
		delete ships[i];

	delete[] ships;
}

///	Drukuje plansze ze strza³ami gracza.
void EnemyBoard::print()
{
	Board::print("YOUR SHOTS: ");
}

void EnemyBoard::update(FieldStatus status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
	for (unsigned int i = 0; i < cordsX.size(); i++)
	{
		board[cordsX[i]][cordsY[i]] = status;
	}
}
