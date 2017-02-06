/**
 * @file OpenGlFactory.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OPENGL_FACTORY_H
#define OPENGL_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/managed/gl/AbstractOpenGlFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <vs/core/gl/OpenGlSettings.h>

namespace vs
{
// predeclarations
namespace core
{
namespace gl
{
// predeclarations
class Camera;
class ObserverCamera;
class Grid;
class Light;
}
}

namespace managed
{
namespace gl
{

/** @class OpenGlFactory
 * 
 */
class VS_EXPORT OpenGlFactory : public AbstractOpenGlFactory, public base::xml::AbstractXmlFactory
{
public:
	OpenGlFactory();
	virtual ~OpenGlFactory();
	
	const std::string getName() const	{ return "OpenGlFactory"; }
	
	/**
	 * Creates a cam and activates it if there is still no other cam.
	 * @param name The name of the cam. Use several names for each cam.
	 * @return A pointer to the new created cam. If you want to make the cam current
	 * call activate() to switch the new cam to current. 
	 * @see Camera
	 */
	core::gl::Camera* createCamera(const std::string &name = "");

	/**
	 * Creates a observer cam and activates it if there is still no other cam.
	 * @param name The name of the cam. Use several names for each cam.
	 * @return A pointer to the new created cam. If you want to make the cam current
	 * call activate() to switch the new cam to current. 
	 * @see ObserverCamera 
	 */
	core::gl::ObserverCamera* createObserverCamera(const std::string &name = "");

	
	core::gl::Light* createLight(const std::string &name = "", double x = 0, double y = 0, double z = 0);
	
	core::gl::Grid* createGrid(const std::string &name = "");
	
	/**
	 * Creates and apply some standard settings:
	 * -
	 * -
	 * -
	 * -
	 * -
	 * -
	 * -
	 * 
	 */
	core::gl::OpenGlSettings* createStdOpenGlSettings();
	
	//void createStdEnvironment();
	
private:

};

} // gl
} // managed
} // vs

#endif  // OPENGL_FACTORY_H
