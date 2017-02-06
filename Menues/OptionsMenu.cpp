#include "OptionsMenu.h"
#include <vs/core/gui/AbstractButton.hpp>
#include <vs/core/gui/GuiException.h>
#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gui/GuiFactory.h>
#include <vs/core/gl/Color.h>


// global options
Options options;


using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gui;

OptionsMenu::OptionsMenu()
{
    GuiFactory gui;
	gui.setDefaultFontSize(30);
	
    try
    {
    	menuGroup = controller_1 = (VectorButtonSimple*) gui.createButton("controller_1", "Deathmatch", 200, 800, 500, 100);
    	menuGroup = controller_2 = (VectorButtonSimple*) gui.createButton("controller_2", "Std. Chess", 800, 800, 500, 100);

    	controller_1->attachEventHandler(this);
    	controller_2->attachEventHandler(this);
    }
    catch(GuiException &e)
    {
    	e.printStackTrace();
    }
    
    menuGroup.deactivate();
    
    // apply button colors
    refreshButtons();
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::notify(Event & message)
{
	ButtonEvent *event = message.castTo<ButtonEvent>();
	if (event)
	{
		if (event->getName() == "controller_1")
			options.controllerType = controller;
		else if (event->getName() == "controller_2")
			options.controllerType = stdChessController;
	}
	
	refreshButtons();
}

void OptionsMenu::refreshButtons()
{
	if (options.controllerType == controller)
	{
		controller_1->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8));
		controller_2->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	}
	else if (options.controllerType == stdChessController)
	{
		controller_2->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8));
		controller_1->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	}

}
