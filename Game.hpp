/***************************************************************************
** Program Filename: Game.hpp
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the Game class specification file, the 
** header file that contains the declaration for the Game, which contains 
** a dynamically allocated board (2-d array) of pointers to Critters. 
** Because the Critter, And, and Doodlebug functions require knowledge
** of the board member variable, these classes have been declared friends. 
** Essentially, the Game has a (has many) Critters, and each Critter has 
** the game. Other member variables include dynamically allocated arrays
** of pointers to Ants, and Doodlebugs, which will be used to populate 
** the board. This also contains the declaration of the Game member 
** functions, needed to create the board and play the game and print 
** the results 
** Input: see member functions
** Output: see member functions
***************************************************************************/
#ifndef GAME_HPP
#define GAME_HPP
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include "myUtils.hpp"

class Game
{
	friend class Critter;
	friend class Ant;
	friend class Doodlebug;
	private:
		Ant *ant;
		Critter ***theBoard;
		Ant **antArray;
		Doodlebug *doodlebug;	
		Doodlebug **doodArray;
		int numAnts;
		int numDoods;
		int numRows;
		int numCols;
		int numSteps;
		int priorSteps;

	public:
		Game();
		void run();
		void initialize();
		void playLoop(int);
		void play();
		void print();
		Direction randDir();
		void setNumAnts(int);
		void setNumDoods(int);
		int getNumAnts();
		int getNumDoods();
		int getNumCols();
		int getNumRows();
		
		~Game();
};

#endif


	
