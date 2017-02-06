#include "Game.h"
#include "Core/Figures.h"
#include "Core/Players.h"
#include "Core/Player.h"
#include "Core/Figure.h"
#include "Core/Board.h"
#include "Controller.h"
#include "Xml/ReadBoardXml.h"
#include "Xml/ReadFiguresXml.h"
#include "Xml/ReadFormationXml.h"
#include "FlexChessException.hpp"

#include "ArtificalIntelligence/AI_1.h"

#include <assert.h>
#include <iomanip>
#include <vs/base/util/FileException.h>
#include <vs/core/gl/Color.h>
#include <vs/Context.h>
#include <vs/constr/ConstraintManager.h>
#include <vs/managed/gl/model/ModelManager.h>
using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gl::model;
using namespace vs::constr;


using namespace vs::base::util;

Game::Game() 
:idCount(0), pause(false), fromX(-1), fromY(-1), toX(-1), toY(-1), figures(NULL), 
players(NULL), board(NULL), controller(NULL)
{
	figures = new Figures();
	board = new Board();
	players = new Players();
}

Game::~Game()
{
	delete figures;
	delete players;
	delete board;
	delete controller;
	vector<AbstractAI*>::iterator it = artificalIntelligences.begin();
	while (it != artificalIntelligences.end())
		delete *it++;
}

void Game::setController(AbstractController *controller)
{
	assert(controller);
	this->controller = controller;
	this->controller->init(board, figures, players);
}

void Game::addPlayer(const string &name, AbstractAI *ai)
{
	players->addPlayer(new Player(name, idCount));
	artificalIntelligences.push_back(ai);
	++idCount;
}

Player* Game::getWinner() const
{
	return players->getWinner();
}

void Game::loadXml(const string &pathFigures, const string &pathBoard, const string &pathFormation)
{
	ReadBoardXml readBoard(board, players);
	ReadFiguresXml readFigures(figures);
	ReadFormationXml readFormation(players, figures);

	try
	{
		if (!pathFigures.empty())
		readFigures.read(pathFigures);

		if (!pathBoard.empty())
		readBoard.read(pathBoard);

		if (!pathFormation.empty())
		readFormation.read(pathFormation);
	}
	catch(FlexChessException &e)
	{
		e.printStackTrace();
	}
	catch(FileException &e)
	{
		e.printStackTrace();
	}
	catch(XmlException &e)
	{
		e.printStackTrace();
	}
	catch(Exception &e)
	{
		e.printStackTrace();
	}
	catch(...)
	{
		assert("Uncaught Exception!!" && false);
	}

	// init board
	populateBoardWithPlayers(board, players);

}

bool Game::run()
{
	// no move if game is still in pause or wait for animation (by constraints)
	if (pause || Context::getCurrentContext()->getConstraintManager()->numActiveManaged())
		return true;
	
	// check winner
	if (players->checkWinner())
		return false;
	
	// get player object (for human or computer)
	Player *player = players->getCurrentPlayer();
	assert("You can't run Game without players!" && player != NULL);

	// get playerId and artifical intelligence (if exist)
	int id = player->getId();
	AbstractAI *artificalIntelligence = artificalIntelligences.at(id);

	// computer move
	if (artificalIntelligence)
	{
		artificalIntelligence->processMove(board, players, controller);
		
		// set next player
		controller->nextPlayer();
		
		// can next player move? (else kill!)
		if (controller->checkLooserId() != -1)
			// TODO killPlayer by controller with command!! (undo possible)
			controller->killPlayer(controller->checkLooserId());
	}
	// human move
	else
	{
		if (fromX != -1 && toX != -1)
		{
			if (controller->checkMove(fromX, fromY, toX, toY))
			{
				controller->move(fromX, fromY, toX, toY);
				resetInject();
				
				// set next player
				controller->nextPlayer();
				
				// can next player move? (else kill!)
				if (controller->checkLooserId() != -1)
					controller->killPlayer(controller->checkLooserId());
			}
			else
				resetInject();
		}
	}

	return true;	// the game is running (no winner)
}

void Game::setPause(bool enable)
{
	pause = enable;
}

void Game::undo()
{
	if (controller)
		controller->undo(2);	// undo move & nextPlayer command
	
	pause = true;
}

void Game::redo()
{
	if (controller)
		controller->redo(2);
	
	pause = true;
}

void Game::resetInject()
{
	this->fromX = -1;
	this->fromY = -1;
	this->toX = -1;
	this->toY = -1;
}

void Game::injectStart(int fromX, int fromY)
{
	if (fromX >= board->getSizeX() || fromY >= board->getSizeY() || fromX < 0 || fromY < 0)
		return;
	this->fromX = fromX;
	this->fromY = fromY;
}

void Game::injectTarget(int toX, int toY)
{
	if (toX >= board->getSizeX() || toY >= board->getSizeY() || toX < 0 || toY < 0)
		return;
	this->toX = toX;
	this->toY = toY;
}

bool Game::checkMove(int fromX, int fromY) const
{
	if (fromX == -1)
		return false;
	Figure *figure = board->getFigure(fromX, fromY);
	
	if (figure && figure->getPlayerId() == players->getCurrentPlayer()->getId())
		return true;
	else
		return false;
}

bool Game::checkMove(int fromX, int fromY, int toX, int toY) const
{
	if (toX == -1 || fromX == -1)
		return false;

	return controller->checkMove(fromX, fromY, toX, toY);
}

pair<int, int> Game::getBoardDimenstions() const
{
	assert(board);
	return pair<int, int>(board->getSizeX(), board->getSizeY());
}

void Game::coutDebugFigures() const
{
	figures->coutDebug();
	cout << endl;
}

void Game::coutDebugPlayers() const
{
	players->coutDebug();
	cout << endl;
}

void Game::coutDebugBoard() const
{
	board->coutDebug();
	cout << endl;
}

void Game::coutPoints() const
{
	assert(players && board && controller);
	
	cout << endl << "Points of current Player:" << endl;
	cout << " sum figures weight = " <<	calcPointsFigures(players) << endl;
	cout << " position points = " << calcPointsPosition(board, players, controller) << endl;
}

// -------------------------------------------------------------------------------

void Game::populateBoardWithPlayers(Board *board, Players *players)
{
	vector<Player*> playerList = players->getAllPlayers();

	// for each player
	for (size_t i = 0; i < playerList.size(); i++)
	{
		Player *player = playerList[i];
		vector<Figure*> figureList = player->getAllFigures();
		vector<Figure*>::const_iterator it = figureList.begin();

		// for each figure
		while (it != figureList.end())
		{
			Figure *figure = *it;

			if (playerList.at(i)->getDirection() == 3) // y, direction up
			{
				figure->setDirection(3);
				figure->setPos(figure->getPosX() + player->getRefX(), figure->getPosY()
						+ player->getRefY(), false);
				board->setFigure(figure->getPosX(), figure->getPosY(), figure);
			}
			if (playerList.at(i)->getDirection() == 2) // -x, direction left
			{
				// TODO implement direction 2
				assert(false);
			}
			if (playerList.at(i)->getDirection() == 1) // -y, direction down
			{
				figure->setDirection(1);
				// correct figure coordinates
				figure->setPos(player->getRefX() - figure->getPosX(), player->getRefY()
						- figure->getPosY(), false);
				board->setFigure(figure->getPosX(), figure->getPosY(), figure);
			}
			if (playerList.at(i)->getDirection() == 0) // x, direction right
			{
				// TODO implement direction 0
				assert(false);
			}

			++it;
		}
	}
}
