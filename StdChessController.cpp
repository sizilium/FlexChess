#include "StdChessController.h"
#include "Core/Player.h"
#include <vs/cmd/CommandExecutor.h>
using namespace vs::cmd;


StdChessController::StdChessController()
{
}

StdChessController::~StdChessController()
{
}

int StdChessController::checkLooserId() const
{
	// check players activ figures
	vector<Figure*> activFigures = players->getCurrentPlayer()->getActivFigures();
	
	for (size_t i = 0; i < activFigures.size(); i++)
	{
		// check figures possible moves
		Figure *figure = activFigures.at(i);
		vector<pair<int, int> > movesToCheck = figure->getPossibleMoves();
		
		for (size_t j = 0; j < movesToCheck.size(); j++)
		{
			if (movesToCheck.at(j).first >= board->getSizeX() || movesToCheck.at(j).second >= board->getSizeY())
				continue;
			
			// probe
			if (checkMove(figure->getPosX(), figure->getPosY(),
			              movesToCheck.at(j).first, movesToCheck.at(j).second))
				return -1;
		}
		
		movesToCheck = figure->getPossibleAttackMoves();
		
		for (size_t j = 0; j < movesToCheck.size(); j++)
		{
			if (movesToCheck.at(j).first >= board->getSizeX() || movesToCheck.at(j).second >= board->getSizeY())
				continue;
			
			// probe
			if (checkMove(figure->getPosX(), figure->getPosY(),
			              movesToCheck.at(j).first, movesToCheck.at(j).second))
				return -1;
		}
	}

	// return looser
	return players->getCurrentPlayer()->getId();
}

bool StdChessController::checkMove(int fromX, int fromY, int toX, int toY) const
{
	Figure *figure = board->getFigure(fromX, fromY);
	if (!figure || figure->getPlayerId() != players->getCurrentPlayer()->getId())
		return false;

	// check target coords
	if (toX >= board->getSizeX() || toY >= board->getSizeY() || toX < 0 || toY < 0)
		return false;
	
	if (!checkKing(fromX, fromY, toX, toY))
		return false;

	if (checkPawn(figure, fromX, fromY, toX, toY))
		return true;

	if (checkCastlingQueensSide(figure, toX, toY))
		return true;

	if (checkCastlingKingsSide(figure, toX, toY))
		return true;

	if (checkEnPassant(figure))
		return true;

	// check further common rules read from xml file
	return Controller::checkMove(fromX, fromY, toX, toY);
}


void StdChessController::move(int fromX, int fromY, int toX, int toY, bool noGraphic)
{
	Figure *figure = board->getFigure(fromX, fromY);
	Controller::move(fromX, fromY, toX, toY, noGraphic);
	postCheck(figure, fromX, fromY, toX, toY, noGraphic);
}

// --------------------------- private ---------------------------------------

bool StdChessController::checkKing(int fromX, int fromY, int toX, int toY) const
{
	// check king move (musn't be in check)

	// move figure (in theory) and look for king check (without graphic output)
	commandExecutor->addCommand(new CmdMoveCommand(fromX, fromY, toX, toY, board, true));
	commandExecutor->execute();
	
	// get king coordinates
	Figure *king = players->getCurrentPlayer()->getFigure(1);
	int kingX = king->getPosX();
	int kingY = king->getPosY();
	if (kingX < 0)
	{
		// restore old situation and continue other checks...
		commandExecutor->undo();
		return false;	// no valid move
	}

	// check if other players could attack the king (impossible in reality)
	vector<Player*> enemies = players->getAllEnemyPlayers();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		vector<Figure*> figures = enemies.at(i)->getActivFigures();
		for (size_t j = 0; j < figures.size(); j++)
		{
			// must have jump?
			bool withJump = false;
			int wayPointX = figures.at(j)->getPosX();
			int wayPointY = figures.at(j)->getPosY();
			while (wayPointX != kingX || wayPointY != kingY)
			{
				if (wayPointX > kingX)
					--wayPointX;
				else if (wayPointX < kingX)
					++wayPointX;
				if (wayPointY > kingY)
					--wayPointY;
				else if (wayPointY < kingY)
					++wayPointY;
				
				// if there is a hint we need jump
				if (board->getFigure(wayPointX, wayPointY) && (wayPointX != kingX || wayPointY != kingY))
				{
					withJump = true;
					break;
				}
			}
			
			// could the enemy figure attack my king?
			if (figures.at(j)->checkAttackMove(kingX, kingY, withJump))
			{
					// restore old situation and continue other checks...
					commandExecutor->undo();
					return false;	// king is in attack (move is not allowed)
			}
		}
	}

	// restore old situation and continue other checks...
	commandExecutor->undo();

	return true;	// king is not in attack
}

bool StdChessController::checkPawn(Figure *figure, int fromX, int fromY, int toX, int toY) const
{
	// check pawn first move (two up steps)
	if (figure->getId() == 6)
	{
		short up = 0, down = 0, left = 0, right = 0;
		int myDirection = figure->getDirection();
		calcRelativeFigureMoves(myDirection, fromX, fromY, toX, toY, up, down, left, right);
		
		int wayPointX = fromX;
		int wayPointY = fromY;
		if (wayPointX > toX)
			--wayPointX;
		else if (wayPointX < toX)
			++wayPointX;
		if (wayPointY > toY)
			--wayPointY;
		else if (wayPointY < toY)
			++wayPointY;
		
		if (up == 2 && left == 0 && right == 0 && !figure->isMoved() && !board->getFigure(wayPointX, wayPointY) && !board->getFigure(toX, toY))
			return true;
	}
	return false;
}

bool StdChessController::checkCastlingQueensSide(Figure *figure, int toX, int toY) const
{
	if (figure->getId() == 1 && !figure->isMoved())	// if king and not moved?
	{
		if (figure->getDirection() == 0)		// x
		{
			// TODO implement direction 0
			assert(false);
		}
		else if (figure->getDirection() == 1)	// -y
		{
			if (toX != 1 || toY != 7)
				return false;

			// check rook
			if (board->getFigure(0, 7) && !board->getFigure(0, 7)->isMoved())
			{
				// check free way
				if (!board->getFigure(1, 7) && !board->getFigure(2, 7) && !board->getFigure(3, 7))
					return true;
			}
		}
		else if (figure->getDirection() == 2)	// -x
		{
			// TODO implement direction 2
			assert(false);
		}
		else									// y
		{
			if (toX != 1 || toY != 0)
				return false;

			// check rook
			if (board->getFigure(0, 0) && !board->getFigure(0, 0)->isMoved())
			{
				// check free way
				if (!board->getFigure(1, 0) && !board->getFigure(2, 0) && !board->getFigure(3, 0))
					return true;
			}
		}

	}	
	return false;
}

bool StdChessController::checkCastlingKingsSide(Figure *figure, int toX, int toY) const
{
	if (figure->getId() == 1 && !figure->isMoved())	// if king and not moved?
	{
		if (figure->getDirection() == 0)		// x
		{
			// TODO implement direction 0
			assert(false);
		}
		else if (figure->getDirection() == 1)	// -y
		{
			if (toX != 6 || toY != 7)
				return false;
			
			// check rook
			if (board->getFigure(7, 7) && !board->getFigure(7, 7)->isMoved())
			{
				// check free way
				if (!board->getFigure(5, 7) && !board->getFigure(6, 7))
					return true;
			}
		}
		else if (figure->getDirection() == 2)	// -x
		{
			// TODO implement direction 2
			assert(false);
		}
		else									// y
		{
			if (toX != 6 || toY != 0)
				return false;

			// check rook
			if (board->getFigure(7, 0) && !board->getFigure(7, 0)->isMoved())
			{
				// check free way
				if (!board->getFigure(5, 0) && !board->getFigure(6, 0))
					return true;
			}
		}

	}	
	return false;
}

bool StdChessController::checkEnPassant(Figure *figure) const
{
	return false;
}


int StdChessController::postCheck(Figure *figure, int fromX, int fromY, int toX, int toY, bool noGraphic) const
{
	int changes = 0;
	
	Figure *lastMovedFigure = board->getFigure(toX, toY);
	
	// check pawn is at the end of board (new queen)	
	if (lastMovedFigure && lastMovedFigure->getId() == 6)
	{	
		int endFieldX = -99, endFieldY = -99;
		int myDirection = lastMovedFigure->getDirection();
		
		if (myDirection == 3)
			endFieldY = board->getSizeY() - 1;
		else if (myDirection == 2)
			endFieldX = board->getSizeX() - 1;
		else if (myDirection == 1)
			endFieldY = 0;
		else if (myDirection == 0)
			endFieldX = 0;
	
		if (lastMovedFigure->getPosX() == endFieldX || lastMovedFigure->getPosY() == endFieldY)
		{		
			Figure *oldFigure = board->getFigure(lastMovedFigure->getPosX(), lastMovedFigure->getPosY());
			assert("Cannot replace figure! There is no figure on this place." && oldFigure);
			Player *oldPlayer = players->getPlayer(oldFigure->getPlayerId());
			Player *newPlayer = players->getCurrentPlayer();
			commandExecutor->addCommand(new CmdReplaceFigureCommand(oldFigure, "queen", figures, 
			                                                        board, oldPlayer, newPlayer, noGraphic));
			commandExecutor->execute();
			++changes;
		}
	}
	
	// check castling kings and queens side
	assert(figure);
	if (figure->getId() == 1)	// if king?
	{
		if (figure->getDirection() == 0)		// x
		{
			// TODO implement direction 0
			assert(false);
		}
		else if (figure->getDirection() == 1)	// -y
		{
			// castling kings side
			if (fromX == 4 && toX == 6)
			{
				commandExecutor->addCommand(new CmdMoveCommand(7, 7, 5, 7, board));
				commandExecutor->execute();
				++changes;
			}
			// castling queens side
			else if (fromX == 4 && toX == 1)
			{
				commandExecutor->addCommand(new CmdMoveCommand(0, 7, 2, 7, board));
				commandExecutor->execute();
				++changes;
			}
		}
		else if (figure->getDirection() == 2)	// -x
		{
			// TODO implement direction 2
			assert(false);
		}
		else									// y
		{
			// castling kings side
			if (fromX == 4 && toX == 6)
			{
				commandExecutor->addCommand(new CmdMoveCommand(7, 0, 5, 0, board));
				commandExecutor->execute();
				++changes;
			}
			// castling queens side
			else if (fromX == 4 && toX == 1)
			{
				commandExecutor->addCommand(new CmdMoveCommand(0, 0, 2, 0, board));
				commandExecutor->execute();
				++changes;
			}
		}
	}

	return changes;
}
