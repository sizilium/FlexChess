/**
 * @file ManagedModelXmlEntry.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MANAGEDMODEL_XMLENTRY_H
#define MANAGEDMODEL_XMLENTRY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/xml/AbstractXmlEntry.h>

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{
// predeclarations
class ManagedModel;

using namespace std;


/** @class ManagedModelXmlEntry
 * 
 */
class VS_EXPORT ManagedModelXmlEntry : public base::xml::AbstractXmlEntry
{
	string path;
	ManagedModel *ptr;
public:
	ManagedModelXmlEntry()	{}	// for read
	ManagedModelXmlEntry(const string &name, const string &path, ManagedModel *model);	// for write
	virtual ~ManagedModelXmlEntry() {}
	
	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual string getNamespace() const		{ return "gl"; }
	virtual string getTypeName() const		{ return "ManagedModel"; }
};

} // model
} // gl
} // managed
} // vs

#endif  // MANAGEDMODEL_XMLENTRY_H
