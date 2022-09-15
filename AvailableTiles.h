//
//  AvailableTiles.h
//
//  A module to keep track of the tiles are available to buy.
//
#pragma once

#include "Tile.h"



const unsigned int AVAILABLE_TILE_COUNT = 5;



//
//  AvailableTilesElement
//
//  A class to represent a single element of the linked list.
//
//  This class is partially encapsulated.  Specifically, the
//    Tile is managed automatically and only accessible through
//    the getTile function.  The other members, including the
//    next pointer, are publically available.  The Tile will be
//    automatically deleted by this class, but the next element
//    in the linked list will not be.
//
class AvailableTilesElement
{
public:
	AvailableTilesElement (const Tile& tile1, int cost1);
	AvailableTilesElement (const AvailableTilesElement& original);
	~AvailableTilesElement ();
	AvailableTilesElement& operator= (const AvailableTilesElement& original);

	const Tile& getTile() const;

private:
	bool isInvariantTrue () const;

private:
	Tile* ptr_tile;
public:
	int cost;
	AvailableTilesElement* ptr_next;
};



//
//  AvailableTiles
//
//  A class to keep track of which tiles are available to buy
//    and their costs.
//
class AvailableTiles
{
public:
//
//  Default Constructor
//
//  Purpose: To create an AvailableTiles containing random
//           tiles.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new AvailableTiles is created.  Each tile is
//               chosen randomly.
//
	AvailableTiles ();

	AvailableTiles (const AvailableTiles& original);
	~AvailableTiles ();
	AvailableTiles& operator= (const AvailableTiles& original);

//
//  print
//
//  Purpose: To list the tiles for this AvailableTiles.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The tiles are printed, along with their indexes
//               and costs.
//
	void print () const;

//
//  getCost
//
//  Purpose: To determine the cost of the specified tile.
//  Parameter(s):
//    <1> index: Which tile
//  Precondition(s):
//    <1> index < AVAILABLE_TILE_COUNT
//  Returns: The cost of the tile with index index.
//  Side Effect: N/A
//
	int getCost (unsigned int index) const;

//
//  getTile
//
//  Purpose: To retreive the specified tile.
//  Parameter(s):
//    <1> index: Which tile
//  Precondition(s):
//    <1> index < AVAILABLE_TILE_COUNT
//  Returns: The tile with index index.
//  Side Effect: N/A
//
	const Tile& getTile (unsigned int index) const;

//
//  replaceAt
//
//  Purpose: To replace the specified tile with a random new
//           tile.
//  Parameter(s):
//    <1> index: Which tile
//  Precondition(s):
//    <1> index < AVAILABLE_TILE_COUNT
//  Returns: N/A
//  Side Effect: The tile with index index is removed from this
//               AvailableTiles.  The tiles with higher indexes
//               are moved down to fill the gap.  Then a random
//               new tile is added at the end.
//
	void replaceAt (unsigned int index);

private:
	AvailableTilesElement* createRandomTile () const;
	void append (AvailableTilesElement* ptr_element);

private:
	AvailableTilesElement* ptr_head;
};
