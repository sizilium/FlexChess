#include "Rules.h"

#include <iostream>


Rules::Rules()
{
}

Rules::~Rules()
{
}

bool Rules::checkMove(short up, short down, short left, short right, 
                      bool withJump, bool withHover) const
{
    return check(moves, up, down, left, right, withJump, withHover);
}

bool Rules::checkAttackMove(short up, short down, short left, short right, 
                            bool withJump, bool withHover) const
{
	return check(attackMoves, up, down, left, right, withJump, withHover);
}

void Rules::coutDebug() const
{
	cout << "  move rules: " << moves.size() << endl;
	cout << "  attackMove rules: " << attackMoves.size() << endl;
}

// --------------------------------------------------------------------


bool Rules::check(const vector<Rule> &searchHere, short up, short down, 
                  short left, short right, bool withJump, bool withHover) const
{
#ifndef NDEBUG
    if (up && down || left && right)
    	assert("A figure can't move in two opposite ways!" && false);
#endif

    vector<Rule>::const_iterator it = searchHere.begin();
    while (it != searchHere.end())
    {
    	// must have hover?
    	if (withHover && !(*it).hover)
    	{
    		++it;
    		continue;
    	}

    	// must have jump?
    	if (withJump && !(*it).jump)
    	{
    		++it;
    		continue;
    	}
    	
    	// if jump
    	if ((*it).jump)
    	{
    		if ((*it).up == up && (*it).down == down && (*it).left == left && (*it).right == right)
    			return true;
    		else
    		{
    			++it;
    			continue;
    		}
    	}

		// check directions
		if (up && up == right)				// up/right
			if ((*it).up >= up && (*it).right >= right)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (right && right == down)	// right/down
			if ((*it).right >= right && (*it).down >= down)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (down && down == left)		// down/left
			if ((*it).down >= down && (*it).left >= left)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (left && left == up)		// left/up
			if ((*it).left >= left && (*it).up >= up)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (up && !left && !right)		// up
			if ((*it).up >= up && (*it).left == 0 && (*it).right == 0)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (right && !up && !down)		// right
			if ((*it).right >= right && (*it).up == 0 && (*it).down == 0)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (down && !left && !right)	// down
			if ((*it).down >= down && (*it).left == 0 && (*it).right == 0)
				return true;
			else
			{
				++it;
				continue;
			}
		
		else if (left && !up && !down)		// left
			if ((*it).left >= left && (*it).up == 0 && (*it).down == 0)
				return true;
			else
			{
				++it;
				continue;
			}

    	
    	++it;
    }
    
    return false;
}
