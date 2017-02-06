#ifndef PLAYER_H_
#define PLAYER_H_

#include "Figure.h"
#include <string>
#include <vector>
#include <vs/core/gl/Color.h>
using namespace vs::core::gl;
using namespace std;

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * The player represents both: human and computer players. A player is more than a container
 * for figures. A player has a direction, a color (global color for all figures), an id, a name
 * a "killed" state, an absolute position on board and useful getter methods for the figures.
 * Each player hold its own figures on heap (copied from a figures object). Its different to
 * the board wich holds only references to the figures.
 */
class Player
{
public:
	/**
	 * @param name A unique name for the player.
	 * @param id A unique id for the player. Each player must have a different id number.
	 * @param computer Pass true if the player is drived by the computer (arifical intelligence).
	 */
	Player(const string &name, int id, bool computer = false);
	
	/**
	 * Deletes all figures from the heap.
	 */
	virtual ~Player();
	
	/**
	 * Sets the name for the player.
	 */
	string getName() const				{return this->name;}
	
	/**
	 * Sets the reference coordinates of the player. All stored figures depends on this 
	 * coordinate (the game object will set this). Its the absolute player coordinate on 
	 * the board, the lower left referece point for each figure.
	 * @param x X coord for the player.
	 * @param y Y coord for the player.
	 */
	void setRefXY(int x, int y)			{assert(x>=0 && y>=0); this->x = x; this->y = y;}
	
	/**
	 * Sets the players direction. All figures will inherit this direction (the game object
	 * will set this).
	 * - 0 = x (right)
	 * - 1 = -y(down)
	 * - 2 = -x (left)
	 * - 3 = y (up)
	 */
	void setDirection(int direction)	{this->direction = direction;}

	/**
	 * Getter for the x reference coordinate of the player
	 * @return A value between 0 and board x size -1.
	 */
	int getRefX() const					{return this->x;}
	
	/**
	 * Getter for the y reference coordinate of the player
	 * @return A value between 0 and board y size -1.
	 */
	int getRefY() const					{return this->y;}
	
	/**
	 * Sets the color of the player. All stored figures will inherit this color.
	 * @param color Red, green, blue and alpha value between 0.0f and 1.0f.
	 */
	void setColor(const Color &color);
	
	/**
	 * Getter for the player's color (and figures color).
	 * @return Red, green, blue and alpha value between 0.0f and 1.0f.
	 * 
	 */
	Color getColor() const				{return this->color;}
	
	/**
	 * Getter for identifier. Each player has its own unique id.
	 * @return A value between 0 and number of players -1.
	 */
	int getId() const					{return this->id;}

	/**
	 * Getter for the direction.
	 * - 0 = x (right)
	 * - 1 = -y(down)
	 * - 2 = -x (left)
	 * - 3 = y (up)
	 */
	int getDirection() const			{return this->direction;}
	
	/**
	 * Adds a new figure to the player. Use the new operator to add a new figure object. The
	 * object will be deleted automatically in destructor. You can copy a figure from the
	 * figure pool:
	 * @code // Example
	 * // copy a predefined figure from a Figures object (pool)
	 * Figure *newFigure = new Figure( * (figures->getFigure("queen") );
	 * // init the figure
	 * newFigure->setPlayerId(0);
	 * newFigure->createModel();
	 * newFigure->setPos(x, y, false);	// without animation
	 * // add figure to player
	 * player->addFigure(newFigure);
	 * @endcode
	 * @see Figures
	 */
	void addFigure(Figure *figure);
	
	/**
	 * Deletes and removes a figure from the player. Be careful: Don't use the figure anymore 
	 * after the remove!
	 */
	void removeFigure(Figure *figure);
	
	/**
	 * Gets a figure by id. Each figure can have an unique identifier (optional). Check the
	 * return for NULL pointer! If multiple figures with an id stored, the first match will be
	 * returned.
	 * @return NULL if there is no figure with matching id, else a pointer to the figure.
	 */
	Figure* getFigure(int id) const;
	
	/**
	 * Returns a vector stored with all figures of the player (active and inactive figures).
	 * You musn't check for NULL pointer. Simply check the vector's size.
	 * @return A vector with figures (the size represents the number of figures stored in the
	 * player).
	 */
	vector<Figure *> getAllFigures() const;
	
	/**
	 * Returns a vector only stored with all active figures of the player.
	 * You musn't check for NULL pointer. Simply check the vector's size.
	 * @return A vector with figures (the size represents the number of active figures stored +
	 * in the player).
	 */
	vector<Figure *> getActivFigures() const;
	
	/**
	 * Checks if the player have active figures. Else, the player should be marked as killed
	 * (see game rules).
	 * @return True if there are activ figures.
	 */
	bool hasActivFigures() const;
	
	/**
	 * Marks the player as killed. Note that only not killed player comes into operation by a
	 * Game object.
	 */
	void markAsKilled()					{this->killed = true;}
	
	/**
	 * Unmarks the player as killed (useful for the controllers undo functionality).
	 */
	void unmarkAsKilled()				{this->killed = false;}
	
	/**
	 * Checks if the player is already killed. Useful artifical intelligences to check 
	 * if there is a menace.
	 * @return True if the player is out of game.
	 */
	bool isKilled() const				{return this->killed;}

	/**
	 * Checks if the player is controlled by the computer of not.
	 * @return True if an artifical intelligence controll this player.
	 */
	bool isComputer() const				{return computer;}
	
private:
	bool killed;	// is player already in game?
	string name;
	vector<Figure *> figures;
	int id;
	int x, y;		// formation reference point
	int direction;	// 0=x 1=-y 2=-x 3=y
	bool computer;
	Color color;
};

#endif /*PLAYER_H_*/
