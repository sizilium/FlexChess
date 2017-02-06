#include "Controller.h"
#include "Core/Board.h"
#include "Core/Figures.h"
#include "Core/Figure.h"
#include "Core/Players.h"
#include "Core/Player.h"
#include <vs/cmd/CommandExecutor.h>


Controller::Controller()
{
	commandExecutor = new CommandExecutor;
	commandExecutor->setHistorySize(UNDO_STEPS);
}

Controller::~Controller()
{
	delete commandExecutor;
}

void Controller::init(Board *board, Figures *figures, Players *players)
{
	assert(board && figures && players);
	this->board = board;
	this->figures = figures;
	this->players = players;
}

int Controller::checkLooserId() const
{
	if (!players->getCurrentPlayer()->hasActivFigures())
		return players->getCurrentPlayer()->getId();
	else
		return -1;
}

void Controller::nextPlayer()
{
	commandExecutor->addCommand(new CmdNextPlayer(players));
	commandExecutor->execute();
}

void Controller::killPlayer(int playerId)
{
	commandExecutor->addCommand(new CmdKillPlayer(players, playerId));
	commandExecutor->execute();
}

bool Controller::checkMove(int fromX, int fromY, int toX, int toY) const
{
	Figure *figure = board->getFigure(fromX, fromY);
	
	// check if figure
	if (figure == NULL)
		return false;

	// check target coords
	if (toX >= board->getSizeX() || toY >= board->getSizeY() || toX < 0 || toY < 0)
		return false;
	
	int figureId = figure->getPlayerId();

	// check if my figure
	if (figureId != players->getCurrentPlayer()->getId())
		return false;

	// must have hover?
	bool hover = false;
	Figure *targetFigure = board->getFigure(toX, toY);
	if (targetFigure)
		if (targetFigure->getPlayerId() == players->getCurrentPlayer()->getId())
			hover = true;

	// must have jump?
	bool jump = false;
	int wayPointX = fromX;
	int wayPointY = fromY;
	while (wayPointX != toX || wayPointY != toY)
	{
		if (wayPointX > toX)
			--wayPointX;
		else if (wayPointX < toX)
			++wayPointX;
		if (wayPointY > toY)
			--wayPointY;
		else if (wayPointY < toY)
			++wayPointY;
		
		if (board->getFigure(wayPointX, wayPointY) && (wayPointX != toX || wayPointY != toY))
		{
			jump = true;
			break;
		}
	}

	// calc relative figure moves (up, down, left, right)
	int myDirection = figure->getDirection();
	short up = 0, down = 0, left = 0, right = 0;
	calcRelativeFigureMoves(myDirection, fromX, fromY, toX, toY, up, down, left, right);

	// if target an enemy?
	if (targetFigure && !hover)
		// check if figure can attack
		return figure->checkAttackMove(up, down, left, right, jump, hover);
	else
		// check if figure can move
		return figure->checkMove(up, down, left, right, jump, hover);
}

void Controller::move(int fromX, int fromY, int toX, int toY, bool noGraphic)
{
#ifndef NDEBUG
	if (!checkMove(fromX, fromY, toX, toY))
		cerr << "Warning in Controller::move(): Move is not allowed! First check with checkMove()" << endl;
#endif

	commandExecutor->addCommand(new CmdMoveCommand(fromX, fromY, toX, toY, board, noGraphic));
	commandExecutor->execute();
}

void Controller::cannotMove()
{
	players->getCurrentPlayer()->markAsKilled();
}

void Controller::replaceFigure(int x, int y, const string &newFigureName, bool noGraphic)
{
	Figure *oldFigure = board->getFigure(x, y);
	assert("Cannot replace figure! There is no figure on this place." && oldFigure);
	Player *oldPlayer = players->getPlayer(oldFigure->getPlayerId());
	Player *newPlayer = players->getCurrentPlayer();
	commandExecutor->addCommand(new CmdReplaceFigureCommand(oldFigure, newFigureName, figures, 
	                                                        board, oldPlayer, newPlayer, noGraphic));
	commandExecutor->execute();
}

void Controller::undo(int steps)
{
	for (int i = 0; i < steps; i++)
		commandExecutor->undo();
}

void Controller::redo(int steps)
{
	for (int i = 0; i < steps; i++)
		commandExecutor->redo();
}

void Controller::clearHistory()
{
	commandExecutor->clear();
}

void Controller::calcRelativeFigureMoves(int myDirection, int fromX, int fromY, int toX, int toY,
                                         short &up, short &down, short &left, short &right) const
{
	if (myDirection == 3)		// y
	{
		fromY > toY ? down = fromY - toY : up = toY - fromY;
		fromX > toX ? left = fromX - toX : right = toX - fromX; 
	}
	else if (myDirection == 2)	// -x
	{
		// TODO implement direction 2
		assert(false);
	}
	else if (myDirection == 1)	// -y
	{
		fromY > toY ? up = fromY - toY : down = toY - fromY;
		fromX > toX ? right = fromX - toX : left = toX - fromX;
	}
	else if (myDirection == 0)	// x
	{
		// TODO implement direction 0
		assert(false);
	}
	else
		assert ("Can't check move! Player has invalid direction." && false);
}

// ------------------------------ Commands ---------------------------------------------


CmdMoveCommand::CmdMoveCommand(int fromX, int fromY, int toX, int toY, Board *board, bool noGraphic)
:enemyFigure(NULL), movedState(false), fromX(fromX), fromY(fromY), toX(toX), toY(toY), 
board(board), noGraphic(noGraphic)
{
	assert(board);
}

void CmdMoveCommand::execute()
{
	// get figure
	Figure *figure = board->getFigure(fromX, fromY);
	assert("Can't move figure, because there is an empty field! First check the field." && figure != NULL);
	
	// update figure
	figure->setPos(toX, toY, true, noGraphic);
	board->setFigure(fromX, fromY, NULL);

	// save move state
	movedState = figure->isMoved();
	figure->markMoved();
	
	// handle enemy figure (if exist)
	if ((enemyFigure = board->getFigure(toX, toY)) != NULL)
		enemyFigure->setPos(-1, -1, true, noGraphic);

	// set figure to new place
	board->setFigure(toX, toY, figure);
}

void CmdMoveCommand::undo()
{
	// get figure
	Figure *figure = board->getFigure(toX, toY);
	assert("Can't move figure, because there is an empty field! First check the field." && figure != NULL);
	
	// update figure
	figure->setPos(fromX, fromY, false, noGraphic);
	
	// restore move state
	if (movedState)
		figure->markMoved();
	else
		figure->unmarkMoved();
	
	// restore enemyFigure if exist
	board->setFigure(toX, toY, enemyFigure);
	if (enemyFigure)
		enemyFigure->setPos(toX, toY, false, noGraphic);
	
	// set figure to old place
	board->setFigure(fromX, fromY, figure);
}


CmdReplaceFigureCommand::CmdReplaceFigureCommand(Figure *oldFigure, const string &newFigureName, 
                     	                        	Figures *figures, Board *board, Player *oldPlayer, 
                     	                        	Player *newPlayer, bool noGraphic)
:oldFigure(oldFigure), newFigureName(newFigureName), figures(figures), board(board),
oldPlayer(oldPlayer), newPlayer(newPlayer), noGraphic(noGraphic), oldX(0), oldY(0)
{
	assert(oldFigure && board && figures && oldPlayer && newPlayer);
}

void CmdReplaceFigureCommand::execute()
{
	oldX = oldFigure->getPosX();
	oldY = oldFigure->getPosY();
	
	// deactivate old figure (no delete)
	oldFigure->setPos(-1, -1, false, noGraphic);
	
	// copy new figure
	assert("Can't copy figure in command. Figure does not exist!" && figures->getFigure(newFigureName));
	Figure *newFigure = new Figure(*figures->getFigure(newFigureName));
	
	// init figure
	newFigure->setPlayerId(newPlayer->getId());
	newFigure->createModel();
	newFigure->setPos(oldX, oldY, false, noGraphic);
	newFigure->setDirection(newPlayer->getDirection());
	newFigure->setColor(newPlayer->getColor());
	
	// add new figure to newPlayer
	newPlayer->addFigure(newFigure);
	
	// update board
	board->setFigure(oldX, oldY, newFigure);
}

void CmdReplaceFigureCommand::undo()
{
	Figure *newFigure = board->getFigure(oldX, oldY);
	assert(newFigure);
	
	// activate old figure
	oldFigure->setPos(oldX, oldY, false, noGraphic);
	
	// remove & delete new figure
	newPlayer->removeFigure(newFigure);
	
	// update board
	board->setFigure(oldX, oldY, oldFigure);
}


CmdNextPlayer::CmdNextPlayer(Players *players)
:players(players)
{

}

void CmdNextPlayer::execute()
{
	players->nextPlayer();
}

void CmdNextPlayer::undo()
{
	players->previousPlayer();
}


CmdKillPlayer::CmdKillPlayer(Players *players, int playerId)
:players(players), playerId(playerId)
{

}

void CmdKillPlayer::execute()
{
	players->killPlayer(playerId);
}

void CmdKillPlayer::undo()
{
	players->getPlayer(playerId)->unmarkAsKilled();
}
