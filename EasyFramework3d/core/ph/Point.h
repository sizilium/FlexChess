/**
 * @file Point.h
 * Point class contains DoubleVector for coordinates.
 *
*/

#ifndef POINT_H
#define POINT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace core
{
namespace ph
{

/** @class Point
 * contains double x, y, z coordinates
 */
class VS_EXPORT Point
{
protected:
	base::math::DoubleVector coords;

	/**
	 * a hook class wich can implement by subclasses. Use it like a value changed
	 * notify event! Point calls this method whenever coords changed.
	 */
	virtual void pointHasChanged() {};

public:
	Point();
	Point(base::math::DoubleVector coords);
	Point(double x, double y, double z);
	virtual ~Point();

	base::math::DoubleVector getCoords() const { return coords; }
	void setCoords(const base::math::DoubleVector coords) { this->coords = coords; pointHasChanged();}


/**
 * calculates distance between the current Point and another coordinates
 *
 * @param coords
 * coordinates as DoubleVector
 */
	double dist_sqr(const base::math::DoubleVector &coords) const;

/**
 * calculates distance between the current Point and another coordinates
 *
 * @param point
 * coordinates as Point
 */
	double dist_sqr(const Point &point) const { return dist_sqr(point.getCoords()); }
};

} // ph
} // core
} // vs

#endif // POINT_H
