/**
 * @file GuiFactory.h
 * @author sizilium
 * @date 04.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef GUI_FACTORY_H
#define GUI_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/managed/gui/AbstractGuiFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <string>

namespace vs
{
// predeclarations
namespace core {namespace gui {class AbstractButton;}}

namespace managed
{
namespace gui
{

/** @class GuiFactory
 * 
 */
class VS_EXPORT GuiFactory : public AbstractGuiFactory, public base::xml::AbstractXmlFactory 
{
public:
	GuiFactory();
	virtual ~GuiFactory();
	
	/**
	 * 
	 */
	const std::string getName() const;
	
	/**
	 * 
	 */
	void setDefaultFontSize(int fontSize)	{this->defaultFontSize = fontSize;}
	
	/**
	 * 
	 */
	int getDefaultFontSize() const			{return this->defaultFontSize;}
	
	/**
	 * 
	 */
	void setDefaultFontType(const std::string &fontType)	{this->defaultFontType = fontType;}
	
	/**
	 * 
	 */
	std::string getDefaultFontType() const					{return this->defaultFontType;}
	
	/**
	 * 
	 */
	core::gui::AbstractButton* createButton(const std::string &name, const std::string &text, 
	                                float x, float y, float sizeX, float sizeY, const std::string &fontType = "");
	
	/**
	 * 
	 */
	core::gui::AbstractButton* createButton(const std::string &name, const std::string &text, 
	                                        float x, float y, int fontSize = 20, const std::string &fontType = "");
	
private:
	int defaultFontSize;
	std::string defaultFontType;
	//int style;
};

} // gui
} // managed
} // vs

#endif  // GUI_FACTORY_H
