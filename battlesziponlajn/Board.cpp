#include "Board.hpp"
#include <iostream>


///	Ogólny szablon planszy. Jest to wzór, który w klasach pochodnych zostanie tak zmodyfikowany
///	by odpowiednio i czytelnie wyświetlane były obie plansze.
void Board::print(const char* title)
{
	///	Formatowanie
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

	shipsRemaining = NO_OF_BATTLESHIPS + NO_OF_CRUISERS + NO_OF_DESTROYERS; 
}

///	Usunięcie z pamięci planszy. Definicja destruktora klasy.
Board::~Board()
{
	for (int i = 0; i < size; i++)
		delete[] board[i];

	delete[] board;
}

///	Wyłuskuje informacje o statku i na ich podstawie modyfikuje planszę gracza.
void PlayerBoard::print()
{
	///	Współrzędne planszy, które będą modyfikowane.
	unsigned int x, y; 

	///	Podwójna pętla, która przechodzi po wszystkich statkach i ich polach i wyłuskuje z nich dane o statku.
	for (unsigned int i = 0; i < noOfShips; i++)
	{
		for (unsigned int j = 0; j < ships[i]->getSize(); j++)
		{
			x = ships[i]->getLocationX() + j * static_cast<int>(ships[i]->getOrientation());
			y = ships[i]->getLocationY() + j * static_cast<int>(!ships[i]->getOrientation());

			board[x][y] = static_cast<FieldStatus>( ships[i]->getDeck(j)); 
		}
	}

	/// Drukowanie planszy ze statkami gracza.
	Board::print("YOUR SHIPS: ");
}

int Board::getSize()
{
	return size; 
}

int Board::getRemainingShips()
{
	return shipsRemaining; 
}

void Board::oneShipLess()
{
	shipsRemaining--;
}

///	Ustawia statki na planszy.
void PlayerBoard::placeShips(void)
{
	///	Pętla for przechodząca po wszystkich dostępnych statkach.
	for (int i = 0; i < noOfShips; i++)
	{
		///	Pętla do-while, która losuje położenie statku do momentu spełnienia warunków 
		///	prawidłowego rozmieszczenia
		do
		{
			ships[i]->randomPlace(size);

		} while (isPlacementGood(i) == false);
	}
}

void PlayerBoard::placeShipsByPlayer()
{
	///	P�tla for przechodz�ca po wszystkich dost�pnych statkach.
	for (int i = 0; i < noOfShips; i++)
	{
		bool firstShipInput = true; 

		print(); 

		///	P�tla do-while, kt�ra losuje po�o�enie statku do momentu spe�nienia warunk�w 
		///	prawid�owego rozmieszczenia
		do
		{
			if (!firstShipInput)
				std::cout << "The ship is overlaping with another one. Try again. \n";

			ships[i]->inputShipCords(size);

			firstShipInput = false; 

		} while (isPlacementGood(i) == false);
	}
}

bool PlayerBoard::isPlacementGood(int currentShipID)
{
	///	Minimalne i maksymalne położenia statku 1 i 2 w obu osiach planszy
	int minX1, maxX1, minX2, maxX2, minY1, maxY1, minY2, maxY2;
	///	Czy statki są odseparowane od siebie w obu osiach planszy.
	bool separatedX, separatedY; 

	///	Przypisanie początkowych wartości dla statku 1.
	minX1 = maxX1 = ships[currentShipID]->getLocationX();
	minY1 = maxY1 = ships[currentShipID]->getLocationY();

#ifdef DEBUG
	std::cout << "placementGood:  id = " << currentShipID << std::endl; 
#endif // DEBUG

	///	Sprawdzenie orientacji
	if (ships[currentShipID]->getOrientation() == Ship::horizontal)
	{
		///	Jeśli pozioma to dodanie długości statku - 1 w celu ustalenia maksymalnego położenia w osi X.
		maxX1 += ships[currentShipID]->getSize() - 1;
	}
	else
	{
		///	Jeśli pozioma to dodanie długości statku - 1 w celu ustalenia maksymalnego położenia w osi Y.
		maxY1 += ships[currentShipID]->getSize() - 1;
	}

	///	Pętla po iterująca po wcześniej położonych statkach.
	for (int i = 0; i < currentShipID; i++)
	{
		///	Przypisanie początkowych wartości dla statku 2.
		minX2 = maxX2 = ships[i]->getLocationX();
		minY2 = maxY2 = ships[i]->getLocationY();

		if (ships[i]->Ship::getOrientation() == Ship::horizontal)
		{
			///	Jeśli pozioma to dodanie długości statku - 1 w celu ustalenia maksymalnego położenia w osi X.
			maxX2 += ships[i]->getSize() - 1;
		}
		else
		{
			///	Jeśli pozioma to dodanie długości statku - 1 w celu ustalenia maksymalnego położenia w osi Y.
			maxY2 += ships[i]->getSize() - 1;
		}

		/// Sprawdzenie w osi X warunku separacji i przypisanie go to tej wartości.
		separatedX = (minX1 <= minX2 && maxX1 + 1 < minX2) || (minX2 < minX1 && maxX2 + 1 < minX1);
		/// Sprawdzenie w osi Y warunku separacji i przypisanie go to tej wartości.
		separatedY = (minY1 <= minY2 && maxY1 + 1 < minY2) || (minY2 < minY1 && maxY2 + 1 < minY1); 

		/// Jeśli w obu osiach są nieodseparowane to położenie nie jest odpowiednie i zwraca false.
		if ( !separatedX && !separatedY ) return false; 
	}

	///	Jeśli wszystkie iteracje się powiodły to zwraca true.
	return true; 
}

void PlayerBoard::checkShotStatus(FieldStatus& status, std::vector<uint8_t>& cordsX, std::vector<uint8_t>& cordsY)
{
	if (cordsX.size() != 1 || cordsY.size() != 1)
	{
		throw std::runtime_error("In checkShotStatus: Bad shot vector size."); 
	} 

	unsigned int shipID = 0;
	int deckID = 0; 

	while (true)
	{
		if (shipID >= noOfShips)
		{
			status = FieldStatus::miss;
			board[cordsX[0]][cordsY[0]] = FieldStatus::miss;

			return;
		}

		if (ships[shipID]->isInShip(deckID, cordsX[0], cordsY[0]) == true)
			break; 

		shipID++; 
	}

	if (ships[shipID]->isHit(deckID) == false)
	{
		status = FieldStatus::miss; 
		cordsX.clear();
		cordsY.clear(); 

		return; 
	}

	if (ships[shipID]->isSinking())
	{
		status = FieldStatus::sunk;
		ships[shipID]->getAllCords(cordsX, cordsY); 

		return; 
	}

	status = FieldStatus::hit;

	return; 
}

///	Domyślny konstruktor klasy PlayerBoard. Tworzone są w nim kolejne obiekty - statki.
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
///	Domyślny destruktor klasy PlayerBoard. Niszczone są w nim stworzone statki.
PlayerBoard::~PlayerBoard()
{
	for (int i = 0; i < noOfShips; i++)
		delete ships[i];

	delete[] ships;
}

///	Drukuje plansze ze strzałami gracza.
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
