#include <vs/base/xml/XmlParser.h>
#include <vs/base/xml/XmlReader.h>
#include <vs/base/util/FileException.h>

namespace vs
{
namespace base
{
namespace xml
{
using namespace vs::base::util;

XmlParser::XmlParser()
{
	this->input = NULL;
	this->reader = NULL;
	ownInput = false;
}

XmlParser::XmlParser(const string &path)
{
	ifstream *newInput = new ifstream;
	newInput->open(path.c_str(), ios_base::in);
	
	if (!(*newInput))
	{
		delete newInput;
		FileException e( __FILE__, __LINE__, "Couldn't open file for xml reading", path);
		throw e;
	}
	
	this->input = newInput;
	ownInput = true;
	this->reader = new XmlReader(*input);
}

XmlParser::XmlParser(ifstream &input)
{
	this->input = &input;
	ownInput = false;
	this->reader = new XmlReader(input);
}

XmlParser::~XmlParser()
{
	if (this->reader != NULL)
		delete this->reader;
	
	if (ownInput)
	{
		this->input->close();
		delete input;
	}
}

int XmlParser::parse(XmlTag *parseTag, XmlReader *otherReader)
{
	// deklarations
	int readElements = 0;
	XmlTag *xmlTag = NULL;
	bool isEndTag, isStartTag;
	stack<XmlTag *> xmlTagStack;
	StringList<XmlListener *>::Iterator listenerIt;
	StringList<XmlParser *>::Iterator parserIt;
	Tree<XmlTag *> *parseTree;

	
	// 1. - init step. am i a sub parser?
	if (otherReader != NULL && parseTag != NULL)
	{
		// then work with parent parsers reader within a parse tag
		this->reader = otherReader;
		xmlTagStack.push(parseTag);
	}
	else
	{
		// work with own parser
		assert ("Cannot parse xml! The parser is not initialized." && this->reader != NULL);
		this->reader->reset();		
	}

	
	// 2. - read first tag
	while (xmlTagStack.empty())
	{
		try
		{
			xmlTag = reader->readTag(isStartTag, isEndTag);
		}
		catch(XmlException &e)
		{
			if (e.endOfFile)	// end of file before first tag allowed (empty file)
				return 0;
			else
				throw e;
		}
		
		if (isStartTag)
		{
			// 2.1 - check sub parsers first
			if(parsers.byName(xmlTag->getName(), parserIt))
			{
				// pass reader reference and tag to sub parser
				readElements += (*parserIt)->parse(xmlTag, reader);
				break;
			}
			// 2.2 - check listeners
			else if (listener.byName(xmlTag->getName(), listenerIt))
			{
				// fill tree to end tag
				parseTree = makeTree(xmlTag->getName());
				
				// pass tree to listener (listener works with tree and returns)
				(*listenerIt)->notifyRead(parseTree);
				++readElements;

				// delete tree
				deleteTree(parseTree);
				break;
			}
			else
				xmlTagStack.push(xmlTag);
		}
		
		if (isEndTag)
			throw XmlException(__FILE__, __LINE__, "Xml Parse Error! No start tag found.", reader->getCurrentLine(), reader->getCurrentChar());
	}
	
	
	// 3. - parse all tags
	while(!xmlTagStack.empty())
	{
		// read next tag
		xmlTag = reader->readTag(isStartTag, isEndTag);

		if (isStartTag)
		{
			// 3.1 - check sub parsers first
			if(parsers.byName(xmlTag->getName(), parserIt))
			{
				// pass reader reference and tag to sub parser
				readElements += (*parserIt)->parse(xmlTag, reader);
				
				continue;
			}
			// 3.2 - check listeners
			else if (listener.byName(xmlTag->getName(), listenerIt))
			{
				// fill tree to end tag
				parseTree = makeTree(xmlTag->getName());
				
				// pass tree to listener (listener works with tree and returns)
				(*listenerIt)->notifyRead(parseTree);
				++readElements;

				// delete tree
				deleteTree(parseTree);
				
				continue;
			}
			else
				xmlTagStack.push(xmlTag);

		}
		if (isEndTag)
		{
			// check syntax
			if (xmlTag->getName() != xmlTagStack.top()->getName())
				throw XmlException(__FILE__, __LINE__, "Xml Parse Error! End tag \"" + xmlTag->getName() + "\" does not match with start tag \"" + xmlTagStack.top()->getName() + "\".", reader->getCurrentLine(), reader->getCurrentChar());
			
			delete xmlTagStack.top();
			xmlTagStack.top() = NULL;
			xmlTagStack.pop();
		}

	}

	return readElements;
}

void XmlParser::attach(const string &callMeByTag, XmlListener *xmlListener)
{
	listener.push_back(xmlListener, callMeByTag);
}

void XmlParser::attach(const string &callMeByTag, XmlParser *xmlParser)
{
	parsers.push_back(xmlParser, callMeByTag);
}

// ----------------------------------------------------------------------------------------

Tree<XmlTag*>* XmlParser::makeTree(const std::string &endTag)
{
	bool init = true;
	bool isStartTag, isEndTag;
	XmlTag *xmlTag = NULL;
	Tree<XmlTag*> *parseTree = new Tree<XmlTag*>;
	Tree<XmlTag *>::Iterator parseTreeIt;
	
	while ((xmlTag = reader->readTag(isStartTag, isEndTag))->getName() != endTag)
	{
		if (isStartTag)
		{
			if (init)
			{
				//cout << "add " << xmlTag->getName() << endl;	// debug
				//std::flush(cout);
				parseTree->add(xmlTag);
				init = false;
				parseTreeIt = parseTree->begin();
			}
			else
			{
				//cout << "add " << xmlTag->getName() << endl;	// debug
				//std::flush(cout);
				parseTree->add(xmlTag, parseTreeIt);
				parseTreeIt.goChild(xmlTag);
			}
		}
		if (isEndTag && !init)
			parseTreeIt.goParent();
	}
	
	return parseTree;
}

void XmlParser::deleteTree (Tree<XmlTag*> *tree)
{
	if (tree->empty())
	{
		delete tree;
		return;
		
	}
	
	Tree<XmlTag *>::Iterator parseTreeIt;
	
	parseTreeIt = tree->begin();
	while (parseTreeIt != tree->end())
	{
		delete *parseTreeIt;
		*parseTreeIt++ = NULL;
	}
	delete tree;
}


} // xml
} // base
} // vs
