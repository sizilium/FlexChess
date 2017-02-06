/*
  Name: vsBody.cpp
  Copyright: VS
  Author: Maccesch
  Date: 07.05.05 00:25
  Description: 
*/

#include "vsbody.h"

vsBody::vsBody()
{
}

vsBody::~vsBody()
{
}

void vsBody::applyForce(const vsIseVector fCoords, vsDoubleVector f)
{
	vsDoubleVector relCoords = (fCoords - coords).toDoubleVector();
	// TODO : Dreh-Moment usw.
}

void vsBody::applyImpulse(const vsBody body)
{
	// TODO : Dreh-Impuls usw.
}

void vsBody::applyImpulse(const vsPointBody body)
{
	// TODO : Dreh-Impuls usw.
}
