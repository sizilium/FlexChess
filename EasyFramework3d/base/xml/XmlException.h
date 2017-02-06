/**
 * @file XmlException.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <string>

namespace vs
{
namespace base
{
namespace xml
{
using namespace std;

/** @class XmlException
 * 
 */
class VS_EXPORT XmlException : public base::util::Exception
{
public:
	XmlException(string fileOfOccuredError, string placeOfOccuredError, string description, int currentLine = -1, int currentChar = -1);
	XmlException(string fileOfOccuredError, int placeOfOccuredError, string description, int currentLine = -1, int currentChar = -1);
	~XmlException() throw();

	virtual const char* what() const throw(); 
	
	int currentLine;
	int currentChar;
	
	bool endOfFile;
};

} // xml
} // base
} // vs

#endif  // XMLEXCEPTION_H
