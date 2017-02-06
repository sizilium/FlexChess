/*
  Name: vsBody.h
  Copyright: VS
  Author: Maccesch
  Date: 07.05.05 00:25
  Description: 
*/

#ifndef VSBODY_H
#define VSBODY_H

#include "vspointbody.h"

class vsBody : public vsPointBody
{
	public:
		vsBody();
		~vsBody();
		
		void setRot(const vsDoubleVector x) { rot = x; }
		vsDoubleVector getRot() const { return rot; }

		void setSpin(const vsDoubleVector x) { spin = x; }
		vsDoubleVector getSpin() const { return spin; }

		virtual void applyForce(const vsIseVector fCoords, const vsDoubleVector f);
		virtual void applyImpulse(const vsPointBody body);
		virtual void applyImpulse(const vsBody body);
		// TODO : Brauchen wir diese Methoden?
		//virtual void applySpinAccel(const double spinA, const vsDoubleVector axis);
		//virtual void applyTorque(const vsIseVector fCoords, const double f);
		
	protected:
		vsDoubleVector rot;
		vsDoubleVector spin;
};

#endif // VSBODY_H
