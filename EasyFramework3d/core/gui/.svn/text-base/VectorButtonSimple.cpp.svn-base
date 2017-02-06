#include <vs/core/gui/VectorButtonSimple.h>
#include <vs/core/gui/GuiException.h>
#include <vs/core/gui/ButtonEvent.hpp>
#include <FTGL/FTGLTextureFont.h>
#include <vs/core/gui/FontStorage.h>
#include <vs/core/gui/GuiException.h>

namespace vs
{
namespace core
{
namespace gui
{
using namespace std;
using namespace vs::base::interfaces;

VectorButtonSimple::VectorButtonSimple(const string &text, float x, float y, 
                                       float sizeX, float sizeY, const string &fontType)
:AbstractButton(x, y, sizeX, sizeY), xBorder(20), yBorder(10), highlight(false), clickHighlight(false),
fontColor(1,1,1), backgroundColor(0.5, 0.5, 0.5, 0.5), borderColor(0.8, 0.8, 0.8, 0.8), text(text),
fontType(fontType)
{
	try
	{
		font = FontStorage::getInstance().getFont(fontType, 20);
	}
	catch (GuiFontException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	centerText();
}

VectorButtonSimple::VectorButtonSimple(const string &text, float x, float y, int fontSize,
                                       const string &fontType)
:AbstractButton(x, y, 0, 0), xBorder(20), yBorder(10),  highlight(false), clickHighlight(false),
fontColor(1,1,1), backgroundColor(0.5, 0.5, 0.5, 0.5), borderColor(0.8, 0.8, 0.8, 0.8), 
text(text), fontType(fontType)
{
	try
	{
		font = FontStorage::getInstance().getFont(fontType, fontSize);
	}
	catch (GuiFontException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	calcCoords();
}

VectorButtonSimple::~VectorButtonSimple()
{
	
}

void VectorButtonSimple::mouseEnteredEvent()
{
	highlight = true;
}

void VectorButtonSimple::mouseLeavedEvent()
{
	highlight = false;
	clickHighlight = false;
}

void VectorButtonSimple::mouseLeftClickEvent(int x, int y, bool pressed)
{
	if (pressed)
		clickHighlight = true;
	else if (!pressed && clickHighlight)
	{
		clickHighlight = false;
		ButtonEvent event(this->getName(), x, y);
		MsgObservable<Event>::notify(event);
	}
	else
		clickHighlight = false;
}

void VectorButtonSimple::setText(const std::string &text)
{
	this->text = text;
	font->Advance(text.c_str());
	centerText();
}

void VectorButtonSimple::setFontSize(int fontSize)
{
//	this->fontSize = fontSize;
//	if (!this->font->FaceSize(fontSize))
//		throw GuiFontException(__FILE__, __LINE__, 
//		                       "Could not change face size of font. Maybe the value is too high!",
//		                       fontSize);
	
	// get new font
	try
	{
		font = FontStorage::getInstance().getFont(fontType, fontSize);
	}
	catch (GuiFontException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	
	centerText();
}

int VectorButtonSimple::getFontSize() const
{
	return fontSize;
}

void VectorButtonSimple::setBorder(float xBorderDistance, float yBorderDistance)
{
	this->xBorder = xBorderDistance;
	this->yBorder = yBorderDistance;
	calcCoords();
}

void VectorButtonSimple::getBorder(float &xBorderDistance, float &yBorderDistance) const
{
	xBorderDistance = this->xBorder;
	yBorderDistance = this->yBorder;
}

void VectorButtonSimple::setSize(float width, float height)
{
	this->sizeX = width;
	this->sizeY = height;
	centerText();
}

void VectorButtonSimple::getSize(float &width, float &height) const
{
	width = this->sizeX;
	height = this->sizeY;
}

void VectorButtonSimple::update(double)
{
	glDisable(GL_TEXTURE_2D);
	
	// border
	glColor4fv(borderColor.toSmartArray().get());
//	glLineWidth(2);
	glBegin(GL_LINES);
	 glVertex2f(x, y);				// |
	 glVertex2f(x, y+sizeY);
	 glVertex2f(x, y+sizeY);		// -
	 glVertex2f(x+sizeX, y+sizeY);
	 glVertex2f(x+sizeX, y);		//  |
	 glVertex2f(x+sizeX, y+sizeY);
	 glVertex2f(x, y);				// _
	 glVertex2f(x+sizeX, y);
	glEnd();

	// background
	if (clickHighlight)
	{
		glColor4f(backgroundColor[0] + 0.3, backgroundColor[1] + 0.3, 
		           backgroundColor[2] + 0.3, backgroundColor[3] + 0.2);
		glRectf (x, y, x + sizeX, y + sizeY);
	}
	else if (highlight)
	{
		glColor4f(backgroundColor[0] + 0.1, backgroundColor[1] + 0.1, 
		           backgroundColor[2] + 0.1, backgroundColor[3] + 0.1);
		glRectf (x, y, x + sizeX, y + sizeY);
	}
	else
	{
		glColor4fv(backgroundColor.toSmartArray().get());
		glRectf (x, y, x + sizeX, y + sizeY);
	}
	
	// text
	glEnable(GL_TEXTURE_2D);
	glColor4fv(fontColor.toSmartArray().get());
	glTranslatef(x + xBorder, y + yBorder, 1);
	font->Render(text.c_str());
	
}

void VectorButtonSimple::calcCoords()
{
	float cx, cy, cz, width, height, dummy;
	font->BBox(text.c_str(), cx, cy, cz, width, height, dummy);
	
	this->sizeX = width + 2 * xBorder;
	this->sizeY = height + 2 * yBorder;
}

void VectorButtonSimple::centerText()
{
	float cx, cy, cz, width, height, dummy;
	font->BBox(text.c_str(), cx, cy, cz, width, height, dummy);
	
	if (sizeX - width < 0)
		sizeX = width + xBorder * 2;

	if (sizeY - height < 0)
		sizeY = height + yBorder * 2;
	
	xBorder = (sizeX - width) / 2;
	yBorder = (sizeY - height) / 2;
}

} // gui
} // core
} // vs
