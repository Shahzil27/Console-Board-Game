//
//  TilePoints.cpp
//
//  A module to represent the points tiles in the game board.
//
#include "Tile.h"
#include "TilePoints.h"
#include "Player.h"

#include <iostream>

using namespace std;

TilePoints :: TilePoints(unsigned int points1)
	: Tile()
{
	points = points1;
}

TilePoints:: TilePoints(const TilePoints& to_copy)
	: Tile(to_copy)
{
	points = to_copy.points;
}

TilePoints :: ~TilePoints()
{
}

TilePoints& TilePoints :: operator= (const TilePoints& to_copy)
{
	if (&to_copy != this)
	{
		Tile :: operator= (to_copy);
		points = to_copy.points;
	}

	return *this;
}

Tile* TilePoints::getClone() const
{
	Tile* tile_ptr = new TilePoints(*(this));    

	return tile_ptr;
}

void TilePoints::print() const
{
	printOwnerChar();
	cout << "*";
	cout << points;
}

void TilePoints::activate(unsigned int who_rolled, const CellId& cell, Board& board) const
{
	unsigned int affected_player = getAffectedPlayer(who_rolled);
	playerIncreasePointsAndPrint(affected_player, points);
}