//
//  Game.h
//
//  A module to represent the complete state of the game.
//
#pragma once

#include <string>

#include "BoardSize.h"
#include "CellId.h"
#include "Tile.h"
#include "Board.h"
#include "AvailableTiles.h"



//
//  Game
//
//  A class to represent the complete state of the game.
//
class Game
{
public:
	Game ();
	void printState (unsigned int whose_turn) const;
	void handleDiceRoll (unsigned int whose_turn);
	bool puchaseTile (unsigned int whose_turn);

private:
	Board board;
	AvailableTiles available;
};

