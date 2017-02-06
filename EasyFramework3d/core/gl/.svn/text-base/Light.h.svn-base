/**
 * @file Light.h
 * @author sizilium
 * @date 25.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef LIGHT_H
#define LIGHT_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/core/ph/Point.h>
#include <vs/core/gl/Color.h>
#include <vs/base/util/DefaultManaged.h>
#include <GL/gl.h>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;
	
// GL_MAX_LIGHTS is defined by OpenGL
	
/** @class Light
 * Encapsulate an OpenGL light source, inspecially the position.\n
 * Why this wrapper? The class is used by GlConfigurationManager class. It can
 * load and save configuration as xml file.\
 * First set up this class, save it as xml and apply the setting to OpenGl with\n
 * appyToOpenGl() method.
 * @see GlConfigurationManager
 */
class VS_EXPORT Light : public vs::base::util::DefaultManaged, public vs::core::ph::Point
{
public:
	/**
	 * The Constructor sets some default values:
	 * - Name is "" if there is no parameter
	 * - Light will enabled (Note: But not GL_LIGHTING)
	 * - Light config is "AmbientAndDiffuse"
	 * - Light color ambient is (0.7, 0.7, 0.7, 1)
	 * - Light color diffuse is (0.8, 0.8, 0.8, 1)
	 * - Light color specular is (1, 1, 1, 1)
	 * - Position is (0, 0, 0)
	 * 
	 */
	Light();
	virtual ~Light();
	
	void activate();
	void deactivate();
	
	/**
	 * Gets the nr given by this wrapper class. The number simply starts with 0
	 * and ends with GL_MAX_LIGHTS.
	 * @return The number of light.
	 */
	int getNr() const			{return lightNr;}
	
	/**
	 * Gets the nr as OpenGl GLenum. See OpenGL doc for further informations.
	 * @return An OpenGL enum. Each light has an own enum value.
	 */
	GLenum getGlNr() const;
	
	/**
	 * Sets color (and intensity too) for ambient light.
	 * @param color @see Color
	 */
	void setAmbient(Color color);
	
	/**
	 * Sets color (and intensity too) for diffuse light.
	 * @param color @see Color
	 */
	void setDiffuse(Color color);
	
	/**
	 * Sets color (and intensity too) to specular light.
	 * @param color @see Color
	 */
	void setSpecular(Color color);
	
	Color getAmbient() const	{ return colorAmbient; }
	Color getDiffuse() const	{ return colorDiffuse; }
	Color getSpecular() const	{ return colorSpecular; }
	
	/**
	 * Applies the settings to the current OpenGl context. Don't forget to apply!
	 */
	void update(double deltaT = 0);

private:
	// reimplemented hook method from Point. Set up Light to new coords
	virtual void pointHasChanged();
	
	// state (to save as config)
	Color colorAmbient;
	Color colorDiffuse;
	Color colorSpecular;
	
	int lightNr;
	
	static int lightSum;
};


} // gl
} // core
} // vs

#endif	// LIGHT_H
