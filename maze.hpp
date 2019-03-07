#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#include <queue>
#include <vector>
#include <utility>
#include <string>


namespace cs427_527
{
    class Maze
    {
	public:
	    // Constructor for Maze class	   
	    Maze(std::vector<std::string>);
	    // returns deque of strings that is the shortest path 
	    std::deque<std::string> shortestPath();
	    
	    struct tile
	    {
		tile(int x, int y, char r);     
		// Data
		// pair of ints, coordinates of tile
		std::pair<int, int> xy;
		// rule of the tile
		char rule;
	    };

	    struct state
	    {
		// Return vector of next possible states to move
		std::vector<state> nextStates();
		
		// Data
		// Pointer to tile state is on
		tile* space;	
		// Pointer to tile of preceding state
		tile* parent;
		// enum of direction of state
	        enum direction{N = 0, W = 1, S = 2, E = 3};
	    };

	    // Helper funtions
	    // Fill grid from input
	    void fillGrid(std::vector<std::string>);

	    void toString();	  

	private:
	    // Queue holding possible paths
	    std::queue<state> paths;
	    // Vector of grid
	    std::vector<tile> grid;
	    // Row Dimension
	    int rows;
	    // Column Dimension
	    int cols;
    };
}
//#include "maze.cpp"
#endif
