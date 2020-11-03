/******************************************************************************
**Author: Michelle Cohen
**Date Last Updated: Oct 31 2016
**Purpose: This is a utility file with general functions for multiple uses in
**C++. More functions should be added over time. 
******************************************************************************/
#include "myUtils.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::srand;
using std::time; 

/******************************************************************************
* getDir() is used to pass in an integer of 0, 1, 2, or 3, and return a 
* Direction type value. Recommended use is for passing in a user-input 
* integer and turning that into a Direction literal
******************************************************************************/
Direction getDir()
{
	int intDir;
	Direction dir;
	cin >> intDir;
	//input validation
	while ( intDir!=0 && intDir!=1 && intDir!=2 && intDir!=3)
	{
		cout << "Not a valid answer, please input 0 1 2 or 3" << endl;
		cin >> intDir;
	}

	switch(intDir)
	{
		case 0: dir=NORTH;
			break;
		case 1: dir=EAST;
			break;
		case 2: dir=SOUTH;
			break;
		case 3: dir=WEST;
			break;
	}
	return dir;
}

Direction getDir(int intIn)
{
	Direction dir;
	//input validation

	switch(intIn)
	{
		case 0: dir=NORTH;
			break;
		case 1: dir=EAST;
			break;
		case 2: dir=SOUTH;
			break;
		case 3: dir=WEST;
			break;
	}
	return dir;
}

/******************************************************************************
* getPosInt() prompts the user for a positive number, and returns this number
* to the program. Note that this abides by the strict definition of a positive
* integer, meaning that 0 is not a valid input 
******************************************************************************/
int getPosInt()
{
	int theInt;
	cin >> theInt;
	while (theInt <= 0)
	{
		cout << "Please enter a positive integer" << endl;
		cin >> theInt;
	}
	return theInt;
}

/******************************************************************************
* getNonNegInt() prompts the user for a number of at least 0 and returns this 
* number to the program. 
******************************************************************************/
int getNonNegInt()
{
	int theInt;
	cin >> theInt;
	while (theInt < 0)
	{
		cout << "Please enter a number 0 or greater " << endl;
		cin >> theInt;
	}
	return theInt;
}


/******************************************************************************
* setPair() reads in 2 numbers from the user and copies them to a predefined
* 2 element array. Especially useful if the user is being asked for x and y 
* coordinates, it's more efficient than grabbing cords one at a time with 
* separate functions. 
******************************************************************************/
void setPair(int arrayIn[2])
{
	int int1, int2;
	cin >> int1 >> int2;
	arrayIn[0]=int1;
	arrayIn[1]=int2;
}
/******************************************************************************
* setRandPair() generates a pair of 2 random numbers using, for each integer,
* 2 input integers...it then reads them into a predefined array. Since it uses
* time(0) as the seed, it's necessary to have a function to populate an array 
* of randoms if the goal is to generate multiple random numbers at the exact 
* same time. Input integers will depend on the desired range... if your min 
* value is 0, that will be the increment, and your max+1 will be the divider.  
******************************************************************************/

void setRandPair(int divider1, int increment1, int divider2, int increment2, int arrayIn[2])
{
	unsigned seed;

	//use time function to get a seed value for srand
	seed  = time(0);
	srand(seed);
	arrayIn[0] = rand()%divider1 + increment1;
	arrayIn[1] = rand()%divider2 + increment2;
}

/******************************************************************************
* getYN() returns true for y or Y, and false for n or N. If invalid values 
* are entered, user will be prompted for input. Useful for having a user 
* answer a yes/no question and making that answer function as a bool. 
******************************************************************************/

bool getYN()
{
	std::string ynIn;
	std::cin >> ynIn;
	char yn;
	yn = ynIn.at(0);
	while ((yn != 'y' && yn != 'Y' && yn != 'n' && yn != 'N') || (ynIn.length() > 1))
	{
		std::cout << "Please enter 'y' or 'n'" << std::endl;
		std::cin >> ynIn;
		yn = ynIn.at(0);
	}
	if (yn == 'y' || yn == 'Y')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/******************************************************************************
* inRange() is an input validation function. It reads three integers, the int
* being tested, and the specified minimum and maximum values these integers 
* are allowed to be, and returns true if int is between the max and min 
* (inclusive) and false if int is not.
******************************************************************************/
bool inRange(int numIn, int min, int max)
{
	bool inRange;
	if (numIn > max || numIn < min)
		inRange=false;
	else if (numIn >= min && numIn <=max)
		inRange=true;
	return inRange;
}

/******************************************************************************
* inRange() this is simply an overloaded function of the original inRange to 
* take double arguments. Note that if the arguments don't each have a decimal
* point, it's possible to get a compiler error or warning
******************************************************************************/
bool inRange(double numIn, double min, double max)
{
	bool inRange;
	if (numIn > max || numIn < min)
		inRange=false;
	else if (numIn >= min && numIn <=max)
		inRange=true;
	return inRange;
}

/******************************************************************************
* strLower() is a function to convert any given string to all lowercase 
* letters, then return it 
******************************************************************************/
std::string strLower(std::string strIn)
{
	for (int i=0; i<strIn.length(); i++)
		strIn[i] = tolower(strIn[i]);
	
	return strIn;
}	
