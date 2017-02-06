/**
 * @file Widget.hpp
 * @author sizilium
 * @date 22.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef WIDGET_HPP
#define WIDGET_HPP

// includes
#include <vs/Build.hpp>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/DefaultManagedMessage.h>
#include <vs/base/interfaces/MsgObserver.hpp>

namespace vs
{
namespace core
{
namespace gui
{

/** @class Widget
 * Base class for all gui widgets in the EasyFramework Gui module.
 * Each widget has a position (x and y) and a dimension (width and height).
 * There are basically gui events supported by virtual methods. Subclasses could implement these
 * methods to process the events (optional).
 * The GuiManager generates and emits these events to all active widgets.
 */
class VS_EXPORT Widget : public base::util::DefaultManaged
{
public:
	Widget(float x = 0, float y = 0, float sizeX = 10, float sizeY = 10)
	:x(x), y(y), sizeX(sizeX), sizeY(sizeY)
	{
	}
	
	virtual ~Widget()
	{
	}

	/**
	 * A specialized deactivate method. Emits a mouseLeavedEvent before the standard DefaultManaged
	 * deactivate method. 
	 * This is because the widget might call deinitialize stuff on mouseLeavedEvent.
	 */
	virtual void deactivate()
	{
		this->mouseLeavedEvent();	
		DefaultManaged::deactivate();
	}
	
	/**
	 * Translates the widget to another 2d coordinated. The x and y coordinates are the lower left
	 * corner of the widget.
	 * @param x Left is 0, right is variable dependent of viewport size and coordinate mode of the
	 * GuiManager.
	 * @param y Bottim is 0, top is variable dependent of viewport size and coordinate mode of the
	 * GuiManager.
	 */
	virtual void move(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	
	/**
	 * Gets the actual widget position. The x and y coordinates are the lower left corner of the 
	 * widget.
	 */
	virtual void getPosition(float &x, float &y) const
	{
		x = this->x;
		y = this->y;
	}

	/**
	 * A widget could sent a event (optional). So the user must can attach event handler on the 
	 * widget. In this case the subclass shoult implement this method,
	 * because the normal attach method inherited from MsgObservable<Event> will occure an 
	 * ambiguous error (the widget class inherits from two different observable classes...).
	 * This method will be well defined.
	 */
	virtual void attachEventHandler(base::interfaces::MsgObserver<base::interfaces::Event> *handler)	{}
	
	/**
	 * A widget could sent a event (optional. So the user must can detach event handler from the 
	 * widget. In this case the subclass shoult implement this method,
	 * because the normal attach method inherited from MsgObservable<Event> will occure an 
	 * ambiguous error (the widget class inherits from two different observable classes...).
	 * This method will be well defined.
	 */
	virtual void detachEventHandler(base::interfaces::MsgObserver<base::interfaces::Event> *handler)	{}
	
	/**
	 * Sets the widgets dimension (width and height).
	 */
	virtual void setSize(float width, float height) = 0;
	
	/**
	 * Gets the widgets dimension (width and height).
	 */
	virtual void getSize(float &width, float &height) const = 0;
	
	/**
	 * Draws the widget to the opengl context.
	 * This method only should be called by the GuiManager, because special opengl states are
	 * necessary (orthogonal perspective, blending etc.).
	 */
	virtual void update(double deltaT) = 0;
	
	/**
	 * This event will created by the GuiManager if the mouse hovers the widget.
	 * Subclasses only should implement this when needed.
	 */
	virtual void mouseHoverEvent(int x, int y)			{}
	
	/**
	 * This event will created by the GuiManager if the mouse entered the widget. Depends on
	 * the widgets coordinates and dimension.
	 * Subclasses only should implement this when needed.
	 */	
	virtual void mouseEnteredEvent()					{}
	
	/**
	 * This event will created by the GuiManager if the mouse leaves the widget. Depends on
	 * the widgets coordinates and dimension.
	 * Subclasses only should implement this when needed.
	 */
	virtual void mouseLeavedEvent()						{}
	
	/**
	 * This event will created by the GuiManager if the mouse left clicked on the widget.
	 * Subclasses only should implement this when needed.
	 * @param x The local x coordinate of the mouse in widget. 0 is on the left of the widget.
	 * @param y The local y coordinate of the mouse in widget. 0 is on bottom of the widget.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	virtual void mouseLeftClickEvent(int x, int y, bool pressed)		{}
	
	/**
	 * This event will created by the GuiManager if the mouse right clicked on the widget.
	 * Subclasses only should implement this when needed.
	 * @param x The local x coordinate of the mouse in widget. 0 is on the left of the widget.
	 * @param y The local y coordinate of the mouse in widget. 0 is on bottom of the widget.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	virtual void mouseRightClickEvent(int x, int y, bool pressed)	{}
	
	/**
	 * This event will created by the GuiManager if the mouse middle clicked on the widget.
	 * Subclasses only should implement this when needed.
	 * @param x The local x coordinate of the mouse in widget. 0 is on the left of the widget.
	 * @param y The local y coordinate of the mouse in widget. 0 is on bottom of the widget.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	virtual void mouseMiddleClickEvent(int x, int y, bool pressed)	{}
	
	/**
	 * This event will created by the GuiManager if the mouse wheel rolled above the widget.
	 * Subclasses only should implement this when needed.
	 * @param ticks A positive value if the mouse wheel goes up, a negative value if the mouse
	 * wheel goes down.
	 */
	virtual void mouseWheelEvent(char ticks)			{}
	
	/**
	 * This event will created by the GuiManager if the widget is selected and a key pressed 
	 * Subclasses only should implement this when needed.
	 */
	virtual void keyPressEvent(unsigned char key)		{}
	
	/**
	 * This event will created by the GuiManager if the widget is selected and a key released.
	 * Subclasses only should implement this when needed.
	 */
	virtual void keyReleaseEvent(unsigned char key)		{}

protected:
	float x, y;
	float sizeX, sizeY;
};

} // gui
} // core
} // vs

#endif  // WIDGET_HPP
