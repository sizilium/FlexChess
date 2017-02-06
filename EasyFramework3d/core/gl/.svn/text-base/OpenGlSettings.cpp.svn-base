#include <vs/core/gl/OpenGlSettings.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace core
{
namespace gl
{
using namespace base::util;

OpenGlSettings::OpenGlSettings()
{
	resetToStdSettings();
}

void OpenGlSettings::resetToStdSettings()
{
	// -- Mode --
	cullFace = false;		// 0 = disabled, 1 = enabled
	cullFaceSide = true;	// 0 = GL_FRONT, 1 = GL_BACK
	depthTest = true;		// 0 = disabled, 1 = enabled
	frontFace = true;		// 0 = GL_CW, 1 = GL_CCW
	polygonModeFront = GL_FILL;
	polygonModeBack = GL_FILL;
	
	// -- Pen --
	pointSize = 1.0f;
	lineWidth = 1.0f;
	lineStipple = false;	// 0 = disabled, 1 = enabled
	lineStippleFactor = 0;
	lineStipplePattern = 0;
	
	// -- Material --
	shadeModel = false;		// 0 = GL_FLAT, 1 = GL_SMOOTH
	colorMaterial = false;	// 0 = disabled, 1 = enabled
	texture = false;		// 0 = disabled, 1 = enabled

	// -- Lighting --
	lighting = false;		// 1 = disabled, 1 = enabled
	//LightModel
	
	// -- Miscellanous --
	// colorMask[4];	// 0 = GL_FALSE, 1 = GL_TRUE for {r,g,b,a}
	colorMask[0] = true;
	colorMask[1] = true;
	colorMask[2] = true;
	colorMask[3] = true;

	normalize = false;
	
	clearColor = Color (0, 0, 0, 1);
}

void OpenGlSettings::applyToOpenGl() const
{
	// -- Mode --
	cullFace ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	cullFaceSide ? glCullFace(GL_FRONT) : glCullFace(GL_BACK);
	depthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	frontFace ? glFrontFace(GL_CCW) : glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT, polygonModeFront);
	glPolygonMode(GL_BACK, polygonModeBack);

	// -- Pen -- 
	glPointSize(pointSize);
	glLineWidth(lineWidth);
	lineStipple ? glEnable(GL_LINE_STIPPLE) : glDisable(GL_LINE_STIPPLE);
	glLineStipple(lineStippleFactor, lineStipplePattern);
	
	// -- Material --
	shadeModel ? glShadeModel(GL_SMOOTH) : glShadeModel(GL_FLAT);
	colorMaterial ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
	texture ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	
	vector<ColorMaterial>::const_iterator it = colorMaterialVec.begin();
	while (it != colorMaterialVec.end())
	{
		//glColorMaterial (it->side, it->material);
		glMaterialfv(it->side, it->material, it->color.toArray());
		++it;
	}

	// -- Lighting --
	lighting ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
	
	// -- Miscellanous --
	glColorMask(colorMask[0], colorMask[1], colorMask[2], colorMask[3]);
	glClearColor(clearColor.red(), clearColor.green(), clearColor.blue(), clearColor.alpha());
	normalize ? glEnable(GL_NORMALIZE) : glDisable(GL_NORMALIZE);
}

void OpenGlSettings::setPointSize (float size)
{
//	float limits[2];
//	glGetFloatv(GL_POINT_SIZE_RANGE, limits);
//	assert ("Invalid OpenGl point size for this system!" && size >= limits[0] && size <= limits[1]);
	
	pointSize = size;
}

void OpenGlSettings::setLineWidth (float width)
{
//	float limits[2];
//	glGetFloatv(GL_LINE_WIDTH_RANGE, limits);
//	assert ("Invalid OpenGl line width for this system!" && width >= limits[0] && width <= limits[1]);
	
	lineWidth = width;
}

void OpenGlSettings::addColorMaterial(GLenum s, GLenum m, Color c)
{
	ColorMaterial tmp;
	tmp.side = s;
	tmp.material = m;
	tmp.color = c;
	colorMaterialVec.push_back(tmp);
}

void OpenGlSettings::setColorMask(bool r, bool g, bool b, bool a)
{
	colorMask[0] = r;
	colorMask[0] = g;
	colorMask[0] = b;
	colorMask[0] = a;
}

std::tr1::shared_array<bool> OpenGlSettings::getColorMask() const
{
	bool *tmp = new bool[4];
	tmp[0] = colorMask[0];
	tmp[1] = colorMask[1];
	tmp[2] = colorMask[2];
	tmp[3] = colorMask[3];
	return std::tr1::shared_array<bool> (tmp);
}

void OpenGlSettings::coutDebug() const
{
	/* TODO OStream ...
	out << "cullFace= " << cullFace << "  cullFaceSide= " << cullFaceSide << "\n";
	out << "depthTest= " << depthTest << "  frontFace= " << frontFace << "\n";
	out << "polygonModeFront= " << polygonModeFront << "  polygonModeBack= " << polygonModeBack << "\n";
	out << "pointSize= " << pointSize << "  lineWidth= " << lineWidth << "\n";
	out << "shadeMode= " << shadeModel << "  colorMaterial= " << colorMaterial << "\n";
	out << "lighting= " << lighting << "\n";
	out << "normalize= " << normalize << "\n";
	*/
}

} // gl
} // core
} // vs
