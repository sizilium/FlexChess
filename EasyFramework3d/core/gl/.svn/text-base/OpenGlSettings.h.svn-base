/**
 * @file OpenGlSettings.h
 * @author sizilium
 * @date 17.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OPENGL_SETTINGS_H
#define OPENGL_SETTINGS_H

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/Color.h>
#include <memory>
#include <vector>
#include <GL/gl.h>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;

/**
 * 
 */
class VS_EXPORT OpenGlSettings
{
public:
	/**
	 * 
	 */
	OpenGlSettings();
	
	void resetToStdSettings();

	
	struct ColorMaterial
	{
		GLenum side;
		GLenum material;
		Color color;
	};
	
	/**
	 * Applies all settings to the current OpenGl context.
	 */
	void applyToOpenGl() const;
	
	
	// -- Mode --
	void enableCullFace()				{ cullFace = true; }
	void disableCullFace()				{ cullFace = false; }
	bool isCullFace() const				{ return cullFace; }
	void setCullFaceFront()				{ cullFaceSide = true; }
	void setCullFaceBack()				{ cullFaceSide = false; }
	bool isCullFaceFront() const		{ return cullFaceSide; }
	void enableDepthTest()				{ depthTest = true; }
	void disableDepthTest()				{ depthTest = false; }
	bool isDepthTest() const			{ return depthTest; }
	void setFrontFaceCW()				{ frontFace = false; }
	void setFrontFaceCCW()				{ frontFace = true; }
	bool isFrontFaceCCW() const			{ return frontFace; }
	void setPolygonModeFront (GLenum type)		{ polygonModeFront = type; }
	GLenum getPolygonModeFront() const			{ return polygonModeFront; }
	void setPolygonModeBack (GLenum type)		{ polygonModeBack = type; }
	GLenum getPolygonModeBack() const			{ return polygonModeBack; }
	
	// -- Pen --
	void setPointSize (float size);
	float getPointSize() const				{ return pointSize; }
	void setLineWidth (float width);
	float getLineWidth() const				{ return lineWidth; }
	void setLineStipple (bool stipple)		{ lineStipple = stipple; }
	bool isLineStipple() const				{return lineStipple; }
	void setLineStippleFactor (int factor)	{ lineStippleFactor = factor; }
	int getLineStippleFactor() const		{ return lineStippleFactor; }
	void setLineStipplePattern (short p)	{ lineStipplePattern = p; }
	short getLineStipplePattern() const		{ return lineStipplePattern; }
	
	// -- Material --
	void enableColorMaterial()		{ colorMaterial = true; }
	void disableColorMaterial()		{ colorMaterial = false; }
	void setShadeModelFlat()		{ shadeModel = false; }
	void setShadeModelSmooth()		{ shadeModel = true; }
	bool isShadeModelSmooth() const	{ return shadeModel; }
	void enableTexture()			{ texture = true; }
	void disableTexture()			{ texture = false; }
	bool isTexture() const			{ return texture; }
	void addColorMaterial(GLenum side, GLenum type, Color c);
	vector<ColorMaterial> getColorMaterial() const	{ return colorMaterialVec; }
	
	// -- Lighting --
	void enableLighting()			{ lighting = true; }
	void disableLighting()			{ lighting = false; }
	bool isLighting() const			{ return lighting; }
	
	// -- Miscellanous --
	void setColorMask(bool r, bool g, bool b, bool a);
	std::tr1::shared_array<bool> getColorMask() const;
	void setClearColor(Color c)		{ clearColor = c; }
	Color getClearColor() const		{ return clearColor; }
	void enableNormalize()			{ normalize = true; }
	void disableNormalize()			{ normalize = false; }
	bool isNormalize() const		{ return normalize; }
	
	void coutDebug() const;
	
private:
	
	// -- Mode --
	bool cullFace;		// 0 = disabled, 1 = enabled
	bool cullFaceSide;	// 0 = GL_FRONT, 1 = GL_BACK
	bool depthTest;		// 0 = disabled, 1 = enabled
	bool frontFace;		// 0 = GL_CW, 1 = GL_CCW
	GLenum polygonModeFront;
	GLenum polygonModeBack;
	
	// -- Pen --
	float pointSize;
	float lineWidth;
	bool lineStipple;	// 0 = disabled, 1 = enabled
	int lineStippleFactor;
	short lineStipplePattern;
	
	// -- Material --
	bool shadeModel;	// 0 = GL_FLAT, 1 = GL_SMOOTH
	bool colorMaterial;	// 0 = disabled, 1 = enabled
	bool texture;		// 0 = disabled, 1 = enabled
	
	vector<ColorMaterial> colorMaterialVec;

	// -- Lighting --
	bool lighting;		// 1 = disabled, 1 = enabled
	bool normalize;		// 1 = disabled, 1 = enabled
	//LightModel
	
	// -- Miscellanous --
	bool colorMask[4];	// 0 = GL_FALSE, 1 = GL_TRUE for {r,g,b,a}
	Color clearColor;
};

} // gl
} // core
} // vs

#endif  // OPENGL_SETTINGS_H
