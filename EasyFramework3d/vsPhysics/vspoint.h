/*
  Name: vsPoint.h
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:08
  Description: 
*/

#ifndef VSPOINT_H
#define VSPOINT_H

#include "vsIseVector.h"
#include "vIse.h"

/**
 * Basic point class.
 */
class vsPoint
{
protected:
	vsIseVector coords;
	
public:
	vsPoint();
	vsPoint(const vsPoint &point);
	~vsPoint();
	
	vsIseVector getCoords() const {	return coord; }
	void setCoords(const vsIseVector coords) { this->coords = coords; }

	
	vsIse dist_sqr(const vsIseVector &coords) const;
	vsIse dist_sqr(const vsPoint &point) const { return dist_sqr(vsPoint.getCoords()); }
;
	
	// TODO : normale distanz - sqrt (ise*ise) für ise entwickeln
};

#endif // VSPOINT_H
