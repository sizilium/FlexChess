/**
 * @file GuiException.h
 * @author sizilium
 * @date 23.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef GUI_EXCEPTION_H
#define GUI_EXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <string>

namespace vs
{
namespace core
{
namespace gui
{

/** @class GuiException
 * 
 */
class VS_EXPORT GuiException : public base::util::Exception
{
public:
	GuiException(std::string fileOfOccuredError, int placeOfOccuredError, std::string description);
	virtual ~GuiException() throw();
	
private:

};

/** @class GuiFontException
 * 
 */
class VS_EXPORT GuiFontException : public GuiException
{
public:
	GuiFontException(std::string fileOfOccuredError, int placeOfOccuredError, 
	                 std::string description, std::string fontName);
	GuiFontException(std::string fileOfOccuredError, int placeOfOccuredError, 
	                 std::string description, int fontSize);
	virtual ~GuiFontException() throw();
	
    virtual const char* what() const throw();
	
    std::string getFontName()	{return fontName;}
    int getFontSize()			{return fontSize;}
    
private:
	std::string fontName;
	int fontSize;
};

} // gui
} // core
} // vs

#endif  // GUI_EXCEPTION_H
