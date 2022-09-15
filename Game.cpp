//
//  Game.cpp
//

#include <cassert>
#include <string>
#include <iostream>

#include "Player.h"
#include "BoardSize.h"
#include "CellId.h"
#include "Tile.h"
#include "Board.h"
#include "AvailableTiles.h"
#include "Dice.h"
#include "CellChooser.h"
#include "Game.h"

using namespace std;



Game :: Game ()
	: board(),
	  available()
{
}



void Game :: printState (unsigned int whose_turn) const
{
	assert(whose_turn < playerGetCount());

	board.print();
	cout << endl;
	available.print();
	cout << endl;
	cout << playerGetName(whose_turn) << "'s turn:" << endl;
	cout << endl;
}



void Game :: handleDiceRoll (unsigned int whose_turn)
{
	assert(whose_turn < playerGetCount());

	bool is_extra_die = false;
	if(playerHasDice(whose_turn, 1))
	{
		is_extra_die = true;
		playerDecreaseDice(whose_turn, 1);
	}

	int row1    = diceRoll();
	int row2    = diceRoll();
	int column1 = diceRoll();
	int column2 = diceRoll();
	int extra   = diceRoll();

	if(is_extra_die)
		dicePrint2and2and1(row1, row2, column1, column2, extra);
	else
		dicePrint2and2(row1, row2, column1, column2);
	cout << endl;  // blank line

	// ask player to choose a cell if needed
	CellChooser cell_chooser(row1, row2, column1, column2, extra, is_extra_die);
	if(!cell_chooser.isChosen())
	{
		cell_chooser.printAvailable();

		while(!cell_chooser.isChosen())
		{
			cout << "Choose a cell to roll: ";
			string input;
			getline(cin, input);

			if(isOnBoard(input))
			{
				CellId chosen = toCellId(input);
				if(cell_chooser.isAvailable(chosen))
					cell_chooser.chooseAvailable(chosen);
				else
					cout << "  Cell " << chosen << " is not available" << endl;
			}
			else
				cout << "  Invalid cell" << endl;
		}
	}
	else
		cout << "Rolled cell: " << cell_chooser.getChosen() << endl;

	CellId chosen_cell = cell_chooser.getChosen();
	assert(isOnBoard(chosen_cell));
	(board.getAt(chosen_cell)).activate(whose_turn, chosen_cell, board);    
}

bool Game :: puchaseTile (unsigned int whose_turn)
{
	assert(whose_turn < playerGetCount());

	playerPrint(whose_turn);

	string input;
	cout << "Choose a cell to place a tile: ";
	getline(cin, input);

	if(input == "q")
		return true;  // player wants to quit

	bool is_discard_tile = true;

	if(isOnBoard(input))
	{
		CellId chosen_cell = toCellId(input);
		assert(isOnBoard(chosen_cell));
		if(!board.getAt(chosen_cell).isOwner())
		{
			int tile_index;
			cout << "Choose a tile to buy (by index): ";
			cin >> tile_index;

			cin.clear();  // clean up bad input
			getline(cin, input);  // read to end of line
				
			if(tile_index >= 0 && tile_index < AVAILABLE_TILE_COUNT)
			{
				int cost = available.getCost(tile_index);
				if(playerHasMoney(whose_turn, cost))
				{
					board.setAt(chosen_cell, available.getTile(tile_index), whose_turn);
					playerDecreaseMoney(whose_turn, cost);
					available.replaceAt(tile_index);
					is_discard_tile = false;
					cout << "Success: Tile added" << endl;
				}
				else
					cout << "Failure: Not enough money" << endl;
			}
			else
				cout << "Failure: Invalid tile" << endl;
		}
		else
			cout << "Failure: Cell already has an owner" << endl;
	}
	else
		cout << "Failure: Invalid cell" << endl;

	if(is_discard_tile)
		available.replaceAt(0);

	return false;  // player does not want to quit
}


