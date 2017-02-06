#include <vs/managed/gui/GuiFactory.h>
#include <vs/managed/gui/GuiXmlEntries.h>
#include <vs/core/gui/GuiException.h>
#include <vs/core/gui/VectorButtonSimple.h>

namespace vs
{
namespace managed
{
namespace gui
{
using namespace core::gui;
using namespace std;


GuiFactory::GuiFactory()
:defaultFontSize (20), defaultFontType("arial.ttf")
{
}

GuiFactory::~GuiFactory()
{
}

const string GuiFactory::getName() const
{
	return "GuiFactory";
}

AbstractButton* GuiFactory::createButton(const string &name, const string &text, 
                                         float x, float y, float sizeX, float sizeY, const string &fontType)
{
	string font;
	if (fontType.empty())
		font = defaultFontType;
	else
		font = fontType;
	
	VectorButtonSimple *button = NULL;
	try
	{
		button = new VectorButtonSimple(text, x, y, sizeX, sizeY, font);
		button->setFontSize(defaultFontSize);
	}
	catch(GuiException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
		
	button->setName(name);
	addManaged(button);
	
	// TODO xml entrie for button
	//ButtonXmlEntry *entry = new ButtonXmlEntry(name, button);
	//addXmlEntry(entry);
	
	return button;
}

core::gui::AbstractButton* GuiFactory::createButton(const string &name, const string &text, 
                                        float x, float y, int fontSize, const string &fontType)
{
	string font;
	if (fontType.empty())
		font = defaultFontType;
	else
		font = fontType;

	VectorButtonSimple *button = NULL;
	try
	{
		button = new VectorButtonSimple(text, x, y, fontSize, font);
	}
	catch(GuiException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}

	button->setName(name);
	addManaged(button);
	
	// TODO xml entrie for button
	//ButtonXmlEntry *entry = new ButtonXmlEntry(name, button);
	//addXmlEntry(entry);
	
	return button;	
}

} // gui
} // managed
} // vs
