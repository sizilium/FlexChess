/**
 * @file Shapes.h
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef SHAPES_H
#define SHAPES_H

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/AbstractShape.hpp>

namespace vs
{
namespace core
{
namespace gui
{

/** @class Circle
 * 
 */
class VS_EXPORT Circle : public AbstractShape
{
public:
	Circle();
	virtual ~Circle();
	
	virtual void update(double deltaT);
	
private:
};


/** @class Line
 * 
 */
class VS_EXPORT Line : public AbstractShape
{
public:
	Line();
	virtual ~Line();
	
	virtual void update(double deltaT);

private:
};


/** @class Rectangle
 * 
 */
class VS_EXPORT Rectangle : public AbstractShape
{
public:
	Rectangle();
	virtual ~Rectangle();
	
	virtual void update(double deltaT);
	
private:
};

} // gui
} // core
} // vs

#endif  // SHAPES_H
