#include <vs/core/ph/MovingPoint.h>

namespace vs
{
namespace core
{
namespace ph
{
using namespace base::math;

MovingPoint::MovingPoint()
{
}

MovingPoint::~MovingPoint()
{
}

void MovingPoint::applyAccel(const DoubleVector a, const double deltaT)
{
	v += a * deltaT;
}


void MovingPoint::update(const double deltaT)
{
	coords += v * deltaT;
}

} // ph
} // core
} // vs
