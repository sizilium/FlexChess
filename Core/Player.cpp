#include "Player.h"

Player::Player(const string &name, int id, bool computer)
:killed(false), name(name), id(id), x(0), y(0), computer(computer)
{
}

Player::~Player()
{
	vector<Figure*>::iterator it = figures.begin();
	while (it != figures.end())
		delete *it++;
}

void Player::setColor(const Color &color)
{
	this->color = color;
	vector<Figure*>::iterator it = figures.begin();
	while (it != figures.end())
		(*it++)->setColor(color);
}

void Player::addFigure(Figure *figure)
{
	figure->setColor(color);
	figures.push_back(figure);
}

void Player::removeFigure(Figure *figure)
{
	figure->setPos(-1, -1, false, false);

	delete figure;
	
	figures.erase(find(figures.begin(), figures.end(), figure));
}

Figure* Player::getFigure(int id) const
{
	vector<Figure*>::const_iterator it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->getId() == id)
			return *it;
		++it;
	}
	return NULL;
}

vector<Figure *> Player::getAllFigures() const
{
	return figures;
}

vector<Figure *> Player::getActivFigures() const
{
	vector<Figure*> retList;
	vector<Figure*>::const_iterator it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->getPosX() >= 0)
			retList.push_back(*it);
		++it;
	}
	return retList;
}

bool Player::hasActivFigures() const
{
	vector<Figure*>::const_iterator it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->getPosX() >= 0)
			return true;
		++it;
	}
	return false;
}

