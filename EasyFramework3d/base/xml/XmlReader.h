/**
 * @file XmlReader.h
 * @author sizilium
 * @date 18.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLREADER_H
#define XMLREADER_H

// includes
#include <vs/Build.hpp>
#include <vs/base/xml/XmlPrimitives.h>
#include <vs/base/xml/XmlException.h>
#include <fstream>
#include <string>

namespace vs
{
namespace base
{
namespace xml
{
using namespace std;

/** @class XmlReader
 * 
 */
class VS_EXPORT XmlReader
{
public:
	XmlReader(ifstream &input);
	XmlReader(const string *input);
	~XmlReader();

	bool hasNext() const;
	
	XmlTag* readTag(bool &isStartTag, bool &isEndTag);
	
	// position
	void reset();
	void init(int setLine, int setChar);
	int getCurrentLine() const;
	int getCurrentChar() const;

private:
	// parse helper
	char getChar();	
	void readChars(string &puffer, int num = 1);
	void readChars(string &puffer, const string &toChars);
	
	Param readParam(const string &readFrom);
	
	// counter (for xml debugging)
	int currentLine;
	int currentChar;
	
	// read from file or string
	bool isFileInput;
	ifstream *fileInput;
	string::const_iterator stdInput;
	string::const_iterator stdInputEnd;
};


} // xml
} // base
} // vs

#endif  // XMLREADER_H
