/**
 * @file XmlManager.h
 * @author sizilium
 * @date 05.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XML_MANAGER_H
#define XML_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/base/util/FileException.h>
#include <vs/base/cont/StringList.hpp>
#include <vs/base/cont/Tree.hpp>
#include <vs/base/xml/XmlException.h>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/interfaces/AbstractContext.h>
#include <vs/base/util/ReferenceCounting.h>
#include <vs/base/interfaces/ManagerInterface.hpp>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace base
{

/**
 * Xml stuff like XmlManager...
 * 
 */
namespace xml
{
// predeclarations
class AbstractXmlEntry;
class AbstractXmlFactory;
class XmlManagedTagReader;

using namespace std;
using namespace base::util;
using namespace base::cont;

/** @class XmlManager
 * 
 */
class VS_EXPORT XmlManager : public util::RcObject
{
public:
	XmlManager();
	~XmlManager();

	int read(const string &pathName, const string &ns = "");
	int write(const string &pathName, const string &ns = "");

	void addXmlEntry(AbstractXmlEntry *entry);
	void addKnownXmlEntry(AbstractXmlEntry *entry);

	Tree<AbstractXmlEntry *>::Const_Iterator getXmlEntrys() const;
	Tree<AbstractXmlEntry *>::Const_Iterator getKnownXmlEntrys() const;

	void clear();

	// global
	void enableXmlLogging(bool enable);
	bool isXmlLogging() const;
	
	static bool isCurrentManager()
	{
		if (currentManager)
			return true;
		else
			return false;
	}

	static XmlManager* getCurrentManager()
	{
		if (currentManager == NULL)
		{
			// if there is no current manager, try to create one!
			if (currentContext != NULL)
			{
				// if there is no current manager, create one!
				currentManager = new XmlManager;

				// perform context action
				if (currentContext)
					currentContext->performAction("refreshManagers");
			}
		}
		return currentManager;
	}

	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "XmlManager"; }

	/**
	 * Print some informations about the manager to std console.
	 */
	void outDebug() const;

	// TODO private!
	static void setCurrentManager(XmlManager *manager)
	{
		currentManager = manager;
	}

private:

	bool xmlLogging;
	
	static void setCurrentContext(interfaces::AbstractContext *context)
	{
		currentContext = context;
	}
	friend class interfaces::AbstractContext;
	
	static XmlManager *currentManager;
	static interfaces::AbstractContext *currentContext;
	
	// void cleanRemoved();

	// sorted by namespaces, element name and name
	void sortXmlEntryInTree (AbstractXmlEntry *entry, Tree<AbstractXmlEntry*> &tree);
	
	void clearXmlEntries();
	void clearKnownXmlEntries();
	
	// xml entries to write
	Tree<AbstractXmlEntry *> xmlEntries;
	
	// xml entries are needed while reading
	Tree<AbstractXmlEntry *> knownXmlEntries;
};

// ------------------------------------------------------------------------

class VS_EXPORT XmlManagedTagReader : public XmlListener
{
public:
	XmlManagedTagReader(AbstractXmlEntry *listener);
	~XmlManagedTagReader();

	void notifyRead(const Tree<XmlTag*> *input);	
	void notifyWrite(Tree<XmlTag*> *fillTreeToWrite);

private:
	AbstractXmlEntry *listener;
};


} // xml
} // base
} // vs

#endif	// XML_MANAGER_H
