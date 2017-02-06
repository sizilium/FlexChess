/*
  Name: vsMovingPoint.cpp
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:07
  Description: 
*/

#include "vsmovingpoint.h"

vsMovingPoint::vsMovingPoint()
: vsPoint(), v()
{
}

vsMovingPoint::~vsMovingPoint()
{
}

vsMovingPoint::vsMovingPoint(const vsMovingPoint &point)
: vsPoint(point), vx(point.vx), vy(point.vy), vz(point.vz)
{
}


void vsMovingPoint::applyAccel(const vsDoubleVector a, const double deltaT)
{
	v += a * deltaT;
}


void vsMovingPoint::move(const double deltaT)
{
	coords += v * deltaT;
}
