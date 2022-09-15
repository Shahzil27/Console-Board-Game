//
//  Board.cpp
//

#include <cassert>
#include <cmath>
#include <iostream>

#include "BoardSize.h"
#include "CellId.h"
#include "Tile.h"
#include "Board.h"

#include "TileMoney.h"   
#include "TileDice.h"
#include "TilePoints.h"

using namespace std;



Board :: Board ()
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			int r2 = abs(r - BOARD_SIZE / 2);
			int c2 = abs(c - BOARD_SIZE / 2);

			int larger = r2;
			if(c2 > r2)
				larger = c2;
			int money = 4 - larger;

			ptr_board[r][c] = new TileMoney(money);              
		}
	}

	assert(isInvariantTrue());
}

Board :: Board (const Board& original)
{
	copyAllTiles(original);

	assert(isInvariantTrue());
}

Board :: ~Board ()
{
	assert(isInvariantTrue());

	deleteAllTiles();
}

Board& Board :: operator= (const Board& original)
{
	assert(isInvariantTrue());
	assert(original.isInvariantTrue());

	if(&original != this)
	{
		deleteAllTiles();
		copyAllTiles(original);
	}

	assert(isInvariantTrue());
	return *this;
}



void Board :: print () const
{
	assert(isInvariantTrue());

	printColumnNameRow();
	printBorderRow();

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		printEmptyRow();
		printDataRow(r);
	}
	printEmptyRow();

	printBorderRow();
	printColumnNameRow();
}

const Tile& Board :: getAt (const CellId& cell_id) const
{
	assert(isInvariantTrue());
	assert(isOnBoard(cell_id));

	return *(ptr_board[cell_id.row][cell_id.column]);
}

void Board :: setAt (const CellId& cell_id,
                     const Tile& value,
                     unsigned int owner)
{
	assert(isInvariantTrue());
	assert(isOnBoard(cell_id));
	assert(!value.isOwner());

	// deallocate existing tile
	assert(ptr_board[cell_id.row][cell_id.column] != NULL);
	delete ptr_board[cell_id.row][cell_id.column];

	// allocate new tile
	const Tile* old_Tile_ptr = value.getClone();                     
	ptr_board[cell_id.row][cell_id.column] = old_Tile_ptr->getClone();   

	ptr_board[cell_id.row][cell_id.column]->setOwner(owner);
	assert(ptr_board[cell_id.row][cell_id.column] != NULL);

	assert(isInvariantTrue());
}



void Board :: printColumnNameRow () const
{
	cout << "    ";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		char label = getColumnName(c);
		cout << "   " << label << " ";
	}
	cout << endl;
}

void Board :: printBorderRow () const
{
	cout << "   +";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << "-----";
	}
	cout << "--+" << endl;
}

void Board :: printEmptyRow () const
{
	cout << "   |";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << "     ";
	}
	cout << "  |" << endl;
}

void Board :: printDataRow (int row) const
{
	assert(row >= 0);
	assert(row <  BOARD_SIZE);

	char label = getRowName(row);
	cout << " " << label << " |";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << "  ";
		ptr_board[row][c]->print();
	}
	cout << "  | " << label << endl;
}

void Board :: deleteAllTiles ()
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			delete ptr_board[r][c];
		}
	}
}

void Board :: copyAllTiles (const Board& original)
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			const Tile* p_original_tile = original.ptr_board[r][c]; 
			ptr_board[r][c] = p_original_tile -> getClone();                  
		}
	}
}

bool Board :: isInvariantTrue () const
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(ptr_board[r][c] == NULL)
				return false;
		}
	}
	return true;
}

