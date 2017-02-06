#ifndef BOARD_H_
#define BOARD_H_

// includes
#include <vs/base/cont/Matrix.hpp>
#include <vs/base/interfaces/Uncopyable.hpp>
using namespace vs::base::interfaces;
using namespace vs::base::cont;

// predeclarations
class Figure;

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * The Board class represents the game board. Here you can check the fields beginning with
 * 0, 0 (lower left). You should only use the getFigure method!
 */
class Board : Uncopyable
{
public:
	Board();
	virtual ~Board();
	/**
	 * Sets the board dimensions.
	 */
	void init(int sizeX, int sizeY);
	
	/**
	 * Sets a pointer to an existing figure to a specific field position.
	 * @param x The x coord (with assertion safety).
	 * @param y The y coord (with assertion safety).
	 * @param figure A pointer to a figure. Do not add a figure with the new operator! This class
	 * does not delete the figures! There are only references.
	 */
	void setFigure(int x, int y, Figure *figure);
	
	/**
	 * Gets a figure from a specific position. 
	 * @param x The x coord (with assertion safety).
	 * @param y The y coord (with assertion safety).
	 * @return NULL if there is no figure on the given position.
	 */
	Figure* getFigure(int x, int y) const;
	
	/**
	 * @return Gets the game board width (x dimension).
	 */
	int getSizeX() const	{return board.numColumns();}
	
	/**
	 * @return Gets the game board heigth (y dimension).
	 */
	int getSizeY() const	{return board.numRows();}
	
	/**
	 * Removes all references to the figures, the game board dimension (x and y size) will be 
	 * unchanged.
	 */
	void clear();
	
	/**
	 * Prints the game board as a matrix to the std console (cout). The figures player ids will
	 * be shown (if there is no player a 0 will be printed for the position).
	 */
	void coutDebug() const;
	
private:
	Matrix<Figure*> board;
};


#endif /*BOARD_H_*/
