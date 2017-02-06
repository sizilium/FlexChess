/**
 * @file ObserverCamera.h
 * @author sizilium
 * @date 22.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OBSERVER_CAMERA_H
#define OBSERVER_CAMERA_H

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/Camera.h>

namespace vs
{
namespace core
{
namespace gl
{

/** @class ObserverCamera
 * A specialized camera for observation. The camera circulates around a looking point with a 
 * specific distance, and two angles. The precondition is that the x-y-plane is the ground and
 * the z axis is up.
 */
class VS_EXPORT ObserverCamera : public Camera
{
public:
	ObserverCamera();
	
	ObserverCamera(float aspect, float fovy, float zNear, float zFar,
	            float angleZ, float angleXY, float distance,
	            base::math::DoubleVector lookAt);
	
	virtual ~ObserverCamera();

	/**
	 * Sets distance between looking point and camera. Value can't be negative (assert)!
	 */
	void setDistance(float distance);

	/**
	 * Adds a distance to the current. Is the result a negative value, it will set to 0 
	 * automatically. 
	 */
	void addDistance(float distance);
	
	/**
	 * Gets the distance between looking point and camera.
	 */
	float getDistance() const;

	/**
	 * Sets the angle around the z axis. 0 degree is the y axis direction, 90 degree the x axis
	 * direction etc. 
	 * @param angleZ A value between 0 and 359. If you set higher or lower values, 
	 * a modulo operation will fix it.
	 */
	void setAngleZ(float angleZ);
	
	/**
	 * Adds an angle to the current. 
	 * @param angleZ A value between 0 and 359. If you set higher or lower values, 
	 * a modulo operation will fix it.
	 */
	void addAngleZ(float angleZ);

	/**
	 * Gets the angle around the z axis (rotation).
	 */
	float getAngleZ() const;
	
	/**
	 * Sets the angle between x-y-plane and camera (heigth).
	 * @angleXY Positive value from 1 - 90 degrees means a topview.
	 */
	void setAngleXY(float angleXY);

	/**
	 * Add an angle to the current.
	 */
	void addAngleXY(float angleXY);
	
	/**
	 * Gets the current angle between x-y-axis and camera (heigth).
	 */
	float getAngleXY() const;

	/**
	 * Print several information to the console:
	 * -the informations from Camera base class
	 * -angleZ
	 * -angleXY
	 * -distance
	 * @see Camera
	 */
	virtual void coutDebug() const;
	
protected:
	float angleZ;
	float angleXY;
	float distance;
	
private:
	// manipulates the position object from derived Camera class.
	void calcPosition();
};

} // gl
} // core
} // vs

#endif  // OBSERVER_CAMERA_H
