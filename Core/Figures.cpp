#include "Figures.h"
#include <iostream>

Figures::Figures()
{
}

Figures::~Figures()
{
	list<Figure*>::iterator it = figures.begin();
	while (it != figures.end())
		delete *it++;
}

void Figures::setColorForAll(const Color &color)
{
	list<Figure*>::iterator it = figures.begin();
	while (it != figures.end())
		(*it++)->setColor(color);
}

void Figures::addFigure(Figure *figure)
{
	figures.push_back(figure);
}

void Figures::removeFigure(Figure *figure)
{
	figures.remove(figure);
}

void Figures::coutDebug() const
{
	cout << "Number Figures: " << figures.size() << endl << endl;
	list<Figure*>::const_iterator it = figures.begin();
	while (it != figures.end())
	{
		(*it++)->coutDebug();
		cout << endl;
	}
}

Figure* Figures::getFigure(const string & name)
{
	list<Figure*>::iterator it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->getName() == name)
			return *it;
		++it;
	}
	return NULL;
}
