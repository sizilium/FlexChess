/*
  Name: vsPointBody.cpp
  Copyright: VS
  Author: Maccesch
  Date: 06.05.05 13:02
  Description: 
*/

#include "vspointbody.h"

vsPointBody::vsPointBody()
{
}

vsPointBody::~vsPointBody()
{
}

void vsPointBody::applyForce(const vsDoubleVector &f, const double deltaT)
{
	// f = m*a  =>  a = f/m
	applyAccel(f * (1/mass), deltaT);
}

void vsPointBody::applyImpulse(const vsPointBody &body)
{
	// TODO : Impuls
	
	v = (body.getV()*body.getMass()) / mass;
}

void vsPointBody::applyGravity(const vsPointBody &body, const double deltaT)
{
	applyAccel(VS_GRAVITY_CONST * body.getMass() / dist_sqr(body));
}
