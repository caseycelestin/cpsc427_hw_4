CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Maze: main.o 
	${CXX} ${CXXFLAGS} -o Maze main.o 

main.o:

