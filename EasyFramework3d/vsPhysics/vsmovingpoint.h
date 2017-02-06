/*
  Name: vsMovingPoint.h
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:06
  Description: 
*/

#ifndef VSMOVINGPOINT_H
#define VSMOVINGPOINT_H

#include "vspoint.h"

class vsMovingPoint : public vsPoint
{
	public:
		vsMovingPoint();
		vsMovingPoint(const vsMovingPoint &point);
		~vsMovingPoint();
		
		vsDoubleVector getV() const { return v }
		void setV(const vsDoubleVector v) { this->v = v }

		// should be called before move (if i remember correctly)
		virtual void applyAccel(const vsDoubleVector a, const double deltaT);
		virtual void move(const double deltaT);
		
	protected:
		vsDoubleVector v;
};

#endif // VSMOVINGPOINT_H
