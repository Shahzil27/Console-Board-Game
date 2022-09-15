//
//  CellId.cpp
//

#include <cassert>
#include <string>
#include <iostream>

#include "BoardSize.h"
#include "CellId.h"

using namespace std;



CellId toCellId (int row, int column)
{
	CellId cell_id;
	cell_id.row    = row;
	cell_id.column = column;
	return cell_id;
}

bool isOnBoard (const CellId& cell_id)
{
	if(cell_id.row    >= 0          &&
	   cell_id.row    <  BOARD_SIZE &&
	   cell_id.column >= 0          &&
	   cell_id.column <  BOARD_SIZE)
	{
		return true;
	}
	else
		return false;
}

bool isOnBoard (const std::string& str)
{
	if(str.size() == 2            &&
	   str[0] >= 'A'              &&
	   str[0] <  'A' + BOARD_SIZE &&
	   str[1] >= '0'              &&
	   str[1] <  '0' + BOARD_SIZE)
	{
		return true;
	}
	else
		return false;
}

CellId toCellId (const std::string& str)
{
	assert(isOnBoard(str));

	CellId cell_id;

	assert(0 < str.size());
	assert(str[0] >= 'A');
	assert(str[0] <  'A' + BOARD_SIZE);
	cell_id.row = str[0] - 'A';

	assert(1 < str.size());
	assert(str[1] >= '0');
	assert(str[1] <  '0' + BOARD_SIZE);
	cell_id.column = str[1] - '0';

	assert(isOnBoard(cell_id));  // validate
	return cell_id;
}



ostream& operator<< (ostream& out,
                     const CellId& cell_id)
{
	out << getRowName   (cell_id.row);
	out << getColumnName(cell_id.column);
	return out;
}

bool operator== (const CellId& lhs,
                 const CellId& rhs)
{
	if(lhs.row    == rhs.row &&
	   lhs.column == rhs.column)
	{
		return true;
	}
	else
		return false;
}

bool operator< (const CellId& lhs,
                const CellId& rhs)
{
	if(lhs.row < rhs.row)
		return true;
	if(lhs.row > rhs.row)
		return false;
	if(lhs.column < rhs.column)
		return true;
	if(lhs.column > rhs.column)
		return false;
	// else lhs == rhs
	return false;
}
