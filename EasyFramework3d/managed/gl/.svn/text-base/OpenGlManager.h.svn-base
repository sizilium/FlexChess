/**
 * @file OpenGlManager.h
 * @author sizilium
 * @date 04.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OPENGL_MANAGER_H
#define OPENGL_MANAGER_H

// include
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>
#include <vs/core/gl/Camera.h>
#include <vs/core/gl/Color.h>
#include <iostream>
#include <list>

namespace vs
{
// predeclarations
namespace base {namespace interfaces { class AbstractManaged; }}
namespace core {namespace gl {class OpenGlSettings;}}

namespace managed
{
namespace gl
{

/** @class OpenGlManager
 * This manager handles opengl stuff like cameras, lights and common opengl settings (states).
 * The order for camera updating and scene drawing (and eventually gui drawing) is important!
 * The context make sure that this order will kept.
 * @see OpenGlSettings
 */
class VS_EXPORT OpenGlManager : public base::interfaces::AbstractManager<OpenGlManager>,
								public base::interfaces::MsgObserver<core::gl::CameraMessage>
{
public:
	OpenGlManager();
	virtual ~OpenGlManager();
	
	/**
	 * Gets all names actually stored in the manager. With the names you can get
	 * access to the managed using getManaged(name) method. Note that these methods
	 * are not optimal for performance. Use handler (pointer) to the managed instead.
	 * @param names Pass any vs container.
	 * @code // Example
	 * ...
	 * List<string> myList;
	 * myManager->getManagedNames(&myList);
	 * ...
	 * @endcode
	 */
	void getManagedNames(base::cont::JavaStyleContainer<std::string> *names) const;
	
	/**
	 * Getter for managed elements.
	 * @name The search string of the managed.
	 * @return A pointer to the managed or a NULL pointer if the managed name not exist.
	 */
	base::interfaces::AbstractManaged* getManaged(const std::string &name) const;
	
	/**
	 * Getter for cameras.
	 * @name The search string of the cam.
	 * @return A pointer to the cam or a NULL pointer if the cam name not exist.
	 */
	core::gl::Camera* getCamera(const std::string &name) const;
	
	/**
	 * Getter for the current camera.
	 * @return A pointer to the cam or a NULL pointer if there is no current cam.
	 */
	core::gl::Camera* getCurrentCamera() const;
	
	/**
	 * Checks if there is an activated camera.
	 * @return True if there is an activated camera.
	 */
	bool isActivCamera() const;
	
	/**
	 * This method handles CameraMessage's. Even when a cam is activated, deactivate
	 * or deleted.
	 * @param message The special CameraMessage told the handle what kind of event is
	 * sent.
	 */
	void notify(core::gl::CameraMessage &message);
	
	/**
	 * Removes an element from the manager finally (no deactivate).
	 * @name The search string of the managed. If the managed does not exist nothing
	 * will happen.
	 */
	void removeManaged(const std::string &name);
	
	/**
	 * Removes a camera from the manager finally (no deactivate).
	 * @name The search string of the camera. If the cam does not exist nothing 
	 * will happen.
	 */
	void removeCamera(const std::string &name);
	
	/**
	 * This method clears all managed from the manager.
	 */
	void clear();
	
	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "OpenGlManager"; }
	
	/**
	 * Updates the manager and with this all containing managed elements. Note that
	 * the Context::update will update this automatically.
	 */
	void update(double deltaT);
	
	/**
	 * Updates the viewport. This is importand for the cameras aspect ratio. The OpenGlManger
	 * redirect this information to the cameras.
	 */
	void injectViewport(int x, int y, int width, int height);
	
	/**
	 * Gets the OpenGlSettigns object if it exist.
	 * @return NULL if there are no settings.
	 */
	core::gl::OpenGlSettings* getOpenGlSettings() const;
	
	/**
	 * Returns a list of light names, stored in this manager. With this names you can get the
	 * specific lights with the getManaged method for example.
	 */
	std::list<std::string> getLightNames() const;
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
	
private:
	friend class AbstractOpenGlFactory;
	/**
	 * Adds a managed element to the manager. The method is private. 
	 * Only the AbstractOpenGlFactory's (sub classes) can use this operation!
	 */
	void addManaged(base::interfaces::AbstractManaged *managed);
	
	/**
	 * Adds a cam to the manager (deactivated). The method is private.
	 * Only the AbstractOpenGlFactory's (sub classes) can use this operation!
	 */
	void addCamera(core::gl::Camera *cam);
	
	/**
	 * Sets a OpenGlSettings object. Only one object is possible at the same time.
	 * If there are already settings the old will deleted.
	 * @param An OpenglSettings object (created by factory for example).
	 */
	void setOpenGlSettings(core::gl::OpenGlSettings *settings);
	
private:
	base::util::DefaultManagment managment;
	core::gl::OpenGlSettings *settings;
	
	friend class core::gl::Camera;
	core::gl::Camera *currentCam;
	base::cont::List<core::gl::Camera *> cameras;
};

} // gl
} // managed
} // vs

#endif	// OPENGL_MANAGER_H
