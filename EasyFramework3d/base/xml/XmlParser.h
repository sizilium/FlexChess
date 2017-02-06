/**
 * @file XmlParser.h
 * @author sizilium
 * @date 18.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLPARSER_H
#define XMLPARSER_H

// includes
#include <vs/Build.hpp>
#include <stack>
#include <fstream>
#include <vs/base/cont/StringList.hpp>
#include <vs/base/cont/Tree.hpp>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/xml/XmlReader.h>
#include <vs/base/xml/XmlException.h>

namespace vs
{
namespace base
{
namespace xml
{
using namespace base::cont;
using namespace std;

/** @class XmlParser
 * 
 */
class VS_EXPORT XmlParser
{
public:
	XmlParser();
	XmlParser(const std::string &path);
	XmlParser(ifstream &input);
	~XmlParser();
	
	int parse(XmlTag *parseTag = NULL, XmlReader *otherReader = NULL);
	void attach(const string &callMeByTag, XmlListener *xmlListener);
	void attach(const string &callMeByTag, XmlParser *xmlParser);
	
private:
	// builds tree from current position to endTag
	Tree<XmlTag*>* makeTree(const std::string &endTagName);
	
	// deletes all members and the tree itself
	void deleteTree (Tree<XmlTag*> *tree);
	
	XmlReader *reader;
	
	stack<string> tags;
	StringList<XmlListener *> listener;
	StringList<XmlParser *> parsers;
	
	bool ownInput;
	ifstream *input;
};

} // xml
} // base
} // vs

#endif  // XMLPARSER_H
