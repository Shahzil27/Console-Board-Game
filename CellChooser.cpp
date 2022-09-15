//
//  CellChooser.cpp
//

#include <cassert>
#include <iostream>

#include "BoardSize.h"
#include "CellId.h"
#include "Dice.h"
#include "CellChooser.h"

using namespace std;

const unsigned int NOT_IN_LIST = 999999;



CellChooser :: CellChooser (int row1_roll,
                            int row2_roll,
                            int column1_roll,
                            int column2_roll,
                            int extra_roll,
                            bool is_extra)
{
	assert(row1_roll    >= 0);
	assert(row1_roll    <  DICE_SIDE_COUNT);
	assert(row2_roll    >= 0);
	assert(row2_roll    <  DICE_SIDE_COUNT);
	assert(column1_roll >= 0);
	assert(column1_roll <  DICE_SIDE_COUNT);
	assert(column2_roll >= 0);
	assert(column2_roll <  DICE_SIDE_COUNT);
	assert(extra_roll   >= 0);
	assert(extra_roll   <  DICE_SIDE_COUNT);

	calculateAllAvailable(row1_roll, row2_roll,
	                      column1_roll, column2_roll,
	                      extra_roll, is_extra);

	//insertionSort();
	selectionSort();

	assert(available_count >= 1);
	if(available_count == 1)
	{
		chosen    = available_cells[0];
		is_chosen = true;
	}
	else
		is_chosen = false;

	assert(isInvariantTrue());
}



bool CellChooser :: isChosen () const
{
	assert(isInvariantTrue());

	return is_chosen;
}

CellId CellChooser :: getChosen () const
{
	assert(isInvariantTrue());
	assert(isChosen());

	return chosen;
}

void CellChooser :: printAvailable () const
{
	assert(isInvariantTrue());

	cout << "Available cells:";
	for(unsigned int a = 0; a < available_count; a++)
		cout << "  " << available_cells[a];
	cout << endl;
}



bool CellChooser :: isAvailable (const CellId& cell_id) const
{
	assert(isInvariantTrue());

	//unsigned int index = linearSearch(cell_id);
	unsigned int index = binarySearch(cell_id);

	if(index != NOT_IN_LIST)
		return true;
	else
		return false;
}

void CellChooser :: chooseAvailable (const CellId& cell_id)
{
	assert(isInvariantTrue());
	assert(isAvailable(cell_id));

	chosen    = cell_id;
	is_chosen = true;

	assert(isInvariantTrue());
}

void CellChooser :: addCellIds (const CellId cells[BOARD_CELL_COUNT],
                                unsigned int cell_count)
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < cell_count; i++)
		addAvailableCell(cells[i]);

	//insertionSort();
	selectionSort();

	assert(isInvariantTrue());
}



void CellChooser :: calculateAllAvailable (int row1_roll,
                                           int row2_roll,
                                           int column1_roll,
                                           int column2_roll,
                                           int extra_roll,
                                           bool is_extra)
{
	assert(row1_roll    >= 0);
	assert(row1_roll    <  DICE_SIDE_COUNT);
	assert(row2_roll    >= 0);
	assert(row2_roll    <  DICE_SIDE_COUNT);
	assert(column1_roll >= 0);
	assert(column1_roll <  DICE_SIDE_COUNT);
	assert(column2_roll >= 0);
	assert(column2_roll <  DICE_SIDE_COUNT);
	assert(extra_roll   >= 0);
	assert(extra_roll   <  DICE_SIDE_COUNT);

	available_count = 0;

	// always add the cell without the extra die
	int row_sum    = row1_roll    + row2_roll;
	int column_sum = column1_roll + column2_roll;
	addAvailableCell(toCellId(row_sum, column_sum));

	if(is_extra)
	{
		// if extra die, add up to 4 more cells
		//  -> substitute the extra die for each other die

		int row_sum_r1 = extra_roll + row2_roll;
		addAvailableCell(toCellId(row_sum_r1, column_sum));

		int row_sum_r2 = row1_roll + extra_roll;
		addAvailableCell(toCellId(row_sum_r2, column_sum));

		int column_sum_r1 = extra_roll + column2_roll;
		addAvailableCell(toCellId(row_sum, column_sum_r1));

		int column_sum_r2 = column1_roll + extra_roll;
		addAvailableCell(toCellId(row_sum, column_sum_r2));
	}

	assert(available_count >= 1);
	assert(available_count <= BOARD_CELL_COUNT);
}

void CellChooser :: addAvailableCell (const CellId& cell_id)
{
	assert(isOnBoard(cell_id));

	if(linearSearch(cell_id) == NOT_IN_LIST)
	{
		available_cells[available_count] = cell_id;
		available_count++;
	}
}

unsigned int CellChooser :: linearSearch (const CellId& cell_id) const
{
	for(unsigned int a = 0; a < available_count; a++)
	{
		if(cell_id == available_cells[a])
			return a;
	}
	return NOT_IN_LIST;
}

unsigned int CellChooser :: binarySearch (const CellId& cell_id) const
{
	unsigned int low  = 0;                // inclusive
	unsigned int high = available_count;  // exclusive
	while(low < high)
	{
		unsigned int mid = (low + high) / 2;
		if(cell_id == available_cells[mid])
			return mid;
		else if(cell_id < available_cells[mid])
			high = mid;
		else
			low = mid + 1;
	}

	return NOT_IN_LIST;
}

void CellChooser :: selectionSort ()
{
	assert(available_count <= BOARD_CELL_COUNT);

	for(unsigned int a = 0; a < available_count - 1; a++)
	{
		// find cell next in list
		unsigned int best_index = a;
		for(unsigned int a2 = a + 1; a2 < available_count; a2++)
		{
			if(available_cells[a2] < available_cells[best_index])
				best_index = a2;
		}

		// swap cells
		CellId temp = available_cells[a];
		available_cells[a] = available_cells[best_index];
		available_cells[best_index] = temp;
	}
}

void CellChooser :: insertionSort ()
{
	assert(available_count <= BOARD_CELL_COUNT);

	for(unsigned int a = 1; a < available_count; a++)
	{
		CellId temp = available_cells[a];

		// find where to insert
		int insert_index = a - 1;
		while(insert_index >= 0 && available_cells[a] < available_cells[insert_index])
		{
			insert_index--;
		}

		// shift everything over
		for(int a2 = a; a2 > insert_index; a2--)
		{
			assert(a2 >= 1);
			available_cells[a2] = available_cells[a2 - 1];
		}

		// insert value
		available_cells[insert_index] = temp;
	}
}

bool CellChooser :: isInvariantTrue () const
{
	if(available_count < 1)
		return false;
	if(available_count > BOARD_CELL_COUNT)
		return false;
	for(unsigned int a = 0; a < available_count; a++)
	{
		if(!isOnBoard(available_cells[a]))
			return false;
	}
	for(unsigned int a = 0; a < available_count - 1; a++)
	{
		assert(a + 1 < available_count);
		if(!(available_cells[a] < available_cells[a + 1]))
			return false;
	}

	// all checks successful
	return true;
}

