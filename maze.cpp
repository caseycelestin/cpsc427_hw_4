#include "maze.hpp"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

//using Maze::tile;
using std::string;
using std::vector;
using std::make_pair;
using std::pair;


namespace cs427_527
{
    Maze::Maze(vector<string> input)
    {
	rows = input.size(); 
	cols = input[0].size();
	count = 0;
	
	fillGrid(input);
	//toString();
    }
 
    Maze::tile::tile(int x, int y, char r)
    {
	xy = make_pair(x, y);
	rule = r;
    }

    Maze::state::state(pair<int, int> loc, vector<int> p, Direction d)
    {
	space = loc;
	parents = p;
	direction = d;
    }

    vector<string> Maze::shortestPath()
    {
	startStates();
	vector<string> temp;
	temp.push_back("temp output");
	return temp;
    }
    
    void Maze::fillGrid(vector<string> in)
    {
	vector<Maze::tile> g;
	int r, c;
	char rul;

	for(int i=0; i < rows*cols; i++)
	{
	    c = i % cols;
	    r = (i - c) / cols;
	    rul = in[r][c];

	    g.push_back(Maze::tile(r, c, rul));
	}

	grid = g;
    }

    void Maze::addToQueue(pair<int, int> new_loc, vector<int> prev, Direction new_d)
    {
	vector<int> index = prev;
	index.push_back(count);
	allPoints.push_back(new_loc);
	count++;
	auto newState = Maze::state(new_loc, index, new_d);
	paths.push(newState);	
    }

    void Maze::startStates()
    {
	vector<int> index;
	for(int i=0; i < cols; i++)
	{
	    addToQueue(make_pair(-1, i), index, S);
	}
	for(int i=0; i < rows; i++)
	{
	    addToQueue(make_pair(i, -1), index, W); 
	}
	for(int i=0; i < cols; i++)
	{
	    addToQueue(make_pair(rows, i), index, N); 
	}
	for(int i=0; i < rows; i++)
	{
	    addToQueue(make_pair(cols, i), index, E); 
	}
    }

    void Maze::toString()
    {
	std::cout << "here" << std::endl;
	for(int i=0; i < rows*cols; i++)
	{
	    if(i != 0 && i % cols ==0) std::cout << std::endl;
	    std::cout << grid[i].rule << " ";
	    
	}
	std::cout << std::endl;
	for(int i=0; i < rows*cols; i++)
	{
	    if(i != 0 && i % cols ==0) std::cout << std::endl;
	    std::cout << grid[i].xy.first << "," << grid[i].xy.second << " ";
	    
	}
	std::cout << std::endl;
    }

}
