//
//  Tile.cpp
//
//  An abstract super class to represent the tiles in the game board.
//

#include <iostream>

#include "Player.h"
#include "Tile.h"

using namespace std;



const unsigned int NO_OWNER = 999999;



Tile :: Tile ()
{
	owner   = NO_OWNER;
}


Tile::Tile(const Tile& to_copy)
{
	owner = to_copy.owner; 
}

Tile :: ~Tile ()  
{
}

Tile& Tile :: operator= (const Tile& to_copy)
{
	if (&to_copy != this)
	{
		owner = to_copy.owner; 
	}

	return *this; 
}


bool Tile :: isOwner () const
{
	if(owner != NO_OWNER)
		return true;
	else
		return false;
}

unsigned int Tile :: getAffectedPlayer (unsigned int whose_turn) const
{
	if(owner == NO_OWNER)
		return whose_turn;
	else
		return owner;
}

void Tile :: setOwner (unsigned int owner1)
{
	owner = owner1;
}

void Tile :: printOwnerChar () const
{
	if(owner == NO_OWNER)
		cout << ' ';
	else
		cout << playerGetTileChar(owner);
}

