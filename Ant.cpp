/***************************************************************************
** Program Filename: Ant.cpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the class implementation file for the Ant class. 
** It has the function definitions of the overriden move() and breed()
** functions specific to Ants 
** Input: None
** Output: None
***************************************************************************/
#include "Ant.hpp"
#include "Game.hpp"
#include <iostream>
using namespace std;

/***************************************************************************
** Function: Ant default constructor
** Description: This is the Ant default constructor, which sets initial 
** values of a few of the member variables
***************************************************************************/
Ant::Ant()
{
	typeCritter = ANT;
	alive = true;
	breedClock = 0;
}

/***************************************************************************
** Function: move()
** Description: This is the function for moving instances of Ants around  
** the board. First the function makes sure theres somewhere to move,
** using checkSurroundings(). Then a direction that is open is chosen 
** at random, and the Ant is moved there
** Parameters: None
** Pre-conditions: Ant on board with known location
** Post-conditions: none
** Return: none
***************************************************************************/
void Ant::move()
{
	if (checkSurroundings()) //first make sure there's somewhere to move
	{
		Direction newDir = (*theGame).randDir(); //choose random direction
		
		while(!(dirPossible(newDir))) //while that dir points to an occupied cell
		{
			newDir = (*theGame).randDir();
		} 
		switch(newDir)        /* set current cell to NULL, then       */
		{                     /* set destination cell to Ant,         */
			case NORTH:         /* then adjust location member variable */
			{	
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow-1][currCol] = this;
				currRow -= 1;}
				break;
			case SOUTH:
			{	
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow+1][currCol] = this;
				currRow += 1;}
				break; 
			case EAST:
			{
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow][currCol+1] = this;
				currCol += 1; }
				break;
			case WEST:
			{
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow][currCol-1] = this;
				currCol -= 1; }
				break; 
		}
	} //if there's nowhere to move Ant will stay put
}

/***************************************************************************
** Function: breed()
** Description: This is the function for breeding (multiplying) the Ants,  
** and placing them in adjacent cells to parent. If appropriate, a new 
** dynamically allocated Ant will be created and added to the antArray. 
** The antArray has to be resized when this happens. 
** Parameters: None
** Pre-conditions: Ant survived 3 timesteps, hasn't breeded in the past 3
** timesteps, there's an open cell adjacent to Ant.
** Post-conditions: none
** Return: none
***************************************************************************/
void Ant::breed()
{
	if (breedClock >=3) /* if there's nowhere for young Ant to go, no  */
	{                   /* breeding occurs... try again next timestep  */              
		if (checkSurroundings()) //first make sure there's somewhere to move
		{
			Ant *ant = new Ant;  //create new Ant
			breedClock=0; //reset breedClock, since Ant is breeding

			//expand ant array 
			int newSize = (*theGame).getNumAnts()+1;
			Ant** tmp = new Ant*[newSize];
			for (int i=0; i<(newSize-1); i++)
			{
				tmp[i] = (*theGame).antArray[i];
			}

			tmp[newSize-1] = ant;
			delete [] (*theGame).antArray;
			(*theGame).antArray = tmp;

			(*theGame).setNumAnts(newSize); //reset number of ants

			(*ant).setGame(theGame);        
			Direction newDir = (*theGame).randDir();
		
			/* randomly choose location for young Ant */
			while(!(dirPossible(newDir))) //while that dir points to an occupied cell
			{
				newDir = (*theGame).randDir();
			} 
			switch(newDir)
			{
				case NORTH: (*ant).setLocation(currRow-1, currCol);
					break;
				case SOUTH: (*ant).setLocation(currRow+1, currCol);
					break;
				case EAST: (*ant).setLocation(currRow, currCol+1);
					break;
				case WEST: (*ant).setLocation(currRow, currCol-1);
					break; 
			}
		}
	}
}

	
