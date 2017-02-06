#include "AI_1.h"

#include "../Core/Player.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;


AI_1::AI_1()
{
	// shuffle random generator
	time_t t;
	srand((unsigned) time(&t));
}

AI_1::~AI_1()
{
}

void AI_1::processMove(const Board *board, const Players *players, AbstractController *controller)
{
	double lowestEnemyPoints = 99999;	// = my best points
	vector<pair<int, int> > bestFigureBestMove;
	
	// check my possible figures
	Player *player = players->getCurrentPlayer();
	vector<Figure*> figures = player->getActivFigures();
	for (size_t i = 0; i < figures.size(); i++)
	{
		// check my possible moves per figure
		Figure *figure = figures.at(i);
		vector<pair<int, int> > moves = figure->getPossibleMoves();
		vector<pair<int, int> > attackMoves = figure->getPossibleAttackMoves();
		copy(attackMoves.begin(), attackMoves.end(), back_inserter(moves));
		for (size_t j = 0; j < moves.size(); j++)
		{
			if (controller->checkMove(figure->getPosX(), figure->getPosY(), moves.at(j).first, moves.at(j).second))
			{
				controller->move(figure->getPosX(), figure->getPosY(), moves.at(j).first, moves.at(j).second, true);
				
				controller->nextPlayer();
	
				// check enemies best points
				double enemyPoints = checkBestMove(board, players, controller);

				if (enemyPoints < lowestEnemyPoints)
				{
					lowestEnemyPoints = enemyPoints;
					bestFigureBestMove.clear();
					bestFigureBestMove.push_back(pair<int,int>(i, j));
				}
				else if (enemyPoints == lowestEnemyPoints)
				{
					bestFigureBestMove.push_back(pair<int,int>(i, j));
				}

				controller->undo(2);
			}
		}
	}

	// move best figure with best move
	assert("AI_1 can't hadn't found a move!" && !bestFigureBestMove.empty());

	// random ...
	int bestFigure, bestMove;
	int randIndex = rand() % bestFigureBestMove.size();
	bestFigure = bestFigureBestMove.at(randIndex).first;
	bestMove = bestFigureBestMove.at(randIndex).second;
	
	Figure *figure = figures.at(bestFigure);
	vector<pair<int, int> > moves = figure->getPossibleMoves();
	vector<pair<int, int> > attackMoves = figure->getPossibleAttackMoves();
	copy(attackMoves.begin(), attackMoves.end(), back_inserter(moves));
	pair<int, int> move = moves.at(bestMove);
	
	controller->move(figure->getPosX(), figure->getPosY(), move.first, move.second);
}


double AI_1::checkBestMove(const Board *board, const Players *players, AbstractController *controller)
{
	double bestPoints = -99999;
	
	// check my possible figures
	Player *player = players->getCurrentPlayer();
	vector<Figure*> figures = player->getActivFigures();
	for (size_t i = 0; i < figures.size(); i++)
	{
		// check my possible moves per figure
		Figure *figure = figures.at(i);
		vector<pair<int, int> > moves = figure->getPossibleMoves();
		vector<pair<int, int> > attackMoves = figure->getPossibleAttackMoves();
		copy(attackMoves.begin(), attackMoves.end(), back_inserter(moves));
		for (size_t j = 0; j < moves.size(); j++)
		{
			if (!controller->checkMove(figure->getPosX(), figure->getPosY(), moves.at(j).first, moves.at(j).second))
				continue;
			
			controller->move(figure->getPosX(), figure->getPosY(), moves.at(j).first, moves.at(j).second, true);

			double points = calcPointsFigures(players) +
							calcPointsPosition(board, players, controller);
			if (points > bestPoints)
				bestPoints = points;
			
			controller->undo();
		}

	}

	return bestPoints;
}


// ---------------------------------------------------------------------------------------------


double calcPointsFigures(const Players *players)
{
	// calc my weigth
	double myWeight = 0;
	vector<Figure*> figures = players->getCurrentPlayer()->getActivFigures();
	vector<Figure*>::const_iterator it = figures.begin();
	
	while (it != figures.end())
		myWeight += (*it++)->getWeight();
	
	// calc enemy weight
	double enemyWeight = 0;
	vector<Player*> enemies = players->getAllEnemyPlayers();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		vector<Figure*> figures = enemies.at(i)->getActivFigures();
		vector<Figure*>::const_iterator it = figures.begin();

		while (it != figures.end())
			enemyWeight += (*it++)->getWeight();
	}
	
	// return points (difference of all figures weight)
	return myWeight - enemyWeight;
}

double calcPointsPosition(const Board *board, const Players *players, AbstractController *controller)
{
	// 1. calc my position points
	double myPoints = 0;
	
	Player *player = players->getCurrentPlayer();
	vector<Figure*> figures = players->getCurrentPlayer()->getActivFigures();
	
	// check all figues
	for (size_t i = 0; i < figures.size(); i++)
	{
		// check all attack moves for each figure
		Figure *figure = figures.at(i);
		vector<pair<int, int> > attackMoves = figure->getPossibleAttackMoves();
		
		for (size_t j = 0; j < attackMoves.size(); j++)
		{
			Figure *targetFigure = board->getFigure(attackMoves.at(j).first, attackMoves.at(j).second);
			
			// figure to attack?
			if (!targetFigure)
				continue;
			// enemy figue?
			if (targetFigure->getPlayerId() == player->getId())
				continue;
			// move valid?
			if (!controller->checkMove(figure->getPosX(), figure->getPosY(), attackMoves.at(j).first, attackMoves.at(j).second))
				continue;
			
			myPoints += targetFigure->getWeight() / 10;
		}
	}
	
	controller->nextPlayer();
		
	// 2. calc enemy position points
	double enemyPoints = 0;
	
	player = players->getCurrentPlayer();
	figures = players->getCurrentPlayer()->getActivFigures();
	
	// check all figues
	for (size_t i = 0; i < figures.size(); i++)
	{
		// check all attack moves for each figure
		Figure *figure = figures.at(i);
		vector<pair<int, int> > attackMoves = figure->getPossibleAttackMoves();
		
		for (size_t j = 0; j < attackMoves.size(); j++)
		{
			Figure *targetFigure = board->getFigure(attackMoves.at(j).first, attackMoves.at(j).second);
			
			// figure to attack?
			if (!targetFigure)
				continue;
			// enemy figue?
			if (targetFigure->getPlayerId() == player->getId())
				continue;
			// move valid?
			if (!controller->checkMove(figure->getPosX(), figure->getPosY(), attackMoves.at(j).first, attackMoves.at(j).second))
				continue;
			
			enemyPoints += targetFigure->getWeight() / 10;
		}
	}
	
	
	controller->undo();

	return myPoints - enemyPoints;
}
