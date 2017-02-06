#include <vs/base/xml/XmlException.h>
#include <sstream>

namespace vs
{
namespace base
{
namespace xml
{

XmlException::XmlException(string fileOfOccuredError, string placeOfOccuredError, string description, int currentLine, int currentChar)
:Exception(fileOfOccuredError, placeOfOccuredError, description)
{	
	this->currentLine = currentLine;
	this->currentChar = currentChar;
	this->endOfFile = false;
}

XmlException::XmlException(string fileOfOccuredError, int placeOfOccuredError, string description, int currentLine, int currentChar)
:Exception(fileOfOccuredError, placeOfOccuredError, description)
{	
	this->currentLine = currentLine;
	this->currentChar = currentChar;
	this->endOfFile = false;
}

XmlException::~XmlException() throw()
{
}

const char* XmlException::what() const throw()
{
	ostringstream message;
	
	message << Exception::what();
	
	if (currentLine != -1 && currentChar != -1)
	{
		message << endl;
		message << "in xml file at line: ";
		message << currentLine;
		message << "  character: ";
		message << currentChar;
		message << endl;
	}

	return message.str().c_str();
}


} // xml
} // base
} // vs
