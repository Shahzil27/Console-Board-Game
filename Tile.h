//
//  Tile.h
//
//  A module to represent a tile in the game.  Anything that can
//    occupy a cell of the game board is a tile.
//
//  Each tile has a genus and a species, which are collectively
//    refered to as the tile type.  The genus indicates the
//    overall function of the tile (e.g. a money tile).  The
//    species is the exact type of tile (e.g. a $3 money tile).
//
//  Note that the species values can overlap between genuses.
//    For example, a $1 money tile and a *1 points tile both use
//    a species value of 1.
//
#pragma once
#include "CellId.h"

//struct CellId; 
class Board;



// for money  tiles, the species is the money value
// for dice   tiles, the species is the number of points
// for points tiles, the species is the number of points
// for bomb tiles, there is no species


//
//  Tile
//
//  A class to represent a tile in the game.  Anything that can
//    occupy a cell of the game board is a tile.
//
//
class Tile
{
	public:
		Tile ();
		Tile (const Tile& to_copy);
		virtual ~Tile ();
		Tile& operator= (const Tile& to_copy);
		
		virtual Tile* getClone() const = 0;
		bool isOwner () const;
		unsigned int getAffectedPlayer (unsigned int whose_turn) const;
		void setOwner (unsigned int owner1);
	
		virtual void activate (unsigned int who_rolled, const CellId& rolled_cell, Board& board) const = 0;
		virtual void print () const = 0;

	protected:
		void printOwnerChar () const;

	private:
		unsigned int owner;
};
