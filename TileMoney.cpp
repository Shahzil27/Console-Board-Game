//
//  TileMoney.cpp
//
//  A module to represent the money tiles in the game board.
//
#include "Tile.h"
#include "TileMoney.h"
#include "Player.h"

#include <iostream>

using namespace std; 

TileMoney :: TileMoney (unsigned int money1)
	: Tile ()
{
	money = money1; 
}

TileMoney :: TileMoney (const TileMoney& to_copy)
	: Tile (to_copy)
{
	money = to_copy.money; 
}

TileMoney :: ~TileMoney()
{  
}

TileMoney& TileMoney :: operator= (const TileMoney& to_copy)
{
	if (&to_copy != this)
	{
		Tile :: operator= (to_copy); 
		money = to_copy.money;
	}

	return *this;
}

Tile* TileMoney :: getClone() const
{
	Tile* tile_ptr = new TileMoney(*(this));    

	return tile_ptr; 
}

void TileMoney :: print() const
{
	printOwnerChar(); 
	cout << "$";
	cout << money;
}

void TileMoney :: activate(unsigned int who_rolled, const CellId& cell, Board& board) const
{
	unsigned int affected_player = getAffectedPlayer(who_rolled);
	playerIncreaseMoneyAndPrint(affected_player, money);
}