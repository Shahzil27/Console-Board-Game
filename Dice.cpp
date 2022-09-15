//
//  Dice.cpp
//

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Dice.h"

using namespace std;



void diceInit ()
{
	// seed the random number generator with the time
	//  -> you don't have to understand this line
	srand((unsigned int)time(NULL));
}

int diceRoll ()
{
	return rand() % DICE_SIDE_COUNT;
}

void dicePrint2and2 (int r1, int r2, int c1, int c2)
{
	cout << "    Row           Column" << endl;
	cout << "+---+ +---+     +---+ +---+" << endl;
	cout << "| " << r1 << " | | " << r2 << " |     "
	     << "| " << c1 << " | | " << c2 << " |" << endl;
	cout << "+---+ +---+     +---+ +---+" << endl;
}

void dicePrint2and2and1 (int r1, int r2, int c1, int c2, int e1)
{
	cout << "    Row           Column        Extra" << endl;
	cout << "+---+ +---+     +---+ +---+     +---+" << endl;
	cout << "| " << r1 << " | | " << r2 << " |     "
	     << "| " << c1 << " | | " << c2 << " |     "
	     << "| " << e1 << " |" << endl;
	cout << "+---+ +---+     +---+ +---+     +---+" << endl;
}

