#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#define UNDO_STEPS		500		// important for ki

// includes
#include "AbstractController.hpp"
#include <vs/cmd/Command.hpp>
using namespace vs::cmd;

// predeclarations
class Board;
class Figures;
class Figure;
class Players;
namespace vs {namespace cmd {class CommandExecutor;}}

/**
 * A standard controller. The controller simply checks the moves by the given xml file 
 * informations. There are no further special moves (like king check in the StdChessController).
 * A player loose if it has no figures anymore (deathmatch). The controller provides a 
 * CommandExecutor (look for command design pattern for further informations) to implement the
 * undo and redo functionality. You can subclass this class to customize something and creating
 * new game mods.
 */
class Controller : public AbstractController
{
public:
	/**
	 * Creates a new CommandExecutor.
	 * @see vs::cmd::CommandExecutor
	 */
	Controller();
	
	/**
	 * Deletes the CommandExecutor.
	 */
	virtual ~Controller();

	/**
	 * Saves the references to board, figures and players object. It's important for late
	 * checkMoved and move method calls. Initialize the controller first with this method
	 * before using the controller! (else assertions will occure).
	 * @param board With the board you can scan the game field. You can ask if there are 
	 * figures on specific x and y coordinates. 
	 * @param figures This object is only needed by adding new figures to the game. In this case
	 * you can copy a figure from this object, add this to a player (with the players object) and
	 * set a reference to the board object. Note: You must implement a undo/redo functionality!
	 * Use a command to perform this job (look for command design pattern)!
	 * @param players Use this object to scan active figures of a player for example. Maybe
	 * you need this for the checkMove or the checkLooserId method.
	 */
	void init(Board *board, Figures *figures, Players *players);

	/**
	 * The standard implementation is: If a player has no figures, he will loose (kill by the
	 * game object). If there only one player with figures, this player will be the winner.
	 * Another way to mark the winner is the cannotMove method (setted by any artifical
	 * intelligence for example).
	 * @return Player id of looser. Else -1 if the current player is no looser.
	 */
	int checkLooserId() const;
	
	/**
	 * Sets the next player as current.
	 */
	void nextPlayer();
	
	/**
	 * Marks a player as killed.
	 */
	void killPlayer(int playerId);
	
	/**
	 * This important method verifies rules with data read from xml files. 
	 * Specialized rules can be implemented in subclasses (if you want special situations for
	 * special moves like castling kings side in std chess for example).
	 */
	bool checkMove(int fromX, int fromY, int toX, int toY) const;
	
	/**
	 * Moves a figure from a coordinate to a target coordinate.
	 * Only use this method to manipulate the board and the players (do not manipulate the
	 * board and player objects directly), except you want implement your own rules.
	 */
	void move(int fromX, int fromY, int toX, int toY, bool noGraphic = false);
	
	/**
	 * If an artifical intelligence can't move (or can't find a move) it will call this method
	 * to signalize this. By the next checkLooserId method call you should return the playerId
	 * of this player to kill them.\n
	 * The method marks the current player as killed.
	 */
	void cannotMove();

	/**
	 * Replace a figure on board coordinates x and y. If there is no figure an assertion 
	 * failed. 
	 * @param x The x coord of the figure to replace.
	 * @param y The y coord of the figure to replace.
	 * @param newFigureName The name of the new figure (you don't need to create the new
	 * figure manually). Ensure that a figure with this name exists in the xml file.
	 * @param noGraphic Important for ai. Normally this parameter is false, but ai don't need
	 * graphic output so they can disable it for more performance.
	 */
	void replaceFigure(int x, int y, const string &newFigureName, bool noGraphic = false);
	
	/**
	 * The controller implements the undo functionality by using a CommandExecutor.
	 */
	void undo(int steps);
	
	/**
	 * The controller implements the redo functionality by using a CommandExecutor.
	 */
	void redo(int steps);

	/**
	 * Clears the history of the CommandExecutor, means the undo steps.
	 */
	void clearHistory();

protected:
	void calcRelativeFigureMoves(int direction, int fromX, int fromY, int toX, int toY,
	                             short &up, short &down, short &left, short &right) const;
	
	Board *board;
	Figures *figures;
	Players *players;
	CommandExecutor *commandExecutor;
};

#endif /*CONTROLLER_H_*/


// ------------------------- Commands --------------------------------------

class CmdMoveCommand : public Command
{
public:
	CmdMoveCommand(int fromX, int fromY, int toX, int toY, Board *board, bool noGraphic = false);
	void execute();
	void undo();
	const std::string name() const	{return "MoveCommand";}
private:
	Figure *enemyFigure;
	bool movedState;
	int fromX, fromY, toX, toY;
	Board *board;
	bool noGraphic;
};

class CmdReplaceFigureCommand : public Command
{
public:
	CmdReplaceFigureCommand(Figure *oldFigure, const string &newFigureName, 
	                        Figures *figures, Board *board, Player *oldPlayer, 
	                        Player *newPlayer, bool noGraphic = false);
	void execute();
	void undo();
	const std::string name() const	{return "ReplaceFigureCommand";}
private:
	Figure *oldFigure;
	string newFigureName;
	Figures *figures;
	Board *board;
	Player *oldPlayer;
	Player *newPlayer;
	bool noGraphic;
	
	// saved on execute
	int oldX, oldY;
};

class CmdNextPlayer : public Command
{
public:
	CmdNextPlayer(Players *players);
	void execute();
	void undo();
	const std::string name() const	{return "NextPlayer";}
private:
	Players *players;
};

class CmdKillPlayer : public Command
{
public:
	CmdKillPlayer(Players *players, int playerId);
	void execute();
	void undo();
	const std::string name() const	{return "KillPlayer";}
private:
	Players *players;
	int playerId;
};
