/***************************************************************************
** Program Filename: Doodlebug.cpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the class implementation file for the Doodlebug 
** class. The Doodlebug class is a derived class from Critter. It 
** overrides the move() and breed() functions, and also has eat() and 
** starve() functions, to account for eating Ants and starving to death 
** Input: See member functions
** Output: See member functions
***************************************************************************/

#include "Doodlebug.hpp"
#include "Game.hpp"
#include <iostream>
using namespace std;
			
/***************************************************************************
** Function: Doodlebug default constructor
** Description: This is the Doodlebug default constructor, which sets 
** initial values of a few of the member variables
***************************************************************************/
Doodlebug::Doodlebug()
{
	typeCritter = DOODLEBUG;
	starveClock = 3;
	alive=true;
	breedClock=0;
}

/***************************************************************************
** Function: move()
** Description: This is the function for moving instances of Doodlebugs   
** around the board. First the function makes sure theres an adequate spot 
** to move to, meaning an adjacent spot that is either empty or has an Ant.
** Then, the function determines if there is an adjacent Ant available. If 
** so, Doodlebug will move into a spot with an Ant, and eat it. If not,
** Doodlebug will move into an adjacent empty cell. If all adjacent cells 
** are filled with other Doodlebugs, the Doodlebug will stay put. 
** Parameters: None
** Pre-conditions: Doodlebug on board with known location
** Post-conditions: none
** Return: none
***************************************************************************/

void Doodlebug::move()
{
	/* if Doodlebug has an empty adjacent cell, or has adjacent cell with an Ant */
	if ((checkSurroundings()) || checkAnt())
	{
		Direction newDir = (*theGame).randDir();
		if (checkAnt()) /* there's an ant adjacent so make sure to move */
		{								/* into a spot with an Ant */
			while(!(checkAnt(newDir))) //see if cell is on board
			{
				newDir = (*theGame).randDir();
			} 
			switch(newDir)
			{
			case NORTH: 
			{
				eat((*theGame).theBoard[currRow-1][currCol]);
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow-1][currCol] = this;
				currRow -= 1;  }
				break;
			case SOUTH:
			{
				eat((*theGame).theBoard[currRow+1][currCol]);
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow+1][currCol] = this;
				currRow += 1;  }
				break; 
			case EAST:
			{
				eat((*theGame).theBoard[currRow][currCol+1]);
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow][currCol+1] = this;
				currCol += 1;  }
				break;
			case WEST:
			{ 
				eat((*theGame).theBoard[currRow][currCol-1]);
				(*theGame).theBoard[currRow][currCol] = NULL;
				(*theGame).theBoard[currRow][currCol-1] = this;
				currCol -= 1;  }
			break; 
			}
			starveClock=3; //ate an ant, so reset full belly!
		}
		else /* there's no ant available, just go somewhere empty */
		{
			while(!(dirPossible(newDir)))
			{
				newDir = (*theGame).randDir();
			}
			switch(newDir)
			{
				case NORTH: 
				{
					(*theGame).theBoard[currRow][currCol] = NULL;
					(*theGame).theBoard[currRow-1][currCol] = this;
					currRow -= 1;  }
					break;
				case SOUTH:
				{
					(*theGame).theBoard[currRow][currCol] = NULL;
					(*theGame).theBoard[currRow+1][currCol] = this;
					currRow += 1;  }
					break; 
				case EAST:
				{
					(*theGame).theBoard[currRow][currCol] = NULL;
					(*theGame).theBoard[currRow][currCol+1] = this;
					currCol += 1;  }
					break;
				case WEST:
				{
					(*theGame).theBoard[currRow][currCol] = NULL;
					(*theGame).theBoard[currRow][currCol-1] = this;
					currCol -= 1;  }
				//break; 
			}
			starveClock -= 1;  //didn't have a meal this turn, getting hungry
		}
	}
	else
		starveClock -= 1; //didn't move this turn, still needs to count though
}

/***************************************************************************
** Function: breed()
** Description: This is the function for breeding (multiplying) the 
** Doodlebugs, and placing them in adjacent cells to parent. If appropriate,
** a new dynamically allocated Doodlebug will be created and added to the
** doodArray. The doodArray has to be resized when this happens. 
** Parameters: None
** Pre-conditions: Doodlebug has survived 8 timesteps, hasn't breeded in 
** the past 8 timesteps, there's an open cell adjacent to Doodlebug.
** Post-conditions: none
** Return: none
***************************************************************************/
void Doodlebug::breed()
{
	if (breedClock >=8) //if nowhere to go, wait til next time step
	{
		if (checkSurroundings()) 
		{
			Doodlebug *doodlebug = new Doodlebug;
			breedClock=0; //reset breedClock

			/* expand doodlebug array */
			int newSize = (*theGame).getNumDoods()+1;
			Doodlebug** tmp = new Doodlebug*[newSize];
			for (int i=0; i<(newSize-1); i++)
			{
				tmp[i] = (*theGame).doodArray[i];
			}
			tmp[newSize-1] = doodlebug; //add new doodlebug to last spot
			delete [] (*theGame).doodArray;
			(*theGame).doodArray = tmp;

			(*theGame).setNumDoods(newSize);
			(*doodlebug).setGame(theGame); 

			/* now place new Doodlebug randomly */
			Direction newDir = (*theGame).randDir();
			while(!(dirPossible(newDir))) //dir points to an occupied cell
			{
				newDir = (*theGame).randDir();
			} 
			switch(newDir)
			{
				case NORTH: (*doodlebug).setLocation(currRow-1, currCol);
					break;
				case SOUTH: (*doodlebug).setLocation(currRow+1, currCol);
					break;
				case EAST: (*doodlebug).setLocation(currRow, currCol+1);
					break;
				case WEST: (*doodlebug).setLocation(currRow, currCol-1);
					break; 
			}
		}
	}
}	

/***************************************************************************
** Function: checkAnt()
** Description: This function will determine if at least one cell 
** adjacent to the Doodlebug has an Ant. This function is used to determine
** if the Doodlebug move() function should make sure to place the Doodlebug
** in a cell with an Ant, as Doodlebug always chooses a cell with an Ant.
** The function checks each direction, first making sure there is a cell
** in that direction, then seeing if there's something in the cell, then
** returning true if that something is an Ant. 
** over an empty cell
** Parameters: None
** Pre-conditions: doodlebug on the board 
** Post-conditions: none
** Return: bool
***************************************************************************/
bool Doodlebug::checkAnt()
{
	if (cellExist(EAST))           /*make sure not checking outside board */
	{
		if (!(checkDirNull(EAST)))   /*see if there's something in cell */
			if ((*((*theGame).theBoard[currRow][currCol+1])).getTypeCritter() == ANT)
				return true;
	}
	if (cellExist(WEST))
	{
		if (!(checkDirNull(WEST)))
			if ((*((*theGame).theBoard[currRow][currCol-1])).getTypeCritter() == ANT)
				return true;
	}
	if (cellExist(NORTH))
	{
		if (!(checkDirNull(NORTH)))
			if ((*((*theGame).theBoard[currRow-1][currCol])).getTypeCritter() == ANT)
				return true;
	}
	if (cellExist(SOUTH))
	{
		if (!(checkDirNull(SOUTH)))
			if ((*((*theGame).theBoard[currRow+1][currCol])).getTypeCritter() == ANT)
				return true;
	}
	return false;
}

/***************************************************************************
** Function: checkAnt(Direction dirIn)
** Description: This overloads the checkAnt() function to determine if a 
** specific adjacent cell to the Doodlebug has an Ant. This function is 
** used to determine if Doodlebug should move in given direction, if 
** doodlebug knows there is an Ant in some adjacent cell
** Parameters: Direction
** Pre-conditions: doodlebug on the board, should only be run after 
** checkAnt() returns true
** Post-conditions: none
** Return: bool
***************************************************************************/
bool Doodlebug::checkAnt(Direction dirIn)
{	
	switch(dirIn)
	{
		case WEST: {
			if (cellExist(WEST))
			{
				if (!(checkDirNull(WEST)))
					if ((*((*theGame).theBoard[currRow][currCol-1])).getTypeCritter() == ANT)
						return true;
			}
		} break;
		case EAST: {
			if (cellExist(EAST))
			{
				if (!(checkDirNull(EAST)))
					if ((*((*theGame).theBoard[currRow][currCol+1])).getTypeCritter() == ANT)
						return true;
			}
		} break;
		case SOUTH: {
			if (cellExist(SOUTH))
			{
				if (!(checkDirNull(SOUTH)))
					if ((*((*theGame).theBoard[currRow+1][currCol])).getTypeCritter() == ANT)
						return true;
			}
		} break;
		case NORTH: {
			if (cellExist(NORTH))
			{
				if (!(checkDirNull(NORTH)))
					if ((*((*theGame).theBoard[currRow-1][currCol])).getTypeCritter() == ANT)
						return true;
			}
		} break;
	}
	return false;
}

/***************************************************************************
** Function: eat(Critter* antIn)
** Description: This is the function for eating an Ant, all it does is set
** given Ant at specified index of Board to dead, so that further functions
** on Ant will not be run on this Ant, since only live Ants get to move
** and breed. Should be called by doodlebug move() function 
** Parameters: Critter* (index on theBoard)
** Pre-conditions: should have set cell in question to NULL already
** Post-conditions: make sure to set Doodlebug to having just eat
** Return: bool
***************************************************************************/
void Doodlebug::eat(Critter* antIn)
{
	/* loop through all ants, dead or alive */
	for (int i=0; i<((*theGame).getNumAnts()); i++)
	{
		/* find ant that has location we're looking for */
		if ((*antIn).getCurrRow() == (*((*theGame).antArray[i])).getCurrRow())
		{
			if ((*antIn).getCurrCol() == (*((*theGame).antArray[i])).getCurrCol())
			{
				if ((*antIn).getAlive()) //this will also locate dead ants
				{                        //since dead ants stay in ant array
					(*antIn).setAlive(false);
				}
			}
		}
	}
}

/***************************************************************************
** Function: starve() 
** Description: This removes the doodlebug from the board and sets it to 
** dead. It is called when a Doodlebug hasn't eaten for 3 time steps
** Parameters: none
** Pre-conditions: starveClock= 0
** Post-conditions: Make sure move functions are only performed on live 
** doodlebugs
** Return: none
***************************************************************************/
void Doodlebug::starve()
{
	(*theGame).theBoard[currRow][currCol] = NULL;
	setAlive(false);
}
	
/* get function */
int Doodlebug::getStarveClock()
{
	return starveClock;
}
	
