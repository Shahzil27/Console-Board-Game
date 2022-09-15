//
//  Board.h
//
//  A module to represent the game board.
//
#pragma once

#include "BoardSize.h"
#include "CellId.h"
#include "Tile.h"



//
//  Board
//
//  A class to represent the game board.  A Board behaves as a
//    2D array of Tiles.  When created, the board is filled with
//    unowned money tiles.
//
//  Class Invariant:
//    <1> ptr_tiles[r][c] != NULL
//                                     WHERE 0 <= r < BOARD_SIZE
//                                     WHERE 0 <= c < BOARD_SIZE
//
class Board
{
public:
	Board ();
	Board (const Board& original);
	~Board ();
	Board& operator= (const Board& original);

	void print () const;

	const Tile& getAt (const CellId& cell_id) const;
	void setAt (const CellId& cell_id,
	            const Tile& value,
	            unsigned int owner);

private:
	void printColumnNameRow () const;
	void printBorderRow () const;
	void printEmptyRow () const;
	void printDataRow (int row) const;

	void deleteAllTiles ();
	void copyAllTiles (const Board& original);
	bool isInvariantTrue () const;

private:
	Tile* ptr_board[BOARD_SIZE][BOARD_SIZE];
};



