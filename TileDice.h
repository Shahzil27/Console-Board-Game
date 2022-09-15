//
//  TileDice.h
//
//  A header file to represent the dice tiles in the game board.
//
#pragma once

#include "Tile.h"
#include "CellId.h"


class TileDice : public Tile
{
	public:
		TileDice(unsigned int dice1);
		TileDice(const TileDice& to_copy);
		virtual ~TileDice();
		TileDice& operator=(const TileDice& to_copy);

		virtual Tile* getClone() const;
		virtual void activate(unsigned int who_rolled, const CellId& cell, Board& board) const;
		virtual void print() const;

	private:
		unsigned int dice; 
};
