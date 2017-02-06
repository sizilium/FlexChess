#include "Figure.h"
#include <iostream>
#include <vs/managed/gl/model/ModelFactory.h>
#include <vs/constr/ModelConstraintFactory.h>
#include <vs/constr/ModelMoveConstraint.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/base/util/FileException.h>
#include <vs/Context.h>
#include <vs/base/util/IDGenerator.hpp>
#include <sstream>
using namespace vs;
using namespace base::math;
using namespace vs::base::util;
using namespace vs::constr;


// animation speed (LE per second)
double speed = 3;

Figure::Figure(const string &name, const string &geometry, double weight, Rules rules, 
               short id, short direction, short playerId)
:name(name), geometry(geometry), x(-1), y(-1), moved(false), weight(weight), rules(rules), 
id(id), direction(direction), playerId(playerId), activ(true)
{
	model = NULL;
	modelId = 0;
	assert("Invalid direction for figure!" && direction >= 0 && direction <= 3);
}

Figure::~Figure()
{
//	if (model)
//		Context::getCurrentContext()->getModelManager()->removeManaged(name);
}

void Figure::createModel()
{
	assert ("Model already created!" && model == NULL);
	
	ModelFactory factory;

	try
	{
		this->model = factory.createManagedModel(geometry, name, true, true, true, true); // with custom stuff
	}
	catch(FileException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		e.printStackTrace();
		model = NULL;
	}
	catch(Exception &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		e.printStackTrace();
		model = NULL;
	}
	catch(...)
	{
		assert("Uncaught Exception!" && false);
	}
	
	assert(model);
	try
	{
		modelId = model->getObjectId(name);
	}
	catch(Exception &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		e.printStackTrace();
		model = NULL;
	}
	
	// TODO die modelId ist nicht eindeutig, die figur sorten haben jeweils die gleiche id! 
	// picking funktioniert noch nicht
	//cout << name << " " << modelId << endl;
	//model->activatePicking(modelId);
}

void Figure::setColor(const Color &color)
{
	assert(model);
	assert(modelId != 0);

	list<double>::iterator colorIterator = model->getObjColorIt(modelId);
	*colorIterator++ = color.red();
	*colorIterator++ = color.green();
	*colorIterator++ = color.blue();
	*colorIterator = color.alpha();
}

void Figure::setDirection(short direction)
{
	this->direction = direction;
	this->direction = direction;
	
    if (model != NULL)
    {
    	assert(modelId != 0);
    	list<double>::iterator eulerIterator = model->getObjEulerIt(modelId);
    	
    	++eulerIterator;
    	++eulerIterator;
    	
    	if (direction == 0)
	    	*eulerIterator = 90;
    	else if (direction == 1)
    		*eulerIterator = 180;
    	else if (direction == 2)
    		*eulerIterator = 270;
    }
}

void Figure::setPos(int toX, int toY, bool withAnimation, bool noGraphic)
{
	if (!noGraphic)
	{
		// make visible
		if (!this->activ /*!model->isActive()*/)
		{
			list<double>::iterator colorIterator = model->getObjColorIt(modelId);
			++colorIterator;
			++colorIterator;
			++colorIterator;
			*colorIterator = 1;
			
			//model->activate();
			this->activ = true;
			if (withAnimation)
			{
				ModelConstraintFactory constrFactory;
				DoubleVector startCoord(x, y, -2);
				DoubleVector endCoord(x, y, 0);
				constrFactory.createModelMoveConstraint (model, modelId, startCoord, endCoord, speed, name);
			}
			else
			{
				list<double>::iterator posIterator = model->getObjCenterIt(modelId);
				*posIterator++ = toX;
				*posIterator++ = toY;
				*posIterator = 0;
			}
		}

		//  make invisible
		if (this->activ && toX == -1)
		{
			// TODO model deaktivieren geht nicht
			//model->deactivate();
			this->activ = false;

			if (withAnimation)
			{
				ModelConstraintFactory constrFactory;
				DoubleVector startCoord(this->x, this->y, 0);
				DoubleVector endCoord(this->x, this->y, -2);
				constrFactory.createModelMoveConstraint (model, modelId, startCoord, endCoord, speed, name);
			}
			else
			{
				list<double>::iterator posIterator = model->getObjCenterIt(modelId);
				*posIterator++ = this->x;
				*posIterator++ = this->y;
				*posIterator = -2;
				list<double>::iterator colorIterator = model->getObjColorIt(modelId);
				++colorIterator;
				++colorIterator;
				++colorIterator;
				*colorIterator = 0;
			}
		}
		// normal figure move
		else
		{
			assert(modelId != 0);
			if (withAnimation)
			{
				ModelConstraintFactory constrFactory;
				DoubleVector startCoord(this->x, this->y, 0);
				DoubleVector endCoord(toX, toY, 0);
				constrFactory.createModelMoveConstraint (model, modelId, startCoord, endCoord, speed, name);
			}
			else
			{
				list<double>::iterator posIterator = model->getObjCenterIt(modelId);
		    	*posIterator++ = toX;
		    	*posIterator++ = toY;
		    	*posIterator = 0;
			}
		}
	}

    this->x = toX;
    this->y = toY;
}

bool Figure::checkMove(short up, short down, short left, short right, bool withJump, bool withHover) const
{
	return rules.checkMove(up, down, left, right, withJump, withHover);
}

bool Figure::checkAttackMove(short up, short down, short left, short right, bool withJump, bool withHover) const
{
	return rules.checkAttackMove(up, down, left, right, withJump, withHover);
}

bool Figure::checkMove(int toX, int toY, bool withJump, bool withHover) const
{
	// consider figures direction and position for checking absolute coordinates...
	
	short up,down, left, right;
	
	if (direction == 0)			// x
	{
		// TODO implement direction 0
		assert ("implement direction 0!" && false);
	}
	else if (direction == 1)	// -y
	{
		if (x < toX)
		{
			right = 0;
			left = toX - x;
		}
		else
		{
			right = x - toX;
			left = 0;
		}
		
		if (y > toY)
		{
			down = 0;
			up = y - toY;
		}
		else
		{
			down = y - toY;
			up = 0;
		}
	}
	else if (direction == 2)	// -x
	{
		// TODO implement direction 2
		assert ("implement direction 2!" && false);
	}
	else						// y
	{
		if (x < toX)
		{
			left = 0;
			right = toX - x;
		}
		else
		{
			left = x - toX;
			right = 0;
		}
		
		if (y < toY)
		{
			down = 0;
			up = toY - y;
		}
		else
		{
			down = y - toY;
			up = 0;
		}
	}
	
	return checkMove(up, down, left, right, withJump, withHover);
}

bool Figure::checkAttackMove(int toX, int toY, bool withJump, bool withHover) const
{
	// consider figures direction and position for checking absolute coordinates...
	
	short up,down, left, right;
	
	if (direction == 0)			// x
	{
		// TODO implement direction 0
		assert ("implement direction 0!" && false);
	}
	else if (direction == 1)	// -y
	{
		if (x < toX)
		{
			right = 0;
			left = toX - x;
		}
		else
		{
			right = x - toX;
			left = 0;
		}
		
		if (y > toY)
		{
			down = 0;
			up = y - toY;
		}
		else
		{
			down = toY - y;
			up = 0;
		}
	}
	else if (direction == 2)	// -x
	{
		// TODO implement direction 2
		assert ("implement direction 2!" && false);
	}
	else						// y
	{
		if (x < toX)
		{
			left = 0;
			right = toX - x;
		}
		else
		{
			left = x - toX;
			right = 0;
		}
		
		if (y < toY)
		{
			down = 0;
			up = toY - y;
		}
		else
		{
			down = y - toY;
			up = 0;
		}
	}
	
	return checkAttackMove(up, down, left, right, withJump, withHover);
}

vector<pair<int, int> > Figure::getPossibleMoves() const
{
	// TODO? return pointer (smart pointer) for more performance
	return getPossibleActions(rules.getMoves());
}

vector<pair<int, int> > Figure::getPossibleAttackMoves() const
{
	return getPossibleActions(rules.getAttackMoves());
}

vector<pair<int, int> > Figure::getPossibleActions(const vector<Rule> *vec) const
{
	// TODO? create on heap
	vector<pair<int, int> > retVec;
	
	vector<Rule>::const_iterator it = vec->begin();
	while (it != vec->end())
	{
		short up = (*it).up;
		short down = (*it).down;
		short left = (*it).left;
		short right = (*it).right;
		
		do
		{
			int absX = x, absY = y;
			
			// calc absolute coords
			if (direction == 3)		// y
			{
				up > down ? absY += up : absY -= down;
				left > right ? absX -= left : absX += right;
			}
			else if (direction == 2)	// -x
			{
				// TODO implement direction 2
				assert(false);
			}
			else if (direction == 1)	// -y
			{
				up > down ? absY -= up : absY += down;
				left > right ? absX += left : absX -= right;
			}
			else if (direction == 0)	// x
			{
				// TODO implement direction 0
				assert(false);
			}
			
			// next possible coord
			if (up > 0)
				--up;
			else if (up < 0)
				++up;
			if (down > 0)
				--down;
			else if (down < 0)
				++down;
			if (left > 0)
				--left;
			else if (left < 0)
				++left;
			if (right > 0)
				--right;
			else if (right < 0)
				++right;
			
			// add absolute coords
			retVec.push_back(pair<int, int>(absX, absY));
		}
		while (up != 0 || down != 0 || right != 0 || left != 0);
		
		++it;
	}
	
	return retVec;
}

void Figure::coutDebug() const
{
	cout << " Figure \"" << name << "\"" << endl;
	cout << "  playerId: " << playerId << endl;
	cout << "  pos: " << x << "," << y << endl;
	cout << "  weight: " << weight << endl;
	if (moved)
		cout << "  moved: true" << endl;
	else
		cout << "  moved: false" << endl;
	cout << " Rules:" << endl;
	rules.coutDebug();
}
