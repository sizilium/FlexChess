/**
 * @file VectorButtonSimple.h
 * @author sizilium
 * @date 22.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VECTOR_BUTTON_SIMPLE_H
#define VECTOR_BUTTON_SIMPLE_H

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/AbstractButton.hpp>
#include <string>

// predeclarations
class FTFont;

namespace vs
{
namespace core
{
namespace gui
{

/** @class VectorButtonSimple
 *
 */
class VS_EXPORT VectorButtonSimple : 	public AbstractButton
{
public:
	VectorButtonSimple(const std::string &text, float x, float sizeY , float sizeX, float sizeY,
	                   const std::string &fontType = "arial.ttf");
	VectorButtonSimple(const std::string &text = "", float x = 0, float y = 0, int fontSize = 20,
	                   const std::string &fontType = "arial.ttf");
	virtual ~VectorButtonSimple();
	
	virtual void mouseEnteredEvent();
	virtual void mouseLeavedEvent();
	virtual void mouseLeftClickEvent(int x, int y, bool pressed);
	
	void setText(const std::string &text);
	std::string getText() const				{return text;}
	
	void setFontSize(int fontSize);
	int getFontSize() const;
	
	void setBorder(float xBorderDistance, float yBorderDistance);
	void getBorder(float &xBorderDistance, float &yBorderDistance) const;
	
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
	void calcCoords();
	void centerText();
	
	float xBorder, yBorder;
	bool highlight, clickHighlight;
	int fontSize;

	gl::Color fontColor;
	gl::Color backgroundColor;
	gl::Color borderColor;
	
	std::string text;
	std::string fontType;
	FTFont *font;
};

} // gui
} // core
} // vs

#endif  // VECTOR_BUTTON_H
