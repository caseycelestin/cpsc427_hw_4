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
	    std::vector<std::string> shortestPath();
	    
	    struct tile
	    {
		//empty initilizer
		tile();
		// full initializer
		tile(int x, int y, char r);     
		// Data
		// pair of ints, coordinates of tile
		std::pair<int, int> xy;
		// rule of the tile
		char rule;
	    };

	    enum Direction{N, W, S, E};

	    struct state
	    {
		// empty constructor
		state();
		// state constructor
		state(std::pair<int, int> loc, std::vector<int> p, Direction d);

		// state equality operator
		bool operator==(const state& rhs) const;
		
		// Return vector of next possible states to move
		state straight();
		state left();
		state right();
		state uTurn();
		
		// Data
		// coordinates of space
		std::pair<int, int> space;
		// Vector of parent indices
		std::vector<int> parents;
		// enum of direction of state
	        Direction direction;
	    };

	    // Helper funtions
	    // Fill grid from input
	    void fillGrid(std::vector<std::string>);

	    // creates starting states and adds them to queue
	    void startStates();

	    // creates new state and adds to queue
	    void addToQueue(state);
	
	    // Controls BDS
	    bool findPaths();

	    // Outputs answer in correct answer 
	    std::vector<std::string> pathString();

	private:
	    // Queue holding possible paths
	    std::queue<state> paths;
	    // Vector of coord of path points
	    std::vector<state> allPoints;
	    // Counter to keep track of points vector
	    int count;
	    // Vector of grid
	    std::vector<tile> grid;
	    // Row Dimension
	    int rows;
	    // Column Dimension
	    int cols;
    };
}
#include "maze.cpp"
#endif
