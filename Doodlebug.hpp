/***************************************************************************
** Program Filename: Doodlebug.hpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the Doodlebug class specification file, the 
** header file that contains the declaration for the Doodlebug class, which
** is a class derived from Critter. This specification includes the
** declaration of the virtual functions move() and breed(), as well as 
** declaration for the member variable keeping track of when doodlebug will
** starve, and function declaration for eating other Critters (Ants)
** Input: N/A
** Output: N/A
***************************************************************************/
#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "myUtils.hpp"
#include "Critter.hpp"

class Doodlebug:public Critter
{
	private:
		int starveClock;

	public:
		Doodlebug();
		void move();
		void eat(Critter*);
		void breed();
		void starve();
		bool checkAnt(); //see if there's an ANT nearby
		bool checkAnt(Direction); //see if there's an Ant in direction given
		/* get and set functions */
		int getStarveClock();
		void setStarveClock(int);
};

#endif		
