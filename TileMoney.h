//
//  TileMoney.h
//
//  A header file to represent the money tiles in the game board.
//
#pragma once
#include "Tile.h"
#include "CellId.h"


class TileMoney : public Tile 
{
	public:
		TileMoney (unsigned int money1);
		TileMoney (const TileMoney& to_copy);
		virtual ~TileMoney ();
		TileMoney& operator= (const TileMoney& to_copy);

		virtual Tile* getClone () const;
		virtual void activate (unsigned int who_rolled, const CellId& cell, Board& board) const;
		virtual void print () const;

	private:
		unsigned int money; 
};
