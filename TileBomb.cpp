//
//  TileBomb.cpp
//
//  A module to represent the bomb tiles in the game board.
//
#include "TileBomb.h"
#include "Tile.h"
#include "Board.h"
#include "TileMoney.h"

#include <iostream>

using namespace std;

TileBomb :: TileBomb()
	: Tile()
{
}

TileBomb :: TileBomb(const TileBomb& to_copy)
	: Tile(to_copy)
{
}

TileBomb :: ~TileBomb()
{
}

TileBomb& TileBomb :: operator= (const TileBomb& to_copy)
{
	if (&to_copy != this)
	{
		Tile :: operator= (to_copy);
	}

	return *this;
}

Tile* TileBomb :: getClone() const
{
	Tile* tile_ptr = new TileBomb(*(this));

	return tile_ptr;
}

void TileBomb :: print() const
{
	cout << " Q ";
}

void TileBomb :: activate(unsigned int who_rolled, const CellId& cell, Board& board) const
{
	CellId north_cell = toCellId((cell.row - 1), cell.column);
	CellId south_cell = toCellId((cell.row + 1), cell.column);
	CellId east_cell = toCellId(cell.row, (cell.column + 1));
	CellId west_cell = toCellId(cell.row, (cell.column - 1));

	if (isOnBoard(north_cell))
	{
		board.setAt(north_cell, TileMoney(0), 0);  
	}
	if (isOnBoard(south_cell))
	{
		board.setAt(south_cell, TileMoney(0), 0); 
	}
	if (isOnBoard(east_cell))
	{
		board.setAt(east_cell, TileMoney(0), 0);
	}
	if (isOnBoard(west_cell))
	{
		board.setAt(west_cell, TileMoney(0), 0);
	}

	board.setAt(cell, TileMoney(0), 0);
	
	cout << endl << "  BOOM!" << endl;
	board.print();
}

