#include "AI_0.h"

#include "../Core/Player.h"
#include <list>
#include <stdlib.h>
#include <time.h>
using namespace std;


AI_0::AI_0()
{
	// shuffle random generator
	time_t t;
	srand((unsigned) time(&t));
}

AI_0::~AI_0()
{
}

void AI_0::processMove(const Board *board, const Players *players, AbstractController *controller)
{
	vector<Figure*> figures = players->getCurrentPlayer()->getActivFigures();
	
	// pick random figure
	int nr = rand() % figures.size();
	Figure *figure = figures.at(nr);
	
	// try random move with figure
	int toX, toY;
	int count = 0;
	do
	{
		++count;
		toX = rand() % board->getSizeX();
		toY = rand() % board->getSizeY();
		
		// try other figure
		if (count > board->getSizeX() * board->getSizeY() * 200)
		{
//			if (figures.size() == 1)
//			{
//				controller->cannotMove();
//				return;
//			}
			int nr = rand() % figures.size();
			figure = figures.at(nr);
		}	
	}
	while (!controller->checkMove(figure->getPosX(), figure->getPosY(), toX, toY));
	
	controller->move(figure->getPosX(), figure->getPosY(), toX, toY);
}
