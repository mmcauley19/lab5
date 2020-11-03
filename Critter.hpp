/***************************************************************************
** Program Filename: Critter.hpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the Critter class specification file, the header
** file that contains the declaration for the Critter class, which is a 
** abstract base for derived Ant and Doodlebug. This specification includes
** all protected member variables and  including all 
** private variable declarations and functions used by Ants and 
** Doodlebugs, as well as virtual move and breed functions
** Input: N/A
** Output: N/A
***************************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

#include "myUtils.hpp"

class Game; 										/* forward declaration */

enum BugType {ANT, DOODLEBUG}; 	/*represent type of bug*/
class Critter
{
	protected: 
		Game *theGame;              /* used to manipulate board */
		BugType typeCritter;
		int currRow;                /* hold location of critter */
		int currCol;
		bool alive;
		int breedClock;             /* aka biological clock */

	public: 
		virtual void move()=0;      /* pure abstract functions */
		virtual void breed()=0;
		bool checkSurroundings();   /* see if there's an adjacent empty cell */
		bool checkDirNull(Direction); /* just sees if cell is empty */
		bool cellExist(Direction);  /* prevent going outside of bounds */
		bool dirPossible(Direction);
		/* standard get and set */
		void setGame(Game*);
		void setLocation(int, int);
		int getCurrRow();
		int getCurrCol();
		int getBreedClock();
		void setBreedClock(int);
		BugType getTypeCritter();
		void setAlive(bool);
		bool getAlive();
		
};

#endif		
