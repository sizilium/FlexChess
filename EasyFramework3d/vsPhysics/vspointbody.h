/*
  Name: vsPointBody.h
  Copyright: VS
  Author: Maccesch
  Date: 06.05.05 13:02
  Description: 
*/

#ifndef VSPOINTBODY_H
#define VSPOINTBODY_H

#include "vsmovingpoint.h"

class vsPointBody : public vsMovingPoint
{
	public:
		vsPointBody();
		~vsPointBody();
		
		void setMass(const double x) { mass = x; }
		double getMass() const { return mass; }

		virtual void applyImpulse(vsPointBody body);
		virtual void applyForce(vsDoubleVector f, double deltaT);
		virtual void applyGravity(vsPointBody body, double deltaT);
		
	protected:
		double mass;
};

#endif // VSPOINTBODY_H
