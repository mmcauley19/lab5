/***************************************************************************
** Program Filename: Critter.cpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the class implementation file for the Critter
** class. The Critter class is an abstract base class. It does have some
** non virtual functions and member variables common to both derived 
** classes Ant and Doodlebug. Functions include get and set functions, 
** and functions for checking the vicinity of the critter. 
** Input: See member functions
** Output: See member functions
***************************************************************************/

#include "Critter.hpp"
#include "Game.hpp"
#include <iostream>
using namespace std;

/***************************************************************************
** Function: dirPossible(Directon dirIn)
** Description: This is a function to determine if a Critter can move into
** a cell in the given direction- the criteria are that the cell is on the
** board, and that it is empty
** Parameters: Direction
** Pre-conditions: critter on board with known location
** Post-conditions: none
** Return: bool
***************************************************************************/
bool Critter::dirPossible(Direction dirIn)
{
	if (cellExist(dirIn))
		if (checkDirNull(dirIn))
			return true;

	return false;
}

/***************************************************************************
** Function: cellExist(Direction dirIn)
** Description: This function determines if a Cell in the given direction 
** exists on the board. For example, if the Critter is in the top row, 
** cellExist(NORTH) will return false
** Pre-conditions: critter on board with known location
** Post-conditions: none
** Return: bool
***************************************************************************/
bool Critter::cellExist(Direction dirIn)
{
	switch(dirIn)
	{
		case WEST: {
			if ((currCol-1) >= 0)
				return true;
		} break;
		case EAST: {
			if ((currCol+1) < (*theGame).getNumCols())
				return true;
		} break;
		case NORTH: {
			if ((currRow-1) >=0)
				return true;
		} break;
		case SOUTH: {
			if ((currRow+1) < (*theGame).getNumRows())
				return true;
		} break;
	}
	return false;
}

/***************************************************************************
** Function: checkDirNull(Direction dirIn)
** Description: This function determines if a Cell in the given direction 
** is empty. If cell doesn't exist, there will be errors
** Pre-conditions: critter on board with known location, must inspect
** cells that exist only
** Post-conditions: none
** Return: bool
***************************************************************************/
bool Critter::checkDirNull(Direction dirIn) //run cellExist first 
{
		switch(dirIn)
		{
			case WEST: {
				if (!((*theGame).theBoard[currRow][currCol-1]))
					return true;
			} break;
			case EAST: {
				if (!((*theGame).theBoard[currRow][currCol+1])) 
					return true;
			} break;
			case NORTH: {
				if (!((*theGame).theBoard[currRow-1][currCol]))
					return true;
			} break;
			case SOUTH: {
				if (!((*theGame).theBoard[currRow+1][currCol])) 
					return true;
			} 
		}
	return false;
}

/***************************************************************************
** Function: checkSurroundings()
** Description: This function determines if a Critter will be able to move
** or breed at all- will return false if all surrounding cells are full
** Pre-conditions: critter on board with known location
** Post-conditions: none
** Return: bool
***************************************************************************/

bool Critter::checkSurroundings()
{
	if (cellExist(NORTH))
	{
		if (checkDirNull(NORTH))
			return true;
	}
	if (cellExist(EAST))
	{
		if (checkDirNull(EAST))
			return true;
	}
	if (cellExist(SOUTH))
	{
		if (checkDirNull(SOUTH))
			return true;
	}
	if (cellExist(WEST))
	{	
		if (checkDirNull(WEST))
			return true;
	}
	return false;
}

/* standard get/set functions */
int Critter::getCurrRow()
{
	return currRow;
}

void Critter::setAlive(bool aliveIn) /* use to kill critters */
{
	alive = aliveIn;
}

bool Critter::getAlive()
{
	return alive;
}

int Critter::getCurrCol()
{
	return currCol;
}

int Critter::getBreedClock()
{
	return breedClock;
}

void Critter::setBreedClock(int numIn)
{
	breedClock = numIn;
}

void Critter::setGame(Game* gameIn)
{
	theGame = gameIn;
}

void Critter::setLocation(int rowIn, int colIn)
{
	(*theGame).theBoard[rowIn][colIn] = this;
	this->currRow = rowIn;
	this->currCol = colIn;
	
}

BugType Critter::getTypeCritter()
{
	return typeCritter;
}	

	
