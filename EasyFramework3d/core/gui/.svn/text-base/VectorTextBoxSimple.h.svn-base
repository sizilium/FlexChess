/**
 * @file VectorTextBoxSimple.h
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VECTOR_TEXT_BOX_SIMPLE_H
#define VECTOR_TEXT_BOX_SIMPLE_H

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/AbstractTextBox.hpp>
#include <vs/core/gl/Color.h>
#include <string>
#include <vector>

// predeclarations
class FTFont;

namespace vs
{
namespace core
{
namespace gui
{

/** @class VectorTextBoxSimple
 * 
 */
class VS_EXPORT VectorTextBoxSimple : public AbstractTextBox
{
public:
	VectorTextBoxSimple(const std::string &text = "", float x = 0, float y = 0, int fontSize = 20,
	                    const std::string &fontType = "arial.ttf");
	virtual ~VectorTextBoxSimple();
	
	void setText(const std::string &text);
	std::string getText() const;
	
	void setSize(float width, float height);
	void getSize(float &width, float &height) const;
	
	void setFontColor(gl::Color fontColor)				{this->fontColor = fontColor;}
	void setBackgroundColor(gl::Color backgroundColor)	{this->backgroundColor = backgroundColor;}
	void setBorderColor(gl::Color borderColor)			{this->borderColor = borderColor;}
	
	gl::Color getFontColor() const					{return fontColor;}
	gl::Color getBackgroundColor() const			{return backgroundColor;}
	gl::Color getBorderColor() const				{return borderColor;}
	
	virtual void update(double);
	
private:
	void arrangeText();
	
	int fontSize;

	float xBorder, yBorder;
	
	gl::Color fontColor;
	gl::Color backgroundColor;
	gl::Color borderColor;
	
	std::vector<std::string> textLines;
	FTFont *font;
};

} // gui
} // core
} // vs

#endif  // VECTOR_TEXT_BOX_SIMPLE_H
