#ifndef FIGURE_H_
#define FIGURE_H_

// includes
#include "Rules.h"
#include <string>
#include <list>
#include <assert.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/core/gl/Color.h>
using namespace vs::core::gl;
using namespace vs::managed::gl::model;
using namespace std;

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * Here you can get a lot of informations about a figure like name, id, direction (given by the
 * player direction), position, possible moves etc. You should only use the "reading" methods
 * (marked with const) to keep the data structures.\n
 * The figure also provides the opengl graphic (no mvc architecture).
 */
class Figure
{
public:
	/**
	 * 
	 */
	Figure(const string &name, const string &geometry, double weight, Rules rules, 
	       short id = -1, short direction = 3, short playerId = -1);
	~Figure();
	
	/**
	 * Creates a vsm model. This method should be called only one time and before the first
	 * setPos method call! Do not care about this method...
	 */
	void createModel();
	
	/**
	 * Gets the vsm model (opengl graphic model generated with Blender). It's unimportand for
	 * algorithms...
	 * @return A vsm reference.
	 */
	ManagedModel* getModel() const					{return this->model;}
	
	/**
	 * Sets the color of the figure. The graphic will be updated directly. All figures should
	 * have the player's color.
	 */
	void setColor(const Color &color);
	
	/**
	 * Returns the figures name read by the figures xml file. The names should be clear without 
	 * ambiguity (for example king, pawn, queen etc.)
	 */
	string getName() const		{return name;}
	
	/**
	 * Optional feature, like the getName method but for more performance. The id should be 
	 * clear without ambiguity.
	 * To use ids for the figure, write the accordant xml tag entry in the figures xml file.
	 */
	short getId() const			{return id;}
	
	/**
	 * Sets the figures direction. Should be the same like the player's direction.
	 * @param direction
	 *  - 0 = x (right)
	 *  - 1 = -y(down)
	 *  - 2 = -x (left)
	 *  - 3 = y (up)
	 */
	void setDirection(short direction);
	
	/**
	 * Getter for direction.
	 * @return direction
	 *  - 0 = x (right)
	 *  - 1 = -y(down)
	 *  - 2 = -x (left)
	 *  - 3 = y (up)
	 */
	short getDirection() const	{return direction;} 
	
	/**
	 * Sets the x and y position of the figure. Only the controller should call this method!
	 * @param x The target x coord.
	 * @param y The target y coord.
	 * @param withAnimation Enables smooth figure animation.
	 * @param noGraphic Disable the graphic. Useful for artifical intelligences when calcing
	 * future moves.
	 */
	void setPos(int x, int y, bool withAnimation = true, bool noGraphic = false);
	
	/**
	 * Gets the actual x position on the board (absolute position).
	 */
	int getPosX() const			{return x;}
	
	/**
	 * Gets the actual y position on the board (absolute position).
	 */
	int getPosY() const			{return y;}

	/**
	 * A figure will be marked by the first move. Useful for the std rules for example: The
	 * pawn can move two up steps at the beginning (when not marked as moved).
	 */
	void markMoved()			{moved = true;}
	
	/**
	 * Unmarks the figure (used by the controllers undo method).
	 */
	void unmarkMoved()			{moved = false;}
	
	/**
	 * Checks if the figure is moved anytime in a game.
	 */
	bool isMoved() const		{return moved;}

	/**
	 * Gets the figures weight (the theoretical cost). Very important for some artifical
	 * intelligences. The weight will read from figures xml file. The quality of some ai
	 * algorithms based on this value. In std chess the king for example has an infinite 
	 * value, the pawn the value 1 etc.
	 */
	double getWeight() const	{return weight;}
	
	/**
	 * Sets the player id. Assure that the id goes with the player's color.
	 */
	void setPlayerId(int id)	{playerId = id;}
	
	/**
	 * Gets the player id. Useful to check if the figure is mine or an enemy!
	 */
	short getPlayerId() const	{return playerId;}

	/**
	 * Checks if a move (not attack) is possible. Depends on the current position.
	 * This method expected relative move values.
	 * @param up Number of relativ forward steps.
	 * @param down Number of relativ backward steps.
	 * @param left Number of relativ sideward steps.
	 * @param right Number of relativ sideward steps.
	 * @param withJump Requres the move a jump (not all figures provide this feature)?
	 * @param withHover TODO not implemented yet
	 * @return True if the move is possible (for the figure purpose), else false.
	 */
	bool checkMove(short up, short down, short left, short right, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Checks if a move (not attack) to an absolute board coordinate is possible.
	 * @param toX Absolute x target position on board.
	 * @param toY Absolute y target position on board.
	 * @param withJump Requres the move a jump (not all figures provide this feature)?
	 * @param withHover TODO not implemented yet
	 * @return True if the move is possible (for the figure purpose), else false.
	 */
	bool checkMove(int toX, int toY, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Checks if an attack move is possible. Depends on the current position.
	 * @param up Number of relativ forward steps.
	 * @param down Number of relativ backward steps.
	 * @param left Number of relativ sideward steps.
	 * @param right Number of relativ sideward steps.
	 * @param withJump Requres the move a jump (not all figures provide this feature)?
	 * @param withHover TODO not implemented yet
	 * @return True if the move is possible (for the figure purpose), else false.
	 */
	bool checkAttackMove(short up, short down, short left, short right, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Checks if a attack move to an absolute board coordinate is possible.
	 * @param toX Absolute x target position on board.
	 * @param toY Absolute y target position on board.
	 * @param withJump Requres the move a jump (not all figures provide this feature)?
	 * @param withHover TODO not implemented yet
	 * @return True if the move is possible (for the figure purpose), else false.
	 */
	bool checkAttackMove(int toX, int toY, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Returns all absolute coords the figure could move to.
	 * Includes jump, hover moves too. Check the coords with the Controller methods 
	 * checkMove or checkAttackMove to validate this possibilities.
	 */
	vector<pair<int, int> > getPossibleMoves() const;
	
	/**
	 * Returns all absolute coords the figure could attack to.
	 * Includes jump, hover moves too. Check the coords with checkMove or checkAttack move
	 * to validate!
	 */
	vector<pair<int, int> > getPossibleAttackMoves() const;
	
	/**
	 * Prints some figure information to the std console (cout).
	 */
	void coutDebug() const;

private:
	vector<pair<int, int> > getPossibleActions(const vector<Rule> *vec) const;
	
	string name;
	string geometry;
	int x, y;			// if (-1,-1), the figure was killed (not on board)
	bool moved;
	float weight;
	Rules rules;
	short id;			// optional (for more performance by figure searching)
	short direction;	// 0=x 1=-y 2=-x 3=y
	short playerId;	// -1 when there is no owner already
	
	// geometry stuff
	unsigned int modelId;
	ManagedModel *model;
	bool activ;
};

#endif /*FIGURE_H_*/
