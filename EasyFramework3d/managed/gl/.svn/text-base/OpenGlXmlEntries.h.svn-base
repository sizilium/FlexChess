/**
 * @file OpenGlXmlEntries.h
 * @author sizilium
 * @date 24.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OPENGL_XMLENTRIES_H
#define OPENGL_XMLENTRIES_H

// includes
#include <vs/Build.hpp>
#include <fstream>
#include <iostream>
#include <vs/base/xml/AbstractXmlEntry.h>
#include <vs/core/gl/OpenGlSettings.h>

namespace vs
{
// predeclarations
namespace core
{
namespace gl
{
// predeclarations
class Light;
class Grid;
class Plane;
}
}

namespace managed
{
namespace gl
{
using namespace std;

/** @class LightXmlEntry
 * 
 */
class VS_EXPORT LightXmlEntry : public base::xml::AbstractXmlEntry
{
	core::gl::Light *light;
public:
	LightXmlEntry() {}	// for read
	LightXmlEntry(string name, core::gl::Light *light);	// for write
	virtual ~LightXmlEntry() {}
	
	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual string getNamespace() const	{ return "gl"; }
	virtual string getTypeName() const	{ return "Light"; }
};


/** @class GridXmlEntry
 * 
 */
class VS_EXPORT GridXmlEntry : public base::xml::AbstractXmlEntry
{
	class PlaneXmlEntry : public base::xml::XmlTag
	{
		string name;
		core::gl::Plane *plane;
	public:
		PlaneXmlEntry() {}	// for read
		PlaneXmlEntry(const string &name, core::gl::Plane *plane);	// for write
		
		void cout(ofstream &os) const;
		void cout(ostream &os) const;
		core::gl::Plane* getPlane(const base::cont::Tree<base::xml::XmlTag*> *input) const;
	};
	
	core::gl::Grid *grid;
	
public:
	GridXmlEntry() {}	// for read
	GridXmlEntry(string name, core::gl::Grid *grid);	// for write
	virtual ~GridXmlEntry() {}
	
	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual string getNamespace() const	{ return "gl"; }
	virtual string getTypeName() const	{ return "Grid"; }
};


class VS_EXPORT OpenGlSettingsXmlEntry : public base::xml::AbstractXmlEntry
{
public:
	OpenGlSettingsXmlEntry() {}	// for read
	OpenGlSettingsXmlEntry(const string &name, core::gl::OpenGlSettings *settings);	// for write

	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual string getNamespace() const	{ return "gl"; }
	virtual string getTypeName() const	{ return "OpenGlSettings"; }
	
private:
	core::gl::OpenGlSettings *settings;
};


} // gl
} // managed
} // vs

#endif  // OPENGL_XMLENTRIES_H
