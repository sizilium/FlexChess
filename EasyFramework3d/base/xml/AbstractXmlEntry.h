/**
 * @file AbstractXmlEntry.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_XMLTAG_H
#define ABSTRACT_XMLTAG_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/base/xml/XmlReader.h>
#include <vs/base/xml/XmlWriter.h>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/cont/Tree.hpp>
#include <vs/base/interfaces/AbstractManaged.h>

namespace vs
{
namespace base
{
// predeclarations

namespace xml
{
using namespace std;

/** @class AbstractXmlEntry
 * 
 */
class VS_EXPORT AbstractXmlEntry : public XmlListener
{
public:
	AbstractXmlEntry(string name = "");
	virtual ~AbstractXmlEntry() {}
	
	// hooks
	virtual base::interfaces::AbstractManaged* read(const base::cont::Tree<XmlTag*> *input) = 0;
	virtual void write(base::cont::Tree<XmlTag*> *fillTreeToWrite) = 0;

	virtual string getNamespace() const = 0;
	virtual string getTypeName() const = 0;
	string getName() const;
	void setName(string &name);

	virtual void notifyRead(const base::cont::Tree<XmlTag*> *input);	
	virtual void notifyWrite(base::cont::Tree<XmlTag*> *fillTreeToWrite);

private:
	string name;
};

} // xml
} // base
} // vs

#endif  // ABSTRACT_XMLTAG_H
