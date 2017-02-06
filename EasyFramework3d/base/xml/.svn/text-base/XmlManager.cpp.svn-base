#include <vs/base/xml/XmlManager.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <vs/base/xml/AbstractXmlEntry.h>
#include <vs/base/xml/XmlParser.h>
#include <vs/base/xml/XmlReader.h>
#include <vs/base/xml/XmlWriter.h>
#include <vs/base/cont/JavaStyleIterator.hpp>
#include <vs/base/cont/SmartIterator.hpp>
#include <vs/Version.hpp>
#include <vs/base/util/IOStream.h>

// TODO? xml benutzt hier util. soll horizontale kommunikation in dieser schicht erlaubt sein?
#include <vs/base/util/DefaultManaged.h>

#include <fstream>
#include <iostream>

namespace vs
{
namespace base
{
namespace xml
{
using namespace std;
using namespace base::interfaces;
using namespace base::cont;
using namespace base::util;

XmlManager* XmlManager::currentManager = NULL;
AbstractContext* XmlManager::currentContext = NULL;

// Overview:
// 
//             Xml structure                     |  class AbstractXmlEntry
// -------------------------------------------------------------------------
//                                               |
//           ___xmlEntries____                   |
//          /   /   |   \     \                  |
//        ph   gl  al  constr  ...     ns        |      getNamespace()
//        /\   /\  /\   /\    /\                 |
//       (...   Typenames     ...)     typenames |      getTypeName()
//      /\ /\ /\ /\ /\ /\ /\ /\ /\               |
//     ( ...     Objects      ... )    objects   |      getName()
//                                               |

XmlManager::XmlManager()
{
	xmlLogging = true;
}

XmlManager::~XmlManager()
{
	if (currentManager == this)
		currentManager = NULL;

	// clean up
	clearXmlEntries();
	clearKnownXmlEntries();
}

int XmlManager::read(const string &pathName, const string &ns)
{
	int readElements = 0;
	
	// open xml file
	ifstream input;
	input.open(pathName.c_str(), ios_base::in); 

	if (!input)
	{
		FileException e( __FILE__, __LINE__, "couldn't open file for read xml", pathName);
		throw e;
	}

	// build parser tree (1 level)
	XmlParser *parser = new XmlParser(input);

	if (knownXmlEntries.empty())
		return 0;
	Tree<AbstractXmlEntry*>::Iterator it(knownXmlEntries);

	// create namespace parsers
	while (it.hasNextSibling())
	{
		XmlParser *namespaceParser = new XmlParser();
		parser->attach((*it)->getNamespace(), namespaceParser);
		
		it.goChildNr(0);
		// create element type parsers
		while (it.hasNextSibling())
		{
			XmlParser *elementTypeParser = new XmlParser();
			namespaceParser->attach((*it)->getTypeName(), elementTypeParser);
			
			it.goChildNr(0);
			// create listeners for reading
			while (it.hasNextSibling())
			{
				XmlManagedTagReader *tmp = new XmlManagedTagReader(*it);
				elementTypeParser->attach("Object", tmp);
				it.nextSibling();
			}
			it.goParent();
			it.nextSibling();
		}
		it.goParent();
		it.nextSibling();
	}

	// parse
	try
	{
		readElements = parser->parse();
	}
	catch(XmlException e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		cout << e.what();
		e.printStackTrace();
	}

	// delete tmp
	delete parser;

	input.close();
	return readElements;
}

int XmlManager::write(const string &pathName, const string &ns)
{
	int wroteElements = 0;

	// open xml file
	ofstream output;
	output.open(pathName.c_str(), ios_base::out);

	if (!output)
	{
		FileException  e( __FILE__, __LINE__, "couldn't open file for write xml", pathName);
		throw e;
	}

	output << Header("latin-1", "1.0");
	output << Comment("visit www.vision-synthesis.de");
	output << endl;

	{
		XmlWriter writer(output, "vsEasyFramework", 0, 1);
		writer << Param("INFO", "version", FRAMEWORK_VERSION);
		writer.newLine();

		// write xmlEntries
		Tree<AbstractXmlEntry*>::Iterator it(xmlEntries);
		while (it.hasNextSibling())					// traverse ns
		{
			XmlWriter namespaceWriter(&writer, (*it)->getNamespace(), 1);
			if (it.hasChild())			
			{
				it.goChildNr(0);
				
				while (it.hasNextSibling())			// traverse type names
				{
					XmlWriter elementNameWriter(&namespaceWriter, (*it)->getTypeName(), 1);
					
					if (it.hasChild())
					{
						it.goChildNr(0);
						
						while (it.hasNextSibling())	// traverse elements
						{
							XmlWriter elementWriter(&elementNameWriter, "Object", 1);
							
							// -> write metadata
							elementWriter << Value("Name" , (*it)->getName());
							
							// -> write custom data from tree
							XmlWriter customWriter(&elementWriter, "Data", 1);
							Tree<XmlTag*> tree; 
							(*it)->notifyWrite(&tree);
							customWriter << tree;
							
							// delete tmp tree
							Tree<XmlTag*>::Iterator del(tree);
							while (del.hasNext())
								delete del.next();
							tree.clear();
							
							++wroteElements;
							
							it.nextSibling();
						}
						it.goParent();
					}
					it.nextSibling();
				}
				it.goParent();
			}
			it.nextSibling();
		}

	}
	output.close();
	return wroteElements;
}

void XmlManager::addXmlEntry(AbstractXmlEntry *entry)
{
	if (xmlLogging)
		sortXmlEntryInTree(entry, xmlEntries);
}

void XmlManager::addKnownXmlEntry(AbstractXmlEntry *entry)
{
	sortXmlEntryInTree(entry, knownXmlEntries);
}

Tree<AbstractXmlEntry *>::Const_Iterator XmlManager::getXmlEntrys() const
{
	return Tree<AbstractXmlEntry *>::Const_Iterator (xmlEntries);
}

Tree<AbstractXmlEntry *>::Const_Iterator XmlManager::getKnownXmlEntrys() const
{
	return Tree<AbstractXmlEntry *>::Const_Iterator (knownXmlEntries);
}

void XmlManager::sortXmlEntryInTree(AbstractXmlEntry *entry, Tree<AbstractXmlEntry*> &tree)
{
	// insert entry in tree
	
	Tree<AbstractXmlEntry*>::Iterator it (tree);
	
	// go/add namespace
	while (it.hasNextSibling() && !tree.isEmpty())
	{
		if (it.current()->getNamespace() == entry->getNamespace())
			break;
		it.nextSibling();
	}
	if (it == tree.end())
	{
		tree.add(entry);
		it = tree.find(entry);
	}

	// go/add element name
	if (it.hasChildNr(0))
	{
		it.goChildNr(0);
		bool found = false;
		while (it.hasNextSibling())
		{
			if ((*it)->getTypeName() == entry->getTypeName())
			{
				found = true;
				break;
			}
			it.nextSibling();
		}
		if (found == false)
		{
			it.goParent();
			tree.add(entry, it);
			it.goChild(entry);
		}
	}
	else
	{
		tree.add(entry, it);
		it.goChild(entry);
	}

	// add name
	tree.add(entry, it);

}

void XmlManager::clear()
{
	clearXmlEntries();
}

void XmlManager::enableXmlLogging(bool enable)
{
	xmlLogging = enable;
}

bool XmlManager::isXmlLogging() const
{
	return xmlLogging;
}

void XmlManager::clearXmlEntries()
{
	Tree<AbstractXmlEntry*>::Iterator it (xmlEntries);

	while (it.hasNext())
	{
		if (!it.hasChild())
			delete it.current();
		it.next();
	}
	xmlEntries.clear();
}

void XmlManager::clearKnownXmlEntries()
{
	Tree<AbstractXmlEntry*>::Iterator it (knownXmlEntries);

	while (it.hasNext())
	{
		if (!it.hasChild())
			delete it.current();
		it.next();
	}
	knownXmlEntries.clear();
}


void XmlManager::outDebug() const
{
	out << " known xml entries:\n"; // << endl;
	Tree<AbstractXmlEntry*>::Const_Iterator it (knownXmlEntries);
	while (it.hasNext())
	{
		if (it.depth() > 2)
		{
			out << it.current()->getNamespace();
			out << it.current()->getTypeName() << "\n";
		}
		it.next();
	}
	
	out << " xml entries\n"; // << endl;
	it = xmlEntries.begin();
	while (it.hasNext())
	{
		if (it.depth() > 2)
		{
			out << it.current()->getNamespace();
			out << it.current()->getTypeName();
			out << it.current()->getName() << "\n";
		}
		it.next();
	}
}

// -----------------------------------------------------------------------------

XmlManagedTagReader::XmlManagedTagReader(AbstractXmlEntry *listener)
{
	this->listener = listener;
}

XmlManagedTagReader::~XmlManagedTagReader()
{}

void XmlManagedTagReader::notifyRead(const Tree<XmlTag*> *input)
{
	Tree<XmlTag*>::Const_Iterator it (input);
	string val;
	string name;
	
	while (it.hasNextSibling())
	{
		val = (*it)->getName();
		
		if (val == "Name")
			name = (*it)->getValue();
		else if (val == "Data")
		{
			Tree<XmlTag*> subTree;
			subTree.copy(it);
			
			// set name (eventually usefull for the reader)
			listener->setName(name);
			
			AbstractManaged *abstractManaged = listener->read(&subTree);

			// set name
			DefaultManaged* managed;
			managed = static_cast<DefaultManaged*>(abstractManaged);
			if (managed != NULL)
				managed->setName(name);
		}
		it.nextSibling();
	}
}

// dummy
void XmlManagedTagReader::notifyWrite(Tree<XmlTag*> *fillTreeToWrite)
{
	listener->notifyWrite(fillTreeToWrite);
}
	

} // xml
} // base
} // vs
