#include <vs/core/gui/VectorTextBoxSimple.h>
#include <vs/core/gui/GuiException.h>
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

VectorTextBoxSimple::VectorTextBoxSimple(const string &text, float x, float y, int fontSize,
                                         const string &fontType)
:AbstractTextBox(x, y), fontColor(1,1,1), backgroundColor(0.5, 0.5, 0.5, 0.5), 
borderColor(0.8, 0.8, 0.8, 0.8)
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
	textLines.push_back(text);
	arrangeText();
}

VectorTextBoxSimple::~VectorTextBoxSimple()
{
}

void VectorTextBoxSimple::setSize(float width, float height)
{
	this->sizeX = width;
	this->sizeY = height;
	arrangeText();
}

void VectorTextBoxSimple::getSize(float &width, float &height) const
{
	width = this->sizeX + xBorder*2;
	height = this->sizeY + yBorder*2;
}

void VectorTextBoxSimple::setText(const string &text)
{
	textLines.clear();
	textLines.push_back(text);
}

string VectorTextBoxSimple::getText() const
{
	string retText;
	vector<string>::const_iterator it;
	it = textLines.begin();
	while (it != textLines.end())
		retText += string(" ") + *it++;
	return retText;
}

void VectorTextBoxSimple::update(double)
{

}

void VectorTextBoxSimple::arrangeText()
{
	//float cx, cy, cz, width, height, dummy;
	//font->BBox(text.c_str(), cx, cy, cz, width, height, dummy);
	

}

} // gui
} // core
} // vs
