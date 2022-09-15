//
//  Main.cpp
//
//  The main program for Assignment 5.
//
//  Name: Shahzil Siddiqui
//  Student number: 200448986
//

#include <cassert>
#include <string>
#include <iostream>

#include "Dice.h"
#include "Player.h"
#include "Game.h"

using namespace std;

const int POINTS_TO_WIN = 5;



int main ()
{
	// setup

	diceInit();

	string player_names[2] = { "Alice", "Bob" };
	playerInit(2, player_names);

	Game game;

	cout << "Welcome to the game." << endl;

	// run main loop

	unsigned int current_player = 0;
	bool is_quit = false;
	
	do
	{
		cout << endl;
		cout << endl;

		assert(current_player < playerGetCount());
		game.printState(current_player);
		game.handleDiceRoll(current_player);
		cout << endl;

		is_quit = game.puchaseTile(current_player);

		current_player++;
		if(current_player >= playerGetCount())
			current_player = 0;
	}
	while (!is_quit && !playerHasPointsAnyone(POINTS_TO_WIN));

	// print end messages

	cout << endl;
	cout << endl;
	for(unsigned int p = 0; p < playerGetCount(); p++)
	{
		playerPrint(p);
	}
	cout << endl;
	cout << "Thank you for playing!" << endl;

	return 0;  // program exited without crashing
}

