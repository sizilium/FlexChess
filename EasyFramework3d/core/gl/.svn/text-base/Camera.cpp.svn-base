#include <vs/core/gl/Camera.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <assert.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;
using namespace base::math;

Camera::Camera()
{
	mvarIsActive = false;
	theAspect = 1;
	theFovy = 45;
	theZNear = 0.01;
	theZFar = 1000;
	position.setCoords(DoubleVector(0, -10, 0));
	upVec = DoubleVector(0, 0, 1);
	//lookAt.setCoords(0, 0, 0);
	
	applyGlPerspective();
}

Camera::Camera(float aspect, float fovy, float zNear, float zFar,
               DoubleVector position, DoubleVector lookAt)
{
	assert("The aspect of a cam can't be 0!" && aspect != 0.0f);
	assert("The angle of a cam can't be negative!" && fovy >= 0.0f);
	assert("The distance to the near clipping plane can't be negative!" && zNear >= 0.0f);
   	assert("The distance to the far clipping plane can't be negative!" && zFar >= 0.0f);
   	assert("The distance for the far clipping plane must be greater than the near clipping plane!" && zFar >= zNear);      
	
	theAspect = aspect;
	theFovy = fovy;
	theZNear = zNear;
	theZFar = zFar;
	this->position.setCoords(position);
	this->lookAt.setCoords(lookAt);
	
	applyGlPerspective();
}

Camera::~Camera() 
{
	CameraMessage msg;
	msg.toDelete = true;
	msg.cam = this;
	notify(msg);
}

Camera& Camera::operator=(const Camera &)
{
	return *this;
}

ph::Point& Camera::getPositionRef()
{
	return position;
}

ph::Point& Camera::getLookAtRef()
{
	return lookAt;
}

DoubleVector& Camera::getUpVecRef()
{
	return upVec;
}

void Camera::setCoords(const DoubleVector &vec)
{
	position.setCoords(vec);
}

void Camera::setLookAt(const DoubleVector &vec)
{
	lookAt.setCoords(vec);
}

void Camera::setUpVec(const DoubleVector &vec)
{
	upVec = vec;
}

void Camera::setOrientatedPoint(const ph::OrientatedPoint &op)
{
	position.setCoords(op.getCoords());
	// TODO cals look at point from euler
}

DoubleVector Camera::getUpVec() const
{
	return upVec;
}

DoubleVector Camera::getCoords() const
{
	return position.getCoords();
}

DoubleVector Camera::getLookAt() const
{
	return lookAt.getCoords();
}

void Camera::setAspect(float width_div_height)
{
	assert("The aspect of a cam can't be 0!" && width_div_height != 0.0f);
	theAspect = width_div_height;
	applyGlPerspective();
}

void Camera::setAspect(float width, float height)
{
	assert("The heigth for the aspect of a cam can't be 0!" && height != 0.0f);
	theAspect = 1.0f * width / height;
	applyGlPerspective();
}

float Camera::aspect() const
{
	return theAspect;
}

void Camera::setFovy(float angle)
{
	assert("The angle of a cam can't be negative!" && angle >= 0.0f);
	theFovy = angle;
	applyGlPerspective();
}

float Camera::fovy() const
{
	return theFovy;
}

void Camera::setZNear(float nearDistance)
{
	assert("The distance to the near clipping plane can't be negative!" && nearDistance >= 0.0f);
	assert("The distance for the far clipping plane must be greater than the near clipping plane!" &&
	       theZFar >= nearDistance);
	
	theZNear = nearDistance;
	applyGlPerspective();
}

float Camera::zNear() const
{
	return theZNear;
}

void Camera::setZFar(float farDistance)
{
	assert("The distance to the far clipping plane can't be negative!" && farDistance >= 0.0f);
	assert("The distance for the far clipping plane must be greater than the near clipping plane!" &&
	       farDistance >= theZNear);

	theZFar = farDistance;
	applyGlPerspective();
}

float Camera::zFar() const
{
	return theZFar;
}

void Camera::update(double /*deltaT*/)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	
	DoubleVector coords = position.getCoords();
	DoubleVector look = lookAt.getCoords();

	gluLookAt(coords.x(), coords.y(), coords.z(),
			  look.x(), look.y(), look.z(),
			  upVec.x(), upVec.y(), upVec.z());

	//glMatrixMode(GL_MODELVIEW);
}

void Camera::activate()
{
	CameraMessage msg;
	msg.cam = this;
	msg.activateState = true;
	notify(msg);
	
	mvarIsActive = true;
}


void Camera::deactivate()
{
	CameraMessage msg;
	msg.cam = this;
	msg.activateState = false;
	notify(msg);
	
	mvarIsActive = false;
}

void Camera::setName(const string &name)
{
	this->name = name; 
}

string Camera::getName() const
{
	return this->name;
}

bool Camera::isActive() const
{
	return mvarIsActive;
}

void Camera::applyGlPerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(theFovy, theAspect, theZNear, theZFar);
	
	glMatrixMode(GL_MODELVIEW);
}

void Camera::coutDebug() const
{
	cout << "cam name=" << this->getName() << "   active= " << this->isActive() << endl;
	cout << "position= "  << position.getCoords() << endl;
	cout << "look at= " << lookAt.getCoords() << endl;
	cout << "upVec= " << upVec << endl;
	cout << "apect= " << theAspect << "   fovy= " << theFovy << "   zNear= " << theZNear << "   zFar= " << theZFar << endl;
}

} // gl
} // core
} // vs
