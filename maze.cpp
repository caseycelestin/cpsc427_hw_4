#include "maze.hpp"

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <sstream>

using std::string;
using std::vector;
using std::make_pair;
using std::pair;
using std::to_string;


namespace cs427_527
{
    Maze::Maze(vector<string> input)
    {
	rows = input.size(); 
	cols = input[0].size();
	count = 0;
	
	fillGrid(input);
    }

    Maze::tile::tile(){}
 
    Maze::tile::tile(int x, int y, char r)
    {
	xy = make_pair(x, y);
	rule = r;
    }

    Maze::state::state(){}

    Maze::state::state(pair<int, int> loc, vector<int> p, Direction d)
    {
	space = loc;
	parents = p;
	direction = d;
    }

    vector<string> Maze::shortestPath()
    {
	startStates();
	if(findPaths())
	{
	    return pathString();
	}
	
	return vector<string>();
    }

    bool Maze::findPaths()
    {
	Maze::state pop;
	Maze::tile space;
	Maze::state newState;
	while(!(paths.empty()))
	{
	    pop = paths.front();
	    
	    if(pop.space.first < 0 || pop.space.first >= rows || pop.space.second < 0 || pop.space.second >= cols)
	    {
		newState = pop.straight();
		if(!(newState.space.first < 0 || newState.space.first >= rows || newState.space.second < 0 || newState.space.second >= cols))
		{
		    addToQueue(newState);
		}

	    }
	    else
	    {
		space = *find_if(grid.begin(), grid.end(), [&pop](Maze::tile t){return pop.space == t.xy;});
		
		switch(space.rule)
		{
		    case '*':
			return true;
		    case 'S':
			newState = pop.straight();
			addToQueue(newState);
			break;
		    case 'L':
			newState = pop.left();
			addToQueue(newState);
			break;
		    case 'R':
			newState = pop.right();
			addToQueue(newState);
			break;
		    case 'U':
			newState = pop.uTurn();
			addToQueue(newState);
			break;
		    case '?':
			newState = pop.straight();
			addToQueue(newState);
			newState = pop.left();
			addToQueue(newState);
			newState = pop.right();
			addToQueue(newState);
			newState = pop.uTurn();
			addToQueue(newState);
			break;
		}
	    }
	    paths.pop();    
	}
	return false;
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

    bool Maze::state::operator==(const state& rhs) const
    {
	return (space == rhs.space && direction == rhs.direction);
    }

    void Maze::addToQueue(Maze::state newState)
    {
	bool check = false;
	for(auto it = allPoints.begin(); it != allPoints.end(); it++)
	{
	    if(newState == *it)
	    {
		check = true;
		break;
	    }
	}
	
	if(!check)
	{
	    newState.parents.push_back(count);
	    allPoints.push_back(newState);
	    count++;
	    paths.push(newState);
	}
    }

    void Maze::startStates()
    {
	vector<int> index;
	for(int i=0; i < cols; i++)
	{
	    addToQueue(Maze::state(make_pair(-1, i), index, S));
	}
	for(int i=0; i < rows; i++)
	{
	    addToQueue(Maze::state(make_pair(i, -1), index, E)); 
	}
	for(int i=0; i < cols; i++)
	{
	    addToQueue(Maze::state(make_pair(rows, i), index, N)); 
	}
	for(int i=0; i < rows; i++)
	{
	    addToQueue(Maze::state(make_pair(i, cols), index, W)); 
	}
    }

    Maze::state Maze::state::straight()
    {
	Maze::state newState = Maze::state(space, parents, direction);
	switch(direction)
	{
	    case N:	
		newState.space.first -= 1;
		break;
	    case W:
		newState.space.second -= 1;
		break;
	    case S:
		newState.space.first += 1;
		break;
	    case E:
		newState.space.second += 1;
		break;
	}
	return newState;
    }

    Maze::state Maze::state::left()
    {
	Maze::state newState = Maze::state(space, parents, direction);
	switch(direction)
	{
	    case N:	
		newState.space.second -= 1;
		newState.direction = W;
		break;
	    case W:
		newState.space.first += 1;
		newState.direction = S;
		break;
	    case S:
		newState.space.second += 1;
		newState.direction = E;
		break;
	    case E:
		newState.space.first -= 1;
		newState.direction = N;
		break;
	}
	return newState;
    }

    Maze::state Maze::state::right()
    {
	Maze::state newState = Maze::state(space, parents, direction);
	switch(direction)
	{
	    case N:	
		newState.space.second += 1;
		newState.direction = E;
		break;
	    case W:
		newState.space.first -= 1;
		newState.direction = N;
		break;
	    case S:
		newState.space.second -= 1;
		newState.direction = W;
		break;
	    case E:
		newState.space.first += 1;
		newState.direction = S;
		break;
	}
	return newState;
    }

    Maze::state Maze::state::uTurn()
    {
	Maze::state newState = Maze::state(space, parents, direction);
	switch(direction)
	{
	    case N:	
		newState.space.first += 1;
		newState.direction = S;
		break;
	    case W:
		newState.space.second += 1;
		newState.direction = E;
		break;
	    case S:
		newState.space.first -= 1;
		newState.direction = N;
		break;
	    case E:
		newState.space.second -= 1;
		newState.direction = W;
		break;
	}
	return newState;
    }

    vector<string> Maze::pathString()
    {
	vector<int> answer = paths.front().parents;
	vector<string> returnString;
	string format;
	
	for(auto it = answer.begin(); it != answer.end(); it++)
	{
	    format = string("(") +  to_string(allPoints[*it].space.first) + string(", ") + to_string(allPoints[*it].space.second) + string(")");
	    returnString.push_back(format);
	}
	return returnString;
    }
}
