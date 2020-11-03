/***************************************************************************
** Program Filename: Ant.hpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the Ant class specification file, the header
** file that contains the declaration for the Ant class, which is a 
** class derived from Critter. This specification includes the declaration
** of the virtual functions move() and breed()
** Input: N/A
** Output: N/A
***************************************************************************/
#ifndef ANT_HPP
#define ANT_HPP
#include "Critter.hpp"
#include "myUtils.hpp"

//derived class
class Ant:public Critter
{
	public:
		Ant();
		void move();
		void breed();
};

#endif		
