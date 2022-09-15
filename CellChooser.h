//
//  CellChooser.h
//
//  A module to handle rolling dice and choosing 4 to represent
//    a cell.
//
#pragma once

#include "BoardSize.h"
#include "CellId.h"



//
//  CellChooser
//
//  A class to handle rolling dice and choosing 4 to represent
//    a cell.  There are  always 2 row dice and 2 column dice
//    rolled, and there may be up to EXTRA_DICE_MAX extra dice
//    rolled as well.
//
//  To make the row position, any 2 of row and extra dice are
//    added.  The column position is made similarly.  However,
//    each extra die may only be used once.  A list is made of
//    all possible cells that can be re[resented with the dice.
//    Then the list is displayed and the player chooses one.
//
//  Class Invariant:
//    <1> available_count >= 1
//    <2> available_count <= BOARD_CELL_COUNT
//    <3> chosen == NOTHING_CHOSEN || chosen < available_count
//
class CellChooser
{
public:
	CellChooser (int row1_roll,
	             int row2_roll,
	             int column1_roll,
	             int column2_roll,
	             int extra_roll,
	             bool is_extra);

	bool isChosen () const;
	CellId getChosen () const;
	void printAvailable () const;
	bool isAvailable (const CellId& cell_id) const;
	void chooseAvailable (const CellId& cell_id);
	void addCellIds (const CellId cells[BOARD_CELL_COUNT],
	                 unsigned int cell_count);

private:
	void calculateAllAvailable (int row1_roll,
	                            int row2_roll,
	                            int column1_roll,
	                            int column2_roll,
	                            int extra_roll,
	                            bool is_extra);
	void addAvailableCell (const CellId& cell_id);
	unsigned int linearSearch (const CellId& cell_id) const;
	unsigned int binarySearch (const CellId& cell_id) const;
	void selectionSort ();
	void insertionSort ();
	bool isInvariantTrue () const;

private:
	CellId available_cells[BOARD_CELL_COUNT];
	unsigned int available_count;
	CellId chosen;
	bool is_chosen;
};


