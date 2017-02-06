#ifndef PLAYERS_H_
#define PLAYERS_H_

// includes
#include <vs/base/interfaces/Uncopyable.hpp>
#include <vector>
using namespace vs::base::interfaces;
using namespace std;


// predeclaration
class Player;

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * This class simply represents a container for players. All player object will stored in this
 * container (on the heap). The class hold a reference to the current player too. With the
 * nextPlayer method you can set the next player (modulo operation). Also you can check if there
 * is a winner.
 */
class Players : Uncopyable
{
public:
	Players();
	
	/**
	 * Deletes all player object from the heap (you don't have to delete the player object
	 * manually!).
	 */
	virtual ~Players();
	
	/**
	 * Adds a new player object to this container. 
	 * @param player Create the new player on the heap with the new operator. 
	 */
	void addPlayer(Player *player)			{players.push_back(player);}

	/**
	 * Marks a player as killed. The player won't be deleted!
	 * @param playerId Pass the unique player id. If the id not exist, a warning will be printed to
	 * the console.
	 */
	void killPlayer(int playerId);
	
	/**
	 * Gets a player. Check the return value for NULL pointer (in case the player wasn't found)!
	 * @return NULL if there is no player with the given id.
	 */
	Player* getPlayer(int playerId) const;
	
	/**
	 * Returns a vector stored with player references. You musn't check for NULL pointer, simply
	 * check the vector's size (it represents the number of players too).
	 * @return All player objects stored in this container.
	 */
	vector<Player*> getAllPlayers() const	{return players;}
	
	/**
	 * Returns a vector stored with all enemy player references. The return depends of the 
	 * current player (all others are enemies). 
	 * @return All enemy player objects stored in this ocntainer.
	 */
	vector<Player*> getAllEnemyPlayers() const;
	
	/**
	 * Returns the current player.
	 * @return NULL pointer if there are no player objects in this container.
	 */
	Player* getCurrentPlayer() const;
	
	/**
	 * Sets the next player current (modulo operation).
	 */
	void nextPlayer();
	
	/**
	 * Sets the previous player current (modulo operation). Useful for the controllers undo
	 * functionality.
	 */
	void previousPlayer();
	
	/**
	 * Little help method. Checks if there is a winner at the moment (in case all player object
	 * marked as killed, except one player).
	 * @return True if there is a winner and the game is ended.
	 */
	bool checkWinner() const;
	
	/**
	 * If checkWinner return true, you can get the winner player with this method.
	 * @return NULL if there is no winner at the moment.
	 */
	Player *getWinner() const;
	
	/**
	 * Print several informations to the std console (cout).
	 */
	void coutDebug() const;
	
private:
	int currentPlayerId;
	vector<Player*> players;
};

#endif /*PLAYERS_H_*/
