#include "Interface.h"
#include "../Game.h"
#include "../Core/Player.h"
#include <vs/Context.h>
#include <vs/core/gui/AbstractButton.hpp>
#include <vs/core/gui/GuiException.h>
#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/core/gl/ObserverCamera.h>
#include <vs/managed/gui/GuiFactory.h>

using namespace vs;
using namespace vs::managed::gui;

Interface::Interface()
:exitFlag(false), cursorX(0), cursorY(0), markedCursorX(-1), markedCursorY(-1), cursorColor(0, 0, 0, 0)
, showWinnerFlag(true)
{
    GuiFactory gui;
    
    try
	{
		VectorButtonSimple *button_1, *button_2, *button_3, *button_4;
		button_1 = (VectorButtonSimple*) gui.createButton("menu", "Menue", 10, 10, 50, "Comicbd.ttf");
    	button_1->setBorder(50, 20);
    	button_1->setBorderColor(Color(0.1, 0.1, 0.4, 0.4));
    	button_1->setBackgroundColor(Color(0.1, 0.1, 0.4, 0.7));
    	button_1->attachEventHandler(this);

		button_2 = (VectorButtonSimple*) gui.createButton("undo", "<", 1050, 10, 50, "Comicbd.ttf");
    	button_2->setBorder(50, 28);
    	button_2->setBorderColor(Color(0.1, 0.1, 0.4, 0.4));
    	button_2->setBackgroundColor(Color(0.1, 0.1, 0.4, 0.7));
    	button_2->attachEventHandler(this);

		button_3 = (VectorButtonSimple*) gui.createButton("redo", ">", 1350, 10, 51, "Comicbd.ttf");
    	button_3->setBorder(50, 27);
    	button_3->setBorderColor(Color(0.1, 0.1, 0.4, 0.4));
    	button_3->setBackgroundColor(Color(0.1, 0.1, 0.4, 0.7));
    	button_3->attachEventHandler(this);

		button_4 = (VectorButtonSimple*) gui.createButton("go", "Go", 1191, 10, 37, "Comicbd.ttf");
    	button_4->setBorder(50, 27);
    	button_4->setBorderColor(Color(0.1, 0.1, 0.4, 0.4));
    	button_4->setBackgroundColor(Color(0.1, 0.1, 0.4, 0.7));
    	button_4->attachEventHandler(this);
    	
		winnerButton = (VectorButtonSimple*) gui.createButton("winner", "Winner!", 450, 800, 150, "Comicbd.ttf");
		winnerButton->setBackgroundColor(Color(0, 0, 0, 0));
		winnerButton->setBorderColor(Color(0, 0, 0, 0));
		winnerButton->deactivate();
	}
	catch (GuiException &e)
	{
		e.printStackTrace();
	}
	catch (...)
	{
		assert("Uncaught Exception!" && false);
	}
}

void Interface::notify(Event &message)
{
	ButtonEvent *event = message.castTo<ButtonEvent>();
	if (event)
	{
		if (event->getName() == "menu" && mainMenu.isActive())
			mainMenu.deactivate();
		else if (event->getName() == "menu" && !mainMenu.isActive())
		{
			mainMenu.activate();
			winnerButton->deactivate();
			if (getGame())
				getGame()->setPause(true);
		}
		else if (event->getName() == "undo" && !mainMenu.isActive())
		{
			if (getGame())
				getGame()->undo();
		}
		else if (event->getName() == "redo" && !mainMenu.isActive())
		{
			if (getGame())
				getGame()->redo();
		}
		else if (event->getName() == "go" && !mainMenu.isActive())
		{
			if (getGame())
				getGame()->setPause(false);
			winnerButton->deactivate();
		}
	}
}

void Interface::addCursor(int x, int y)
{
	if (getGame())
	{
		ObserverCamera *cam = (ObserverCamera*) Context::getCurrentContext()->getOpenGlManager()->getCurrentCamera();
		assert(cam);
		
		// cursor move depends on camera rotation
		float angle = cam->getAngleZ();
		if (angle >= 45 && angle <= 135)
		{
			cursorX -= y;
			cursorY += x;
		}
		else if (angle >= 135 && angle <= 225)
		{
			cursorX += x;
			cursorY += y;
		}
		else if (angle >= 225 && angle <= 315)
		{
			cursorX += y;
			cursorY -= x;
		}
		else
		{
			cursorX -= x;
			cursorY -= y;
		}

		checkCursor();
	}
}

void Interface::setCursor(int x, int y)
{
	if (getGame())
	{
		cursorX = x;
		cursorY = y;
		checkCursor();
	}
}

void Interface::pressCursor()
{
	if (getGame())
	{
		if (markedCursorX == -1)
		{
			markedCursorX = cursorX;
			markedCursorY = cursorY;
			getGame()->injectStart(cursorX, cursorY);
		}
		else
		{
			markedCursorX = -1;
			markedCursorY = -1;
			getGame()->injectTarget(cursorX, cursorY);
		}
	}
}

pair<int, int> Interface::getMarkedCursor() const
{
	pair<int, int> retVal(markedCursorX, markedCursorY);
	return retVal;
}

pair<int, int> Interface::getCursor() const
{
	pair<int, int> retVal(cursorX, cursorY);
	return retVal;
}

void Interface::drawCursor() const
{
	glPushAttrib(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	
	if (getGame())
	{	
		float x = (float)getCursor().first;
		float y = (float)getCursor().second;
		
		glLineWidth(4);
		
		// draw cursor
		glColor4fv(cursorColor.toSmartArray().get());
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x-0.5, y-0.5, 0.07);
		glVertex3f(x+0.5, y-0.5, 0.07);
		glVertex3f(x+0.5, y+0.5, 0.07);
		glVertex3f(x-0.5, y+0.5, 0.07);
		glEnd();
		
		// draw marked cursor
		x = (float)getMarkedCursor().first;
		y = (float)getMarkedCursor().second;
		if (x != -1)
		{
			glColor4f(0.5, 0, 3, 1);
			glBegin(GL_LINE_STRIP);
			glVertex3f(x-0.5, y-0.5, 0.07);
			glVertex3f(x+0.5, y-0.5, 0.07);
			glVertex3f(x+0.5, y+0.5, 0.07);
			glVertex3f(x-0.5, y+0.5, 0.07);
			glVertex3f(x-0.5, y-0.5, 0.07);
			glEnd();
		}
		
		glLineWidth(2);
	}

	glPopAttrib();	
}

void Interface::reset()
{
	showWinnerFlag = true;
	winnerButton->deactivate();
	cursorX = -1;
	cursorY = -1;
}

void Interface::showWinner()
{
	if (showWinnerFlag)
	{
		showWinnerFlag = false;
		assert("can't show winner because there is no winner at the moment!" && getGame()->getWinner());
		winnerButton->setFontColor(getGame()->getWinner()->getColor());
		winnerButton->activate();
	}
}


// ------------------------------- private -----------------------------------

void Interface::checkCursor()
{
	// check position
	if (cursorX >= getGame()->getBoardDimenstions().first)
		cursorX = getGame()->getBoardDimenstions().first - 1;
	else if (cursorX < 0)
		cursorX = 0;
	if (cursorY >= getGame()->getBoardDimenstions().second)
		cursorY = getGame()->getBoardDimenstions().second - 1;
	else if (cursorY < 0)
		cursorY = 0;
	
	// check color
	if (getMarkedCursor().first != -1 &&
		getGame()->checkMove(getMarkedCursor().first, getMarkedCursor().second,
		getCursor().first, getCursor().second))
		cursorColor.setRgba(0, 2, 0, 0.5);
	else if (getMarkedCursor().first == -1 && 
			getGame()->checkMove(getCursor().first, getCursor().second))
		cursorColor.setRgba(0, 2, 0, 0.5);
	else
		cursorColor.setRgba(2, 0, 0, 0.5);
}
