#include "MainMenu.h"
#include <vs/Context.h>
#include <vs/core/gui/AbstractButton.hpp>
#include <vs/core/gui/VectorButtonSimple.h>
#include <vs/core/gui/GuiException.h>
#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gui/GuiFactory.h>
#include <vs/core/gl/Color.h>
using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gui;

MainMenu::MainMenu()
:exitButtonClicked(false)
{
    GuiFactory gui;
    gui.setDefaultFontSize(40);
   
    try
    {	
    	VectorButtonSimple *button_1, *button_2, *button_3, *button_4;
    	menuGroup = button_1 = (VectorButtonSimple*) gui.createButton("startGame", "Start Game", 450, 800, 600, 100);
    	menuGroup = button_2 = (VectorButtonSimple*) gui.createButton("options", "Options", 450, 650, 600, 100);
    	menuGroup = button_3 = (VectorButtonSimple*) gui.createButton("credits", "Credits", 450, 500, 600, 100);
    	menuGroup = button_4 = (VectorButtonSimple*) gui.createButton("exitGame", "Exit", 450, 350, 600, 100);

    	button_1->attachEventHandler(this);
    	button_2->attachEventHandler(this);
    	button_3->attachEventHandler(this);
    	button_4->attachEventHandler(this);
    	
    	button_1->setBackgroundColor(Color(0.1, 0.1, 0.5, 0.8));
    	button_2->setBackgroundColor(Color(0.1, 0.1, 0.5, 0.8));
    	button_3->setBackgroundColor(Color(0.1, 0.1, 0.5, 0.8));
    	button_4->setBackgroundColor(Color(0.5, 0.1, 0.1, 0.8));
    }
    catch(GuiException &e)
    {
    	e.printStackTrace();
    }
}

void MainMenu::notify(Event &message)
{
	ButtonEvent *event = message.castTo<ButtonEvent>();
	if (event)
	{
		if (event->getName() == "startGame")
		{
			this->deactivate();
		   	startGameMenu.activate();
		}
		else if (event->getName() == "options")
		{
			this->deactivate();
			optionsMenu.activate();
		}
		else if (event->getName() == "credits")
			cout << "written by sizilium\n" << endl;
		else if (event->getName() == "exitGame")
		   	exitButtonClicked = true;
	}
}

