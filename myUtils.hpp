/******************************************************************************
** Author: Michelle Cohen
** Date: October 30, 2016
** Description: This is the specification file for the utility file myUtils
** for general functions with multiple uses in C++
******************************************************************************/
#ifndef MYUTILS_HPP
#define MYUTILS_HPP

#include <string>

//enum Direction definition. Each describes a direction
enum Direction {NORTH, EAST, SOUTH, WEST};

Direction getDir();
Direction getDir(int);
void setPair(int[2]);
int getPosInt();
int getNonNegInt();
void setRandPair(int, int, int, int, int[2]);
bool getYN();
bool inRange(int, int, int);
bool inRange(double, double, double); 
std::string strLower(std::string);

#endif
