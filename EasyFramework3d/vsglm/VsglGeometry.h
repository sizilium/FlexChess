/*
  Author: Marc-Stefan Cassola
  Startdate: 13.04.05 20:37
  Description: Abstract basic class for model handling
*/

#ifndef VSGL_GEOMETRY_HEADER
#define VSGL_GEOMETRY_HEADER

#include <gl/gl.h>

class VsglGeometry
{
//protected:
	
public:
//	VsglGeometry();
//	~VsglGeometry();
	
	virtual void draw() = 0;
};

#endif
