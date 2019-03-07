#include "maze.hpp"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

//using Maze::tile;
using std::string;
using std::vector;
using std::make_pair;


namespace cs427_527
{
    Maze::Maze(vector<string> input)
    {
	rows = input.size(); 
	cols = input[0].size();
	
	fillGrid(input);
	toString();
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
    
    Maze::tile::tile(int x, int y, char r)
    {
	xy = make_pair(x, y);
	rule = r;
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
