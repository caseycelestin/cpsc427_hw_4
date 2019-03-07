CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Maze: main.o maze.o
	${CXX} ${CXXFLAGS} -o Maze main.o maze.o

main.o:

maze.o:

