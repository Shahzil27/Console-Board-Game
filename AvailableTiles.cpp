//
//  AvailableTiles.cpp
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "Tile.h"
#include "AvailableTiles.h"

#include "TileMoney.h"   
#include "TileDice.h"
#include "TilePoints.h"
#include "TileBomb.h"

using namespace std;

static int allocation_count = 0;
const bool IS_PRINT_ALL_ALLOCATIONS = false;



AvailableTilesElement :: AvailableTilesElement (const Tile& tile1, int cost1)
{
	ptr_tile = tile1.getClone();                  
	cost     = cost1;
	ptr_next = NULL;

	allocation_count++;
	if(IS_PRINT_ALL_ALLOCATIONS)
		cout << "Created element: Now " << allocation_count << " allocated" << endl;

	assert(isInvariantTrue());
}

AvailableTilesElement :: AvailableTilesElement (const AvailableTilesElement& original)
{
	ptr_tile = (original.ptr_tile) -> getClone();     
	cost     = original.cost;
	ptr_next = NULL;

	allocation_count++;
	if(IS_PRINT_ALL_ALLOCATIONS)
		cout << "Copied element: Now " << allocation_count << " allocated" << endl;

	assert(isInvariantTrue());
}

AvailableTilesElement :: ~AvailableTilesElement ()
{
	assert(isInvariantTrue());

	assert(ptr_tile != NULL);
	delete ptr_tile;

	assert(allocation_count >= 1);
	allocation_count--;
	if(IS_PRINT_ALL_ALLOCATIONS)
		cout << "Deleted element: Now " << allocation_count << " allocated" << endl;
	else if(allocation_count <= 0)
		cout << "Now " << allocation_count << " linked list elements allocated" << endl;
	assert(allocation_count >= 0);
}

AvailableTilesElement& AvailableTilesElement :: operator= (const AvailableTilesElement& original)
{
	assert(isInvariantTrue());
	assert(original.isInvariantTrue());

	if(&original != this)
	{
		// from destructor
		assert(ptr_tile != NULL);
		delete ptr_tile;

		// from copy constructor
		ptr_tile = (original.ptr_tile)->getClone();     
		cost     = original.cost;
		ptr_next = NULL;
	}

	// don't change allocation_count

	assert(isInvariantTrue());
	return *this;
}



const Tile& AvailableTilesElement :: getTile() const
{
	assert(isInvariantTrue());

	assert(ptr_tile != NULL);
	return *ptr_tile;
}



bool AvailableTilesElement :: isInvariantTrue () const
{
	if(ptr_tile != NULL)
		return true;
	else
		return false;
}





static void destroyLinkedList (AvailableTilesElement* ptr_element)
{
	while(ptr_element != NULL)
	{
		AvailableTilesElement* ptr_temp = ptr_element;
		ptr_element = ptr_element->ptr_next;
		delete ptr_temp;
	}
}

static AvailableTilesElement* copyLinkedList (const AvailableTilesElement* ptr_old_head)
{
	if(ptr_old_head == NULL)
		return NULL;

	// copy head element
	AvailableTilesElement* ptr_new_head = new AvailableTilesElement(*ptr_old_head);

	const AvailableTilesElement* ptr_old_current = ptr_old_head;
	      AvailableTilesElement* ptr_new_current = ptr_new_head;
	while(ptr_old_current->ptr_next != NULL)
	{
		// copy next element
		ptr_new_current->ptr_next = new AvailableTilesElement(*(ptr_old_current->ptr_next));

		// advance to next element
		ptr_old_current = ptr_old_current->ptr_next;
		ptr_new_current = ptr_new_current->ptr_next;
	}

	// return head of new linked list
	return ptr_new_head;
}





AvailableTiles :: AvailableTiles ()
{
	ptr_head = createRandomTile();
	for(unsigned int i = 1; i < AVAILABLE_TILE_COUNT; i++)
	{
		append(createRandomTile());
	}
}

AvailableTiles :: AvailableTiles (const AvailableTiles& original)
{
	ptr_head = copyLinkedList(original.ptr_head);
}

AvailableTiles :: ~AvailableTiles ()
{
	destroyLinkedList(ptr_head);
}

AvailableTiles& AvailableTiles :: operator= (const AvailableTiles& original)
{
	if(&original != this)
	{
		destroyLinkedList(ptr_head);
		ptr_head = copyLinkedList(original.ptr_head);
	}
	return *this;
}



void AvailableTiles :: print () const
{
	cout << "Available tiles:" << endl;

	unsigned int i = 0;
	for(const AvailableTilesElement* ptr_current = ptr_head;
	    ptr_current != NULL;
	    ptr_current = ptr_current->ptr_next)
	{
		cout << "  " << i << ": ";
		ptr_current->getTile().print();
		cout << "   $" << ptr_current->cost << endl;

		i++;
	}
}

int AvailableTiles :: getCost (unsigned int index) const
{
	assert(index < AVAILABLE_TILE_COUNT);

	assert(ptr_head != NULL);
	const AvailableTilesElement* ptr_current = ptr_head;
	for(unsigned int i = 0; i < index; i++)
	{
		assert(ptr_current != NULL);
		ptr_current = ptr_current->ptr_next;
	}

	assert(ptr_current != NULL);
	return ptr_current->cost;
}

const Tile& AvailableTiles :: getTile (unsigned int index) const
{
	assert(index < AVAILABLE_TILE_COUNT);

	assert(ptr_head != NULL);
	const AvailableTilesElement* ptr_current = ptr_head;
	for(unsigned int i = 0; i < index; i++)
	{
		assert(ptr_current != NULL);
		ptr_current = ptr_current->ptr_next;
	}

	assert(ptr_current != NULL);
	return ptr_current->getTile();
}

void AvailableTiles :: replaceAt (unsigned int index)
{
	assert(index < AVAILABLE_TILE_COUNT);

	assert(ptr_head != NULL);
	if(index == 0)
	{
		// destroy head element
		AvailableTilesElement* ptr_to_destroy = ptr_head;
		ptr_head = ptr_head->ptr_next;
		delete ptr_to_destroy;
	}
	else
	{
		// advance to the correct linked list element
		AvailableTilesElement* ptr_previous = ptr_head;
		AvailableTilesElement* ptr_current  = ptr_head->ptr_next;
		for(unsigned int i = 1; i < index; i++)
		{
			ptr_previous = ptr_current;
			ptr_current  = ptr_current->ptr_next;    
		}

		// destroy the linked list element
		ptr_previous->ptr_next = ptr_current->ptr_next;
		delete ptr_current;
	}

	append(createRandomTile());
}



AvailableTilesElement* AvailableTiles :: createRandomTile () const
{
	unsigned int chosen = rand() % 6;
	if(chosen < 3)
	{
		unsigned int dice1 = 1 + rand() % 2;
		TileDice tile(dice1);                                   
		return new AvailableTilesElement(tile, 5 * dice1);
	}
	else if (chosen > 2 && chosen < 5)
	{
		unsigned int points1 = 1 + rand() % 3;
		TilePoints tile(points1);                                 
		return new AvailableTilesElement(tile, points1 * points1);
	}
	else
	{
		return new AvailableTilesElement(TileBomb(), 8); 
	}
}

void AvailableTiles :: append (AvailableTilesElement* ptr_element)
{
	assert(ptr_head != NULL);
	assert(ptr_element != NULL);
	assert(ptr_element->ptr_next == NULL);

	// find end of linked list
	AvailableTilesElement* ptr_current = ptr_head;
	while(ptr_current->ptr_next != NULL)
	{
		ptr_current = ptr_current->ptr_next;
	}

	// add new element to end of list
	assert(ptr_current != NULL);
	assert(ptr_current->ptr_next == NULL);
	ptr_current->ptr_next = ptr_element;
}

