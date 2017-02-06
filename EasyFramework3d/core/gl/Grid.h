/**
 * @file Grid.h
 * @author sizilium
 * @date 29.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef GRID_H
#define GRID_H

// includes
#include <vs/Build.hpp>
#include <GL/gl.h>
#include <vs/core/gl/Color.h>
#include <vs/core/ph/OrientatedPoint.h>
#include <vs/base/util/DefaultManaged.h>
#include <assert.h>

namespace vs
{
namespace core
{
namespace gl
{

#define AXIS_DEFAULT_LENGTH		99999;
#define DEFAULT_RANGE			1000;
#define DEFAULT_STEP			10;

	
class VS_EXPORT Plane
{
public:
	Plane();
	
	void draw(bool withoutMidLine = false);

	void setStep(double step)		{ assert(step > 0); this->step = step; }
	double getStep() const			{ return step; }

	void setMin(double min)			{ assert(min < 0); this->min = min; }
	double getMin() const			{ return min; }

	void setMax(double max)			{ assert(max > 0); this->max = max; }
	double getMax() const			{ return max; }

private:
	double min, max;
	double step;
};
	
	
/** @class Grid
 * 
 */
class VS_EXPORT Grid : public core::ph::OrientatedPoint, public base::util::DefaultManaged
{
public:
	Grid();
	virtual ~Grid();

	void enableAxis(bool enable)		{ axis = enable; }
	void setAxisLength(double length)	{ axisLength = length; }
	double getAxisLength() const		{ return axisLength; }
	bool isAxis() const					{ return axis; }

	void setPlaneXy(Plane *plane)		{ isXyPlane = true; xyPlane = plane; }
	void setPlaneXz(Plane *plane)		{ isXzPlane = true; xzPlane = plane; }
	void setPlaneYz(Plane *plane)		{ isYzPlane = true; yzPlane = plane; }

	bool getPlaneXy(Plane *&plane);
	bool getPlaneXz(Plane *&plane);
	bool getPlaneYz(Plane *&plane);

	void setColorXy(Color color)		{ xyColor = color; }
	void setColorXz(Color color)		{ xzColor = color; }
	void setColorYz(Color color)		{ yzColor = color; }
	Color getColorXy() const			{ return xyColor; }
	Color getColorXz() const			{ return xzColor; }
	Color getColorYz() const			{ return yzColor; }
	
	void update(double deltaT = 0);

private:
	bool axis;
	double axisLength;
	bool isXyPlane;
	bool isXzPlane;
	bool isYzPlane;

	Plane *xyPlane;
	Plane *xzPlane;
	Plane *yzPlane;
	Color xyColor;
	Color xzColor;
	Color yzColor;
};


} // gl
} // core
} // vs

#endif	// GRID_H
