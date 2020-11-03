# CXx is a standard variable name used for the compiler
CXX = g++

#CXXFLAGS is a standard variable name for compile flags
#std=c++0x specifies to use a certain language version
CXXFLAGS = -std=c++0x

# -Wall turns on all warnings
CXXFLAGS += -Wall

# pedantic-errors strictly enforces the standard
CXXFLAGS += -pedantic-errors

# -g turns on debug information
CXXFLAGS += -g

####################
### USER SECTION ###
####################

#SRCS is a standard name for the source files
SRC1 = main.cpp
SRC2 = Critter.cpp
SRC3 = Ant.cpp
SRC4 = Doodlebug.cpp
SRC5 = Game.cpp
SRC6 = myUtils.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6}

#HEADERS is a standard name for header files
HEADER1 = Critter.hpp
HEADER2 = Ant.hpp
HEADER3 = Doodlebug.hpp
HEADER4 = Game.hpp
HEADER5 = myUtils.hpp
HEADERS = ${HEADER1} ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5}

#These will be the executable names
PROG1 = main
PROGS = ${PROG1}

#This is the name of the document
#DOC = Lab5MichelleCohen.pdf

#Name of compressed file
TAR = cs162_Lab5_MichelleCohen.tar.bz2 

#####################
### BUILD SECTION ###
#####################

#Typing 'make' in the terminal calls the first build available
#In this case, default.

default:
	${CXX} ${SRCS} ${HEADERS} -o ${PROG1}

#Typing 'make tar' in terminal calls this build
#This creates a compressed file for submission
tar:
	tar cvjf ${TAR} ${SRCS} ${HEADERS} ${DOC} makefile

clean: 
	rm -f ${PROGS} *.o *~

