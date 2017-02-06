#include <vs/managed/gl/OpenGlXmlEntries.h>
#include <vs/core/gl/Light.h>
#include <vs/core/gl/Grid.h>
#include <vs/managed/gl/OpenGlFactory.h>
#include <vs/core/gl/OpenGlSettings.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/core/ph/XmlPrimitivesForPhysic.h>
#include <vs/base/xml/XmlPrimitivesForMath.h>
#include <assert.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace std;
using namespace core::ph;
using namespace core::gl;
using namespace base::interfaces;
using namespace base::xml;
using namespace base::cont;
using namespace base::math;

LightXmlEntry::LightXmlEntry(string name, Light *light)
:AbstractXmlEntry(name), light(light)
{}

AbstractManaged* LightXmlEntry::read(const Tree<XmlTag*> *input)
{
	light = new Light;
	
	if (!getPointTag(input, *light))
		throw XmlException(__FILE__, __LINE__, "Couldn't read LightXmlEntry, coords not found");
	
	DoubleVector ambient, diffuse, specular;
	if (!getDoubleVector("colorAmbient", input, ambient))
		throw XmlException(__FILE__, __LINE__, "Couldn't read LightXmlEntry, colorAmbient not found");
	if (!getDoubleVector("colorDiffuse", input, diffuse))
		throw XmlException(__FILE__, __LINE__, "Couldn't read LightXmlEntry, colorDiffuse not found");
	if (!getDoubleVector("colorSpecular", input, specular))
		throw XmlException(__FILE__, __LINE__, "Couldn't read LightXmlEntry, colorSpecular not found");

	light->setAmbient(Color((float)ambient[0], (float)ambient[1], (float)ambient[2]));
	light->setDiffuse(Color((float)diffuse[0], (float)diffuse[1], (float)diffuse[2]));
	light->setSpecular(Color((float)specular[0], (float)specular[1], (float)specular[2]));

	return light;
}

void LightXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new PointTag(*light));
	output->add(new DoubleVectorTag("colorAmbient", light->getAmbient()[0], 
	                                    				light->getAmbient()[1], 
	                                    				light->getAmbient()[2]));
	output->add(new DoubleVectorTag("colorDiffuse", light->getDiffuse()[0], 
	                                    				light->getDiffuse()[1], 
	                                    				light->getDiffuse()[2]));
	output->add(new DoubleVectorTag("colorSpecular", light->getSpecular()[0], 
	                                    				 light->getSpecular()[1], 
	                                    				 light->getSpecular()[2]));
	// nummer stimmt wenn light erzeugt wird (gleiche reihenfolge)
	//output->add(new Value("lightNr", light->getNr()));
}


GridXmlEntry::PlaneXmlEntry::PlaneXmlEntry(const string &name, Plane *plane)
:plane(plane)
{
	this->name = name;
}

void GridXmlEntry::PlaneXmlEntry::cout(ofstream & /*os*/) const
{

}

void GridXmlEntry::PlaneXmlEntry::cout(ostream & /*os*/) const
{

}

Plane* GridXmlEntry::PlaneXmlEntry::getPlane(const Tree<XmlTag*> * /*input*/) const
{
	return NULL;
}

GridXmlEntry::GridXmlEntry(string name, Grid *grid)
:AbstractXmlEntry(name), grid(grid)
{}

AbstractManaged* GridXmlEntry::read(const Tree<XmlTag*> *input)
{
	// 1. new grid object
	grid = new Grid();
	
	// 2. set axis
	Value tmp;
	if (!getXmlTag("axis", input, tmp))
		throw XmlException(__FILE__, __LINE__, "Couldn't read GridXmlEntry! axis not found.");
		
	if (tmp.getValue() == "1")
		grid->enableAxis(true);
	else
		grid->enableAxis(false);
	
	// 3. set axis length
	if (!getXmlTag("axisLength", input, tmp))
		throw XmlException(__FILE__, __LINE__, "Couldn't read GridXmlEntry! axisLength not found.");
		
	grid->setAxisLength(atof(tmp.getValue().c_str()));

	// 4. set plane colors
	DoubleVector color;
	if (!getDoubleVector("xyColor", input, color))
		throw XmlException(__FILE__, __LINE__, "Couldn't read GridXmlEntry! xyColor not found.");
	grid->setColorXy(Color((float)color[0], (float)color[1], (float)color[2]));
	
	if (!getDoubleVector("xzColor", input, color))
		throw XmlException(__FILE__, __LINE__, "Couldn't read GridXmlEntry! xzColor not found.");
	grid->setColorXz(Color(color[0], color[1], color[2]));
	
	if (!getDoubleVector("yzColor", input, color))
		throw XmlException(__FILE__, __LINE__, "Couldn't read GridXmlEntry! yzColor not found.");
	grid->setColorYz(Color(color[0], color[1], color[2]));

	// 5. set planes
	// TODO read planes...
	
	return grid;
}

void GridXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new Value("axis", grid->isAxis()));
	output->add(new Value("axisLength", grid->getAxisLength()));
	Plane *tmp;
	output->add(new Value("planeXy", grid->getPlaneXy(tmp)));
	output->add(new PlaneXmlEntry("planeYz", tmp));
	output->add(new Value("planeXz", grid->getPlaneXz(tmp)));
	output->add(new PlaneXmlEntry("planeYz", tmp));
	output->add(new Value("planeYz", grid->getPlaneYz(tmp)));
	output->add(new PlaneXmlEntry("planeYz", tmp));
	output->add(new DoubleVectorTag("xyColor", grid->getColorXy()[0], 
	                                    			grid->getColorXy()[1], 
	                                    			grid->getColorXy()[2]));
	output->add(new DoubleVectorTag("xzColor", grid->getColorXz()[0], 
	                                    			grid->getColorXz()[1], 
	                                    			grid->getColorXz()[2]));
	output->add(new DoubleVectorTag("xyColor", grid->getColorYz()[0], 
	                                    			grid->getColorYz()[1], 
	                                    			grid->getColorYz()[2]));

}


OpenGlSettingsXmlEntry::OpenGlSettingsXmlEntry(const string &name, OpenGlSettings *settings)
:AbstractXmlEntry(name), settings(settings)
{
}

AbstractManaged* OpenGlSettingsXmlEntry::read(const Tree<XmlTag*> *input)
{
	Value tmp;

	settings = new OpenGlSettings;
	
	// -- Mode --
	if (!getXmlTag("cullFace", input, tmp))
		throw XmlException(__FILE__, __LINE__, "cullFace not found.");
	tmp.getValue() == "1" ? settings->enableCullFace() : settings->disableCullFace();

	if (!getXmlTag("cullFaceFront", input, tmp))
		throw XmlException(__FILE__, __LINE__, "cullFaceFront not found.");
	tmp.getValue() == "1" ? settings->setCullFaceFront() : settings->setCullFaceBack();
	
	if (!getXmlTag("depthTest", input, tmp))
		throw XmlException(__FILE__, __LINE__, "depthTest not found.");
	tmp.getValue() == "1" ? settings->enableDepthTest() : settings->disableDepthTest();
	
	if (!getXmlTag("frontFaceCCW", input, tmp))
		throw XmlException(__FILE__, __LINE__, "frontFaceCCW not found.");
	tmp.getValue() == "1" ? settings->setFrontFaceCCW() : settings->setFrontFaceCW();

	if (!getXmlTag("polygonModeFront", input, tmp))
		throw XmlException(__FILE__, __LINE__, "polygonModeFront not found.");
	settings->setPolygonModeFront(atoi(tmp.getValue().c_str()));
	
	if (!getXmlTag("polygonModeBack", input, tmp))
		throw XmlException(__FILE__, __LINE__, "polygonModeBack not found.");

	// -- Pen --
	if (!getXmlTag("pointSize", input, tmp))
		throw XmlException(__FILE__, __LINE__, "pointSize not found.");
	settings->setPointSize(atof(tmp.getValue().c_str()));
	
	if (!getXmlTag("lineWidth", input, tmp))
		throw XmlException(__FILE__, __LINE__, "lineWidth not found.");
	settings->setLineWidth(atof(tmp.getValue().c_str()));
	
	if (!getXmlTag("isLineStipple", input, tmp))
		throw XmlException(__FILE__, __LINE__, "isLineStipple not found.");
	tmp.getValue() == "1" ? settings->setLineStipple(true) : settings->setLineStipple(false);
	
	if (!getXmlTag("lineStippleFactor", input, tmp))
		throw XmlException(__FILE__, __LINE__, "lineStippleFactor not found.");
	settings->setLineStippleFactor(atoi(tmp.getValue().c_str()));
	
	if (!getXmlTag("lineStipplePattern", input, tmp))
		throw XmlException(__FILE__, __LINE__, "lineStipplePattern not found.");
	settings->setLineStipplePattern(atoi(tmp.getValue().c_str()));
	
	// -- Material --
	if (!getXmlTag("shadeModelSmooth", input, tmp))
		throw XmlException(__FILE__, __LINE__, "shadeModelSmooth not found.");
	tmp.getValue() == "1" ? settings->setShadeModelSmooth() : settings->setShadeModelFlat();

	if (!getXmlTag("texture", input, tmp))
		throw XmlException(__FILE__, __LINE__, "texture not found.");
	tmp.getValue() == "1" ? settings->enableTexture() : settings->disableTexture();
	
	// -- Lighting --
	if (!getXmlTag("lighting", input, tmp))
		throw XmlException(__FILE__, __LINE__, "lighting not found.");
	tmp.getValue() == "1" ? settings->enableLighting() : settings->disableLighting();
	
	// -- Miscellanous --
	if (!getXmlTag("normalize", input, tmp))
		throw XmlException(__FILE__, __LINE__, "normalize not found.");
	tmp.getValue() == "1" ? settings->enableNormalize() : settings->disableNormalize();

	// apply settings to current context with factory
	OpenGlFactory factory;
	OpenGlSettings *theSettings = factory.createStdOpenGlSettings();

	// copy
	*theSettings = *settings;

	// apply
	theSettings->applyToOpenGl();

	// no managed in this case
	return NULL;
}

void OpenGlSettingsXmlEntry::write(Tree<XmlTag*> *output)
{
	// -- Mode --
	output->add(new Value("cullFace", settings->isCullFace()));
	output->add(new Value("cullFaceFront", settings->isCullFaceFront()));
	output->add(new Value("depthTest", settings->isDepthTest()));
	output->add(new Value("frontFaceCCW", settings->isFrontFaceCCW()));

	output->add(new Value("polygonModeFront", (int)settings->getPolygonModeFront()));
	output->add(new Value("polygonModeBack", (int)settings->getPolygonModeBack()));

	// -- Pen --
	output->add(new Value("pointSize", settings->getPointSize()));
	output->add(new Value("lineWidth", settings->getLineWidth()));
	output->add(new Value("isLineStipple", settings->isLineStipple()));
	output->add(new Value("lineStippleFactor", settings->getLineStippleFactor()));
	output->add(new Value("lineStipplePattern", settings->getLineStipplePattern()));

	// -- Material --
	output->add(new Value("shadeModelSmooth", settings->isShadeModelSmooth()));
	output->add(new Value("texture", settings->isTexture()));
//	vector<ColorMaterial> getColorMaterial()

	// -- Lighting --
	output->add(new Value("lighting", settings->isLighting()));

	// -- Miscellanous --

//	std::auto_ptr<bool> getColorMask()
//	Color getClearColor()
	output->add(new Value("normalize", settings->isNormalize()));

}


} // gl
} // managed
} // vs
