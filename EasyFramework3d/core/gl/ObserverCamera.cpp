#include <vs/core/gl/ObserverCamera.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/base/math/Math.h>
#include <cmath>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;
using namespace base::math;

ObserverCamera::ObserverCamera()
{
	distance = 10;
	angleZ = 180;
	angleXY = 45;
	calcPosition();
}

namespace {DoubleVector tmp;}	//  dummy

ObserverCamera::ObserverCamera(float aspect, float fovy, float zNear, float zFar,
            float angleZ, float angleXY, float distance,
            DoubleVector lookAt)
:Camera(aspect, fovy, zNear, zFar, tmp, lookAt)
{
	this->angleZ = angleZ;
	this->angleXY = angleXY;
	this->distance = distance;
	calcPosition();
}

ObserverCamera::~ObserverCamera()
{
}


void ObserverCamera::setDistance(float distance)
{
	assert (distance >= 0 && "Distance must be greate than 0!");
	this->distance = distance;
	calcPosition();
}

void ObserverCamera::addDistance(float distance)
{
	float newDistance = this->distance + distance;
	if (newDistance < 0)
		newDistance = 0;
	this->distance = newDistance;
	calcPosition();
}

float ObserverCamera::getDistance() const
{
    return distance;
}

void ObserverCamera::setAngleXY(float angleXY)
{
	while (angleXY > 90)
		angleXY = 90;
	while (angleXY < -90)
		angleXY = -90;
    this->angleXY = angleXY;
    calcPosition();
}

void ObserverCamera::addAngleXY(float angleXY)
{
	setAngleXY(getAngleXY() + angleXY);
}

float ObserverCamera::getAngleXY() const
{
    return angleXY;
}

void ObserverCamera::setAngleZ(float angleZ)
{
	while (angleZ > 360)
		angleZ -= 360;
	while (angleZ < 0)
		angleZ += 360;
    this->angleZ = angleZ;
    calcPosition();
}

void ObserverCamera::addAngleZ(float angleZ)
{
	setAngleZ(getAngleZ() + angleZ);
}

float ObserverCamera::getAngleZ() const
{
    return angleZ;
}

void ObserverCamera::calcPosition()
{
	// TODO fix the trigonomie cam problem (toggle by 90° angle) 
	if (angleXY == 90)
		angleXY = 89.9;
	
	float dist = cos ( toRad(angleXY) ) * distance;
	
	float x = sin( toRad(angleZ) ) * dist + this->lookAt.getCoords().x();
	float y = cos( toRad(angleZ) ) * dist + this->lookAt.getCoords().y();
	float z = sin( toRad(angleXY) ) * distance + this->lookAt.getCoords().z();
	
	DoubleVector coords(x, y, z);
	position.setCoords(coords);
}

void ObserverCamera::coutDebug() const
{
	Camera::coutDebug();	// base class
	cout << "angleZ= "  << angleZ << "°" <<  endl;
	cout << "angleXY= " << angleXY << "°" << endl;
	cout << "distance= " << distance << endl;
}

} // gl
} // core
} // vs
