/**
 * @file Camera.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_CAMERA_H
#define VS_CAMERA_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/Point.h>
#include <vs/core/ph/OrientatedPoint.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/interfaces/MsgObservable.hpp>
#include <string>

namespace vs
{
namespace core
{
namespace gl
{
// predeclarations
class CameraMessage;

/** @class Camera
 * This class encapsulates all basic cam qualities like position, lookAt point, 
 * OpenGl specific settings etc.\n
 * To set the cams direction you can use the getLookAtRef() method and change the
 * coords regularly or the setLookAt() method to change the direction one time.
 * The update method will apply all settings to OpenGl (the manager calls the update
 * automatically, you don't need them). Because this Camera is an DefaultManaged it 
 * can be activated and deactivated. Do not activate two cams at the same time! Else
 * you get a undesirable flicker effect or you have a wrong visibility.\n 
 * There are many assertion checks in this class, if you don't want them type \#define NDEBUG
 * in this header and build a new EasyFramework library. 
 */
class VS_EXPORT Camera : 	public base::interfaces::AbstractManaged, 
							public base::interfaces::MsgObservable<CameraMessage>, 
							public base::interfaces::Updateable
{
public:
	/**
	 * The standard settings at the beginninng are:
	 * - aspect = 1 (width/heigth)
	 * - fovy = 45 degree (angle from viewer position)
	 * - zNear = 0.01 (near clipping plane)
	 * - zFar = 1000 (far clipping plane)
	 * - position = (0, -10, 0)
	 * - lookAt   = (0,  0,  0)
	 * - upVec    = (0,  0,  1)
	 */
	Camera();
	
	/**
	 * Constructor for user defined init settings.
	 * @param aspect Specifies the aspect ratio that determines the field of view
	 * in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	 * @param fovy Specifies the field of view angle, in degrees, in the y direction.
	 * @param zNear Specifies the distance from the viewer to the near clipping plane
	 * (always positive).
	 * @param zFar Specifies the distance from the viewer to the far clipping plane 
	 * (always positive).
	 * @param position Pass the coords for the viewer position here.
	 * @param lookAt Pass the coorkd for the viewr lookAt point here.
	 */
	Camera(float aspect, float fovy, float zNear, float zFar,
	            base::math::DoubleVector position, 
	            base::math::DoubleVector lookAt);
	
	virtual ~Camera();
	
	Camera& operator=(const Camera &op2);
	
	/**
	 * Gets a reference to the cams position. Useful for constraints for example.
	 * @return The position reference.
	 */
	ph::Point& getPositionRef();
	
	/**
	 * Gets a reference to the cams looking point. Useful for constraint for example.
	 * @return The looking point reference.
	 */
	ph::Point& getLookAtRef();
	
	/**
	 * Gets a reference to the cams "up vector".
	 * @return A reference to the up vector.
	 */
	base::math::DoubleVector& getUpVecRef();
	
	/**
	 * Sets the position of the cam/viewer to the specified coordinates. To see the
	 * result an update is necessary.
	 */
	void setCoords(const base::math::DoubleVector &vec);
	
	/**
	 * Sets the looking point of the cam/viewer to the specified coordinates. To see the
	 * result an update is necessary.
	 */
	void setLookAt(const base::math::DoubleVector &vec);
	
	/**
	 * Sets the "up vector" to specifiy the "up" axis. For example if the up vector
	 * is (0, 0, 1) the z-axis is up.
	 */
	void setUpVec(const base::math::DoubleVector &vec);
	
	/**
	 * Sets a OrientatedPoint (position + rotation), means the look at point automatically
	 * will be calculated. 
	 */
	void setOrientatedPoint(const core::ph::OrientatedPoint &op);
	
	// TODO? Quaternions?
	
	/**
	 * Getter for the actual cam/viewer position.
	 * @return x, y, z values in a DoubleVector.
	 */
	base::math::DoubleVector getCoords() const;
	
	/**
	 * Getter for the actual cam/viewer looking point.
	 * @return x, y, z values in a DoubleVector.
	 */
	base::math::DoubleVector getLookAt() const;
	
	/**
	 * Getter for the actual "up vector" of the cam/viewer.
	 */
	base::math::DoubleVector getUpVec() const;
	
	/**
	 * Specifies the aspect ratio that determines the field of view in the x direction.
	 * The aspect ratio is the ratio of x (width) to y (height).\n
	 * Of course you can use the OpenGl 
	 * gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	 * method directly.
	 */
	void setAspect(float width_div_height);
	
	/**
	 * Overloaded method. Calcs and sets the aspect. (With division to 0 check).
	 * @param width x size of the window.
	 * @param height y size of the window. 
	 */
	void setAspect(float width, float height);
	
	/**
	 * Gets the actual aspect ratio.
	 * @return A positive float value. 1 if width is equal as heigt, >1 if width is
	 * greater than height, <1 if widht is lower than height.
	 */
	float aspect() const;
	
	/**
	 * Specifies the field of view angle, in degrees, in the y direction.\n
	 * Of course you can use the OpenGl 
	 * gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	 * method directly.
	 */
	void setFovy(float angle);
	
	// TODO : change theses getters to our default getters-style (get...)
	/**
	 * Gets the actual fovy (view angle in degree).
	 * @return A positive float value in degree.
	 */
	float fovy() const;

	/**
	 * Specifies the distance from the viewer to the near clipping plane
	 * (always positive).\n
	 * Of course you can use the OpenGl 
	 * gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	 * method directly.
	 */
	void setZNear(float nearDistance);

	/**
	 * Gets the distance from the viewer to the near clipping plane.
	 * @return A positive float value for distance.
	 */
	float zNear() const;

	/**
	 * Specifies the distance from the viewer to the far clipping plane 
	 * (always positive).\n
	 * Of course you can use the OpenGl 
	 * gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	 * method directly.
	 */
	void setZFar(float farDistance);

	/**
	 * Gets the distance from the viewer to the far clipping plane.
	 * @return A positive flaot value for distance.
	 */
	float zFar() const;

	/**
	 * Important method of this class: Sets the cam to the actual position and 
	 * orientate it to the actual looking point (by calling OpenGl's glu function
	 * gluPerspective(...) ).\n
	 * If you use the EasyFramework managers and/or context you don't need an update
	 * manually. 
	 * @see vs::Context
	 */
	void update(double deltaT = 0);

	/**
	 * Activates the cam. This means eventually that another cam will be deactivated.
	 * Only one cam can be activ at the same time per context. So this is a switch
	 * method.
	 */
	void activate();

	/**
	 * Deactivates the cam. This means that currently no cam is activ (you will see
	 * nothing in the correlating context.
	 */
	void deactivate();

	/**
	 * Sets the name of the cam.
	 * @param name The name of the cam. Use different names for each cam.
	 */
	void setName(const std::string &name);

	/**
	 * Gets the name of the cam.
	 * @return The name. Note that an unnamed cam returns an empty string.
	 */
	std::string getName() const;
	
	/**
	 * Check if active in the current context.
	 * @return True if the cam currently is active. 
	 */
	bool isActive() const;
	
	/**
	 * Print several information to the console:
	 * - position vector
	 * - looking point vector
	 * - axis up vector
	 * - aspect, fovy, znear, zfar
	 */
	void coutDebug() const;
	
protected:	
	std::string name;
	
	bool mvarIsActive;
	
	float theAspect;
	float theFovy;
	float theZNear;
	float theZFar;
	
	// Applies the opengl matrix for perspective.
	// Method is calling whenever a setting has changed.
	void applyGlPerspective();

	ph::Point position;
	ph::Point lookAt;
	base::math::DoubleVector upVec;
};


class VS_EXPORT CameraMessage
{
public:
	CameraMessage()
	{
		cam = NULL;
		activateState = false;
		toDelete = false;
	}
	
	Camera *cam;
	bool activateState;
	bool toDelete;
};

} // gl
} // core
} // vs

#endif  // VS_CAMERA_H
