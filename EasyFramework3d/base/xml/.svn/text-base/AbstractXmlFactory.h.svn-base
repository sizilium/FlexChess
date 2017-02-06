/**
 * @file AbstractXmlFactory.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_XMLFACTORY_H
#define ABSTRACT_XMLFACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/StringList.hpp>
#include <vs/base/interfaces/FactoryInterface.h>
#include <iostream>
#include <fstream>

namespace vs
{

namespace base
{
namespace xml
{
// predeclarations
class XmlManager;
class AbstractXmlEntry;

using namespace base::cont;
using namespace std;


/** @class AbstractXmlFactory
 * 
 */
class VS_EXPORT AbstractXmlFactory
{
public:
	AbstractXmlFactory();
	virtual ~AbstractXmlFactory()
	{}
	
	void enableXmlLogging(bool enable);
	bool isXmlLogging() const;

	void setXmlManager(XmlManager *manager);
	void setCurrentXmlManager();
	XmlManager* getXmlManager() const;
	
protected:
	// additional property
	void addXmlEntry(AbstractXmlEntry *entry);
	
private:
	bool xmlLogging;
	XmlManager *manager;
};

} // xml
} // base
} // vs

#endif  // ABSTRACT_XMLFACTORY_H
