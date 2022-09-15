//
//  CellId.h
//
//  A module to represent the position of a cell on the game
//    board.  A cell is a place where a tile can be.
//
//  A CellId is not encapsulated.
//
#pragma once

#include <string>



struct CellId
{
	int row;
	int column;
};



//
//  toCellId
//
//  Purpose: To create a CellId for the specified row and
//           column.
//  Parameter(s):
//    <1> row1: The row for the cell
//    <2> column1: The column for the cell
//  Precondition(s): N/A
//  Returns: A CellId for row row and column column.  The CellId
//           may be outside the board.
//  Side Effect: N/A
//
CellId toCellId (int row1, int column1);

//
//  isOnBoard
//
//  Purpose: To determine if the specified position is on the game
//           board.
//  Parameter(s):
//    <1> cell_id: The position to check
//  Precondition(s): N/A
//  Returns: Whether position cell_id is on the game board.
//  Side Effect: N/A
//
bool isOnBoard (const CellId& cell_id);

//
//  isOnBoard
//
//  Purpose: To determine if the specified string represents a
//           cell on the game board.
//  Parameter(s):
//    <1> str: The string to check
//  Precondition(s): N/A
//  Returns: Whether str represents a cell on the game board.
//           If str doesn't represnt a cell at all, this
//           function returns false.
//  Side Effect: N/A
//
bool isOnBoard (const std::string& str);

//
//  toCellId
//
//  Purpose: To convert the specified string to a CellId on the
//           game board.  This function expects the string to be
//           in the same format as the printCellId function.
//  Parameter(s):
//    <1> str: The string to convert
//  Precondition(s):
//    <1> isOnBoard(str)
//  Returns: The CellId corresponding to str.
//  Side Effect: N/A
//
CellId toCellId (const std::string& str);

//
//  Stream Output Operator
//
//  Purpose: To print the specified CellId to the specified
//           output stream.
//  Parameter(s):
//    <1> out: The output stream to print to
//    <2> cell_id: The position to print
//  Precondition(s): N/A
//  Returns: Output stream out.
//  Side Effect: CellId cell_id is printed to out.  The output
//               is always a letter, representing a row,
//               followed by a digit, representing a column.
//
std::ostream& operator<< (std::ostream& out,
                          const CellId& cell_id);

//
//  Equality Test Operator
//
//  Purpose: To determine if the specified CellIds are
//           equivilent.
//  Parameter(s):
//    <1> lhs: The first CellId
//    <2> rhs: The second CellId
//  Precondition(s): N/A
//  Returns: Whether lhs and rhs have the same row and column.
//  Side Effect: N/A
//
bool operator== (const CellId& lhs,
                 const CellId& rhs);

//
//  Less Than Operator
//
//  Purpose: To determine the ordering of the specified
//           CellIds.
//  Parameter(s):
//    <1> lhs: The first CellId
//    <2> rhs: The second CellId
//  Precondition(s): N/A
//  Returns: Whether lhs should be ordered before rhs.  The
//           CellId with the smaller row is ordered first.  If
//           the rows are the same, the CellId with the smaller
//           column is ordered first.  If the columns are also
//           the same, false is returned.
//  Side Effect: N/A
//
bool operator< (const CellId& lhs,
                const CellId& rhs);
