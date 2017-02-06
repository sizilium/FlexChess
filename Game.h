#ifndef GAME_H_
#define GAME_H_

// includes
#include <string>
#include <vector>
#include "ArtificalIntelligence/AbstractAI.hpp"
#include <vs/base/interfaces/Uncopyable.hpp>
using namespace vs::base::interfaces;
using namespace std;

// predeclarations
class Figures;
class Players;
class Board;
class AbstractController;

/**
 * A important class for a flexchess game. Stores the board, players (with its figures) a
 * controller and the artifical intelligences (depending on game mode). The game object can get
 * human inputs by the inject methods (cursor moved, cursor klicked etc.). The game object
 * loads the xml files and initiaizes all flexchess core data structures.\n
 * The run method is very important too. At this place the winner will be checked, the human
 * move will perform or an artifical intelligence will started.
 */
class Game : Uncopyable
{
public:
	Game();
	virtual ~Game();
	
	/**
	 * Sets the controller. You must set a controller before using the game object (especially 
	 * the run method). The controller appoints the basically game rules (who is the looser,
	 * wich move is allowed, has figures special abilities etc.).
	 * @param controller Pass a valid controller wich implements the AbstractController interface.
	 * @see Controller, StdChessController
	 */
	void setController(AbstractController *controller);

	/**
	 * Adds a new player to the game. A player can be a computer (ai) or a human. The player id
	 * will be incremented automatically. Only pass the name.
	 * @param name Set the name for the new player.
	 * @param ai Optional parameter. If the player is a computer (ai) create a new artifical
	 * intelligence object (with AbstractAi interface) on the heap and pass the pointer. You
	 * don't need to delete this object, it will be done by the destructor automatically!
	 */
	void addPlayer(const string &name, AbstractAI *ai = NULL);
	
	/**
	 * Checks the winner.
	 * @return NULL if there is no winner at the moment, else the looser player object.
	 */
	Player* getWinner() const;
	
	/**
	 * This is an init method. Before using the game object call this method! Else several
	 * assertion will fail (in best case), because no core data structures are available.
	 * Ensure that the figures, board and formation xml files are available and complete.
	 * Check the xml syntax of these files to prevent exception errors.\n
	 * The method will load the xml file informations and initialize the figures, players and
	 * board data structures.\n
	 * You can load a single xml file too (empty strings will be ignored).
	 */
	void loadXml(const string &pathFigures = "", 
	             const string &pathBoard = "", 
	             const string &pathFormation = "");

	/**
	 * Gets the current player (from the controller) and calls the processMove method if the 
	 * player is a computer.
	 * If the player is a human the run method (wich called regularly in endless loop) waits
	 * for cursor injectStart and cursor injectTarget to perform the user move. The method
	 * checks the winner too (by the controllers method checkLooserId).
	 * @return True if game has no winner at the moment. False if the game is at the end.
	 */
	bool run();
	
	/**
	 * Enables or disables the pause mode. If the game is in pause the run method has no effect.
	 * @param enable Pass true for pause or false for running mode.
	 */
	void setPause(bool enable = true);
	
	/**
	 * Game goes back to the previous state. Board and players will be restored.
	 * This method simply calls the controller's undo method.
	 */
	void undo();
	
	/**
	 * Redo the last undo. This method simply calls the contoller's redo method.
	 */
	void redo();
	
	/**
	 * Resets the cursor injects.
	 */
	void resetInject();
	
	/**
	 * Marks the "from" coordinates for a user move command.
	 * @param fromX The start x coordinate of a figure on the board.
	 * @param fromY The start y coordinate of a figure on the board.
	 */
	void injectStart(int fromX, int fromY);
	
	/**
	 * Marks the "to" coordinates for a user move command. If the injectStart method was valid
	 * and the target is valid too, the next run method call will perform the move!
	 * @param toX The target x coordinate of a figure on the board.
	 * @param toY The target y coordinate of a figure on the board.
	 */
	void injectTarget(int toX, int toY);
	
	/**
	 * Quick check if a figure eventually can move or not. The method simply checks if a figure
	 * is associated with the current player. A player can only move it's own figures of course.
	 * @return False if a move is impossible or true if a move eventually is possible.
	 */
	bool checkMove(int fromX, int fromY) const;
	
	/**
	 * Checks if a move is allowed or not. This method simply calls the controller checkMove
	 * method. Dependend of the controller this method could takes some time.
	 * @see Controller, StdChessController
	 */
	bool checkMove(int fromX, int fromY, int toX, int toY) const;
	
	/**
	 * Gets the board x and y size (by standard chess 8 x 8).
	 * @return The first value is x, the second value is y.
	 */
	pair<int, int> getBoardDimenstions() const;
	
	/**
	 * Prints some figure information to the std console (cout).
	 */
	void coutDebugFigures() const;
	
	/**
	 * Prints some player information to the std console (cout).
	 */
	void coutDebugPlayers() const;
	
	/**
	 * Prints some board information to the std console (cout).
	 */
	void coutDebugBoard() const;
	
	void coutPoints() const;
	
private:
	void populateBoardWithPlayers(Board *board, Players *players);
	
	int idCount;
	bool pause;
	int fromX, fromY, toX, toY;
	
	Figures *figures;
	Players *players;
	vector<AbstractAI*> artificalIntelligences;
	
	Board *board;

	AbstractController *controller;
};

#endif /*GAME_H_*/
