#ifndef FIGURES_H_
#define FIGURES_H_

// includes
#include "Figure.h"
#include <string>
#include <list>
#include <vs/base/interfaces/Uncopyable.hpp>
#include <vs/core/gl/Color.h>
using namespace vs::core::gl;
using namespace vs::base::interfaces;
using namespace std;

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * This class is simply a container for figures. It will be used by the ReadFiguresXml class
 * to store all kinds of figures. So this is a figures database. The players will get a copy
 * from this stored figures.
 * @see Figure
 */
class Figures : public Uncopyable
{
public:
	Figures();
	
	/**
	 * Deletes all stored figures. 
	 */
	virtual ~Figures();
	
	/**
	 * Calls for all figures the setColor method.
	 * @see Figure
	 */
	void setColorForAll(const Color &color);
	
	/**
	 * Adds a new figure.
	 * @param figure You should allocate the figure on heap and pass a pointer. The destructor 
	 * will delete the figure for you.
	 */
	void addFigure(Figure *figure);
	
	/**
	 * Deletes and removes a figure.
	 * @param figure The figure to delete.
	 */
	void removeFigure(Figure *figure);
	
	/**
	 * Gets a figure by name. The name is given by the figure xml file. Pay attention that each
	 * kind of figure has its own unique name in the xml file!
	 */
	Figure* getFigure(const string &name);
	
	/**
	 * Calls the coutDebug method for each figure, stored in this manager to the std console
	 * (cout).
	 */
	void coutDebug() const;
	
private:
	list<Figure*> figures;
};

#endif /*FIGURES_H_*/
