/***************************************************************************
** Program Filename: Game.cpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the class implementation file for the Game class. 
** Game, when run, will prompt the user to initialize size of the board
** and number of ants and doodlebugs and amount of steps, then will run
** the predator-prey simulation, for the specified number of time steps. 
** During each time step, first each Doodlebug will move (if possible), 
** breed (if possible), then die (if necessary). Then each Ant will move,
** then breed (if possible). The board will be printed out at the end of
** the time step.
** Input: See member functions
** Output: See member functions
***************************************************************************/
#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/***************************************************************************
** Function: Game default constructor
** Description: This is just sets the seed for the random number functions.
** values of member variables will be initialized in initialize()
***************************************************************************/
Game::Game()
{
	unsigned seed;
	seed = time(0);
	srand(seed);
}

/***************************************************************************
** Function: run()
** Description: This causes the game to be played, by first calling    
** initialize(), then prompts the user for steps, plays the game, and 
** once steps are used up, will ask user for more steps or to exit.
** Parameters: None
** Pre-conditions: Game instance declared
** Post-conditions: none
** Return: none
***************************************************************************/
void Game::run()
{
	bool more = true;
	priorSteps = 0;
	initialize();  /* set up member variables */
	cout << "This is your starting board:" << endl;
	print();
	
	while(more)
	{
		cout << "How many steps? ";
		numSteps = getPosInt();
		playLoop(numSteps); /* play game, print at each step */
		priorSteps += numSteps; //add steps done 
		cout << "Done. Would you like to keep going?"
				<< "Enter Y for yes or N for no: ";
		more = getYN(); /* will keep going til user says N */
	}
}

/***************************************************************************
** Function: initialize()
** Description: This prompts the user for the number of rows columns ants
** and doodlebugs, running checks to make sure all ants and doodles can be
** placed on the board and prompting user if numbers entered aren't 
** possible. Ants and Doodlebugs are then placed on the board. User is 
** allowed to enter 0 of ants and/or doodlebugs, though this wouldn't be
** very interesting
** Parameters: None
** Pre-conditions: Game instance declared
** Post-conditions: none
** Return: none
***************************************************************************/
void Game::initialize()
{
	cout << "Hello and welcome to a Ant/Doodlebug predator-prey simulation!" << endl
			 << "Since I've done the extra credit, you got to choose the size of\n"
       << "your board, in addition to how many Ants and Doodlebugs to have " << endl;

	/* get rows and columns */
	cout << "How many rows would you like grid to have? ";
	numRows = getPosInt();
	cout << "How many columns would you like the grid to have? ";
	numCols = getPosInt();

	int spaceAvailable = numRows*numCols; /*how many cells are availble */
	
	cout << "How many ants? ";
	numAnts = getNonNegInt();
	while (!(inRange(numAnts,0,spaceAvailable)))
	{	
		cout << "Can't fit that many ants on the board, only have "
         << spaceAvailable << " open cells.\n Give another amount: ";
		numAnts = getNonNegInt();
	}
	cout << "How many doodlebugs? ";
	spaceAvailable -= numAnts;
	numDoods = getNonNegInt();

	while (!(inRange(numDoods,0,spaceAvailable)))
	{	
		cout << "Can't fit that many doodlebugs on the board, only have "
         << spaceAvailable << " open cells. \nGive another amount: ";
		numDoods = getNonNegInt();
	}

	//create board
	theBoard = new Critter **[numRows];
	for (int i=0; i<numRows; i++)
		theBoard[i] = new Critter*[numCols];

	//set each to NULL
	for (int i=0; i<numRows; i++) 
		for (int j=0; j<numCols; j++) 
			theBoard[i][j] = NULL;

	//place ants on board, randomly
	antArray = new Ant*[numAnts];
	int randRow, randCol;
	for (int i=0; i < numAnts; i++)
	{
		ant = new Ant;
		(*ant).setGame(this);
		randRow = rand()%numRows;
		randCol = rand()%numCols;

		//if cell is full, get a new cell
		while(theBoard[randRow][randCol])
		{
			randRow = rand()%numRows;
			randCol = rand()%numCols;
		}
		(*ant).setLocation(randRow, randCol);
		antArray[i] = ant; //add to antArray
	}
			
	//place doodlebugs on board	
	doodArray = new Doodlebug*[numDoods];
	for (int i=0; i < numDoods; i++)
	{
		doodlebug = new Doodlebug;
		(*doodlebug).setGame(this);
		randRow = rand()%numRows;
		randCol = rand()%numCols;
		//if full, reset
		while(theBoard[randRow][randCol])
		{
			randRow = rand()%numRows;
			randCol = rand()%numCols;
		}
		(*doodlebug).setLocation(randRow,randCol);
		doodArray[i] = doodlebug; //add to doodArray
	}
}

/***************************************************************************
** Function: playLoop()
** Description: This will play the game for the specified amount of steps,
** printing after each step
** Parameters: int stepsIn
** Pre-conditions: intialize() run
** Post-conditions: none
** Return: none
***************************************************************************/
void Game::playLoop(int stepsIn)
{
	for (int i=1; i<=stepsIn; i++)
	{
		cout << "step " << (i+priorSteps) << ":" << endl;
		play();
		print();
		cout << endl;
	}
}

/***************************************************************************
** Function: play()
** Description: This will play the game for one time step, first looping  
** through each doodlebug and performing the move/ breed/ starve functions
** (when valid), then looping through each ant and performing the
** move/breed functions (when valid)
** Parameters: none
** Pre-conditions: intialize() run
** Post-conditions: none
** Return: none
***************************************************************************/
void Game::play()
{
	int clock; /* local variable for holding value */

	/* first take care of all the doodlebugs */
	for (int i=0; i<numDoods; i++)
	{
		//doodlebug will breed (if possible) before starving to death, 
		//following a similar route to salmon
		if ((*doodArray[i]).getAlive())   /* only act on living doodles! */
		{
			(*(doodArray[i])).move();    /*eat called by move when applicable*/
			clock = (*(doodArray[i])).getBreedClock(); /*give doodlebug credit */
			clock+=1;                                 /*for surviving this long*/
			(*(doodArray[i])).setBreedClock(clock);
			(*(doodArray[i])).breed();    /*try to breed*/
			if ((*(doodArray[i])).getStarveClock() == 0) 
			{                             /*if time to starve, die */
				(*(doodArray[i])).starve();
			}
		}
	}

	/* now loop through the ants */
	for (int i=0; i<numAnts; i++)
	{
		if ((*(antArray[i])).getAlive()) /*only act on live ants */
		{
			(*(antArray[i])).move();      /* move if possible */     
			clock = (*(antArray[i])).getBreedClock();
			clock+=1;              /* credit for surviving round */  
			(*(antArray[i])).setBreedClock(clock);
			(*(antArray[i])).breed();  /* breed if possible */
		} 
	}
}

/***************************************************************************
** Function: print()
** Description: This will print the game by looping through theBoard and 
** printing O if there's ant, X if there's a doodlebug, and E if a cell
** is empty. Recommended setting: blank space or "_" for empty cell 
** Parameters: none
** Pre-conditions: intialize() run
** Post-conditions: none
** Return: none
***************************************************************************/
void Game::print()
{
	for (int i=0; i<numRows; i++)
	{
		for (int j=0; j<numCols; j++)
		{
			if (!(theBoard[i][j]))  /* recommend printing '.' instead */
				cout << "."; 
			else if ((*(theBoard[i][j])).getTypeCritter() == ANT)
				cout << "O";
			else if ((*(theBoard[i][j])).getTypeCritter() == DOODLEBUG)
				cout << "X";
			else            /* should not be reached, sign of an error */
				cout << ".";
		}
		cout << endl;
	}
}

/***************************************************************************
** Function: randDir()
** Description: Random direction generator. Computes random number from 0
** to 3, then returns corresponding Direction per Direction enumerated data
** type. 
** Pre-conditions: have seed set (set in Game constructor)
** Post-conditions: none
** Return: none
***************************************************************************/
Direction Game::randDir()
{
	int randIndex;
	randIndex=rand()%4;
	Direction dirOut;
	dirOut = getDir(randIndex);
	return dirOut;
}

/* standard get/ set function */
void Game::setNumAnts(int intIn)
{
	numAnts = intIn;
}

void Game::setNumDoods(int intIn)
{
	numDoods = intIn;
}

int Game::getNumAnts()
{
	return numAnts;
}

int Game::getNumDoods()
{
	return numDoods;
}

int Game::getNumCols()
{
	return numCols;
}

int Game::getNumRows()
{
	return numRows;
}

/* Game class destructor. deletes all instances */
/* of Ants and Doudlebugs, frees memory         */
/* allocated for theBoard                       */
Game::~Game()
{
	for (int i=0; i< numAnts; i++)
	{
		delete antArray[i];
	} 
	delete[] antArray;
	
	for (int i=0; i< numDoods; i++)
	{
		delete doodArray[i];
	}
	delete[] doodArray;

	for (int i=0; i<numRows; i++)  
	{
		delete[] theBoard[i];
	}	
	delete[] theBoard; 
}


