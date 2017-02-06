/*
  Name: vsPoint.cpp
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:08
  Description: 
*/

vsPoint::vsPoint()
: coords()
{
		
}

vsPoint::vsPoint(vsIse x, vsIse y, vsIse z)
: coords(x, y, z)
{
}

vsPoint::vsPoint(vsIseVector coords)
: coords(coords)
{
}

vsPoint::vsPoint(vsDoubleVector coords)
: coords(coords)
{
}

vsPoint::vsPoint(double x, double y, double z)
: coords(x, y, z)
{
}

vsPoint::vsPoint(const vsPoint &point)
: coords(point.coords)
{
}

vsPoint::~vsPoint()
{
}
	
vsIse vsPoint::dist_sqr(const vsIseVector &coords) const
{
	vsIseVector temp = (this->coords - coords);
	return temp.abs_sqr();
}
