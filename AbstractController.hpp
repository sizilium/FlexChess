#ifndef ABSTRACTCONTROLLER_H_
#define ABSTRACTCONTROLLER_H_

// includes
#include "Core/Board.h"
#include "Core/Figures.h"
#include "Core/Players.h"

/**
 * Interface for controller. A controller manipulates the core objects like board, players,
 * figure etc. To implement several game rules (mods) each subclass must implement this
 * interface. The StdChessController for example implements the standard chess rules (king check,
 * castling queens side, castling kings side, pawn first move etc.).\n
 * Generally there are two ways to influence the game rules:
 * -# Changing the xml files. Advantages:
 *  - It's easy to use
 *  - Only a restart of the program is required (no compilation of source code)
 * -# Modifiing the source code by subclassing this class (or others). Advantages:
 *  - You can change basical rules like winner detection, special move rules, bonus conditions,
 * anything!
 * 
 * You should hold a reference to a board, players and figures object to accomplish this interface.
 * You don't need to implement anything. Look for the Controller class, and re-use it's 
 * implementation instead of inherit directly from this interface.
 * @see Controller, StdChessController
 */
class AbstractController
{
public:	
	
	/**
	 * Implement the winner detection at this place. The game object must know if a player has
	 * loosed after his turn (to kill them). If all players has loosed, the game object will
	 * signalize the winner.
	 * @return The playerId of the current player (if loosed), or -1 if the current player is
	 * still in game.
	 */
	virtual int checkLooserId() const = 0;
	
	/**
	 * Checks if a move from a coordinate to a target coordinate is allowed. Note: You can use the
	 * standard implementation of the Controller class!
	 * @see Controller
	 */
	virtual bool checkMove(int fromX, int fromY, int toX, int toY) const = 0;
	
	/**
	 * Performs a move from a coordinate to a target coordinate. Remember that you must implement
	 * undo and redo functionality, so you should save the old state of the board and the figures!
	 * @see Controller
	 */
	virtual void move(int fromX, int fromY, int toX, int toY, bool noGraphic = false) = 0;
	
	/**
	 * If an artifical intelligence can't move (or can't find a move) it will call this method
	 * to signalize this. By the next checkLooserId method call you should return the playerId
	 * of this player to kill them.\n
	 * You can use this method to capitulate a game too.
	 */
	virtual void cannotMove() = 0;
	
	/**
	 * Set the next player current. Just call the players method nextPlayer.
	 * @see Players
	 */
	virtual void nextPlayer() = 0;
	
	/**
	 * Marks a player as killed. Just call the players method killPlayer.
	 * @see Players
	 */
	virtual void killPlayer(int playerId) = 0;
	
	/**
	 * Here you will get the needed references to board, figures and players.
	 * The board, figures and players object already will initialize itself. Don't delete this
	 * object with the delete operator (it will deleted automatically) in the destructor or
	 * elsewhere!
	 */
	virtual void init (Board *board, Figures *figures, Players *players) = 0;
	
	/**
	 * Goes back to the last state. A state includes the figures positions, the board assembly
	 * and the players states.
	 * @see Controller
	 */
	virtual void undo(int steps = 1) = 0;
	
	/**
	 * Redo the last undo. You don't need to implement this manually, use the Controller implementation
	 * subclassing from this.
	 * @see Controller
	 */
	virtual void redo(int steps = 1) = 0;
};

#endif /*ABSTRACTCONTROLLER_H_*/
