//
//  TileDice.cpp
//
//  A module to represent the dice tiles in the game board.
//
#include "Tile.h"
#include "TileDice.h"
#include "Player.h"

#include <iostream>

using namespace std;

TileDice :: TileDice(unsigned int dice1)
	: Tile()
{
	dice = dice1;
}

TileDice :: TileDice(const TileDice& to_copy)
	: Tile(to_copy)
{
	dice = to_copy.dice; 
}

TileDice :: ~TileDice()
{  
}

TileDice& TileDice :: operator= (const TileDice& to_copy)
{
	if (&to_copy != this)
	{
		Tile :: operator= (to_copy);
		dice = to_copy.dice;
	}

	return *this;
}

Tile* TileDice::getClone() const
{
	Tile* tile_ptr = new TileDice(*(this));    

	return tile_ptr;
}

void TileDice::print() const
{
	printOwnerChar();
	cout << "#";
	cout << dice;
}

void TileDice::activate(unsigned int who_rolled, const CellId& cell, Board& board) const
{
	unsigned int affected_player = getAffectedPlayer(who_rolled);
	playerIncreaseDiceAndPrint(affected_player, dice);
}