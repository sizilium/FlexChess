#include <vs/core/ph/Point.h>

namespace vs
{
namespace core
{
namespace ph
{
using namespace base::math;

Point::Point()
:coords()
{

}

Point::Point(double x, double y, double z)
:coords(x, y, z)
{
    pointHasChanged();
}

Point::Point(DoubleVector coords)
{
    this->coords = coords;
    pointHasChanged();
}

Point::~Point()
{
}

double Point::dist_sqr(const DoubleVector &c2) const
{
    return sqrt((c2.x() - coords.x()) * (c2.x() - coords.x()) +
                (c2.y() - coords.y()) * (c2.y() - coords.y()) +
                (c2.z() - coords.z()) * (c2.z() - coords.z()) );
}

} // ph
} // core
} // vs
