/**
 * @file AnimationXmlEntry.h
 * @author sizilium
 * @date 21.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ANIMATION_XML_ENTRY_H
#define ANIMATION_XML_ENTRY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/xml/AbstractXmlEntry.h>

namespace vs
{
namespace managed
{
namespace gl
{
// predeclarations
class ModelAnimation;

using namespace std;

/** @class AnimationXmlEntry
 * 
 */
class VS_EXPORT AnimationXmlEntry : public base::xml::AbstractXmlEntry
{
	string path;
	ModelAnimation *ptr;
public:
	AnimationXmlEntry()  {}	// for read
	AnimationXmlEntry(const string &name, const string &path, ModelAnimation *animation);	// for write
	virtual ~AnimationXmlEntry() {}
	
	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);
	
	virtual string getNamespace() const		{ return "gl"; }
	virtual string getTypeName() const		{ return "ModelAnimation"; }
};

} // gl
} // managed
} // vs

#endif  // ANIMATION_XML_ENTRY_H
