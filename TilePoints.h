//
//  TilePoints.h
//
//  A header file to represent the points tiles in the game board.
//
#pragma once

#include "Tile.h"
#include "CellId.h"


class TilePoints : public Tile
{
	public:
		TilePoints(unsigned int points1);
		TilePoints(const TilePoints& to_copy);
		virtual ~TilePoints();
		TilePoints& operator= (const TilePoints& to_copy);

		virtual Tile* getClone() const;
		virtual void activate(unsigned int who_rolled, const CellId& cell, Board& board) const;
		virtual void print() const;

	private:
		unsigned int points; 
};

