/**
 * @file AbstractOpenGlFactory.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_OPENGL_FACTORY_H
#define ABSTRACT_OPENGL_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/core/gl/OpenGlSettings.h>
#include <vs/managed/gl/OpenGlManager.h>

namespace vs
{
// predeclarations
namespace base { namespace util {class DefaultManaged; }}
namespace core { namespace gl {class Camera; }}

namespace managed
{
namespace gl
{

/** @class AbstractOpenGlFactory
 * 
 */
class VS_EXPORT AbstractOpenGlFactory : public base::interfaces::AbstractFactory<OpenGlManager>
{
public:
	virtual ~AbstractOpenGlFactory();
	
	virtual const std::string getName() const = 0;
	const std::string getNamespace() const	{ return "gl"; }
	
protected:
	void addManaged(base::util::DefaultManaged *managed);
	void addCamera(core::gl::Camera *cam);
	void setOpenGlSettings(core::gl::OpenGlSettings *settings);
	
	OpenGlManager* getCurrentManager();
};

} // gl
} // managed
} // vs

#endif  // ABSTRACT_OPENGL_FACTORY_H
