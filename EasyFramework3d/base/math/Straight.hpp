#ifndef STRAIGHT_HPP
#define STRAIGHT_HPP

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace math
{

VS_EXPORT DoubleVector intersectStraightWithXZPlane(DoubleVector point, DoubleVector direction, double height) {
    double factor = (height-point[1])/direction[1];
    return point + direction*factor;
}

VS_EXPORT DoubleVector intersectStraightWithXYPlane(DoubleVector point, DoubleVector direction, double height) {
    double factor = (height-point[2])/direction[2];
    return point + direction*factor;
}

VS_EXPORT DoubleVector intersectStraightWithYZPlane(DoubleVector point, DoubleVector direction, double height) {
    double factor = (height-point[0])/direction[0];
    return point + direction*factor;
}

} // math
} // base
} // vs

#endif // STRAIGHT_HPP
