//
//  TileBomb.h
//
//  A header file to represent the bomb tiles in the game board.
//
#pragma once
#include "Tile.h"



class TileBomb : public Tile 
{
	public: 
		TileBomb();
		TileBomb(const TileBomb& to_copy);
		virtual ~TileBomb();
		TileBomb& operator= (const TileBomb& to_copy);
	
		virtual Tile* getClone() const;
		virtual void activate(unsigned int who_rolled, const CellId& cell, Board& board) const;
		virtual void print() const;
};

