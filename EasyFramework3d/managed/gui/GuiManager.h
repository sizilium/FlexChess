/**
 * @file GuiManager.h
 * @author sizilium
 * @date 04.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>

namespace vs
{
// predeclarations
namespace base {namespace interfaces {class AbstractManaged; }}
namespace core {namespace gui {class Widget; }}

namespace managed
{
namespace gui
{
// predeclarations
class AbstractGuiFactory;
class GuiManager;

/**
 * A modified DefaultManagment class for the GuiManager. Don't care about it...
 */
class VS_EXPORT GuiManagment : public base::util::DefaultManagment
{
public:
	GuiManagment(GuiManager *guiManager);
	virtual ~GuiManagment() {}
	
	void update(double deltaT);
	void notify(base::util::DefaultManagedMessage &message);
	
private:
	friend class GuiManager;
	GuiManager *guiManager;
};


// ---------------------------------------------------------------------


/** @class GuiManager
 * The GuiManager stores gui widgets like buttons, textboxes, sliders, windows, spinboxes,
 * textedits, images, shapes etc. All active widgets will draw to the opengl context by the
 * update method (the Context class call this automatically). Only active widgets will drawed.
 * Further the GuiManager holds the selected widget (optional).
 * You can inject user actions like mouse inputs, key inputs etc. to inform the gui about events.\n
 * For gui drawing there are two common modes:
 * -absolue coordinate system (default)
 * -relative coordinate system (optional, based on given reference resolution)
 * 
 * The disadvantage of absolute coordinate system is the rigid positioning of widgets. When you
 * change the resolution (opengl viewport), the widgets might out of view, or the widgets are
 * no more aligned correctly. The advantage is the simple usage.
 * The relative coordinate system fix these problems, but you must choose a reference resolution.
 * The disadvantage is that the widget might draw blassed a bit (by scaling the viewport).
 */
class VS_EXPORT GuiManager : public base::interfaces::AbstractManager<GuiManager>
{
public:
	/**
	 * The constructor sets the following default values:
	 * -viewport/refviewport width = 1024
	 * -viewport/refviewport height = 768
	 * -coordinate mode = absoluteCoordinates
	 * -active widget = NULL
	 */
	GuiManager();
	virtual ~GuiManager();

	/**
	 * Use this enum for the setCoordinateMode method.
	 * @code // Example
	 * GuiManager manager;
	 * manager.setCoordinateMode(GuiManager::relativeCoordinates);
	 * @endcode
	 */
	enum GuiCoordinateMode
	{
		absoluteCoordinates,	/*!< for using absolute coordinates for following gui drawing */
		relativeCoordinates		/*!< for using relative coordinates for following gui drawing */
	};

	/**
	 * Sets the reference resolution. Only important for the relativeCoordinates mode.
	 * When you use this mode, the real resolution is irrelevant and all real resolutions
	 * will streched from the reference resolution.
	 * You can see side effects when you have a reference resolution ratio of 4:3 and a real
	 * resolution ratio of 16:9 for example. In this case the font will drawed blurred.
	 * @param x Default is 0
	 * @param y Default is 0
	 * @param width Default is 1024.
	 * @param height Default is 768.
	 */
	void setReferenceResolution(int x, int y, int width, int height);
	
	/**
	 * Sets a coordinate mode. See enum GuiCoordinateMode for further informations.
	 * The default is absoluteCoordinates.
	 */
	void setCoordinateMode(enum GuiCoordinateMode mode);
	
	/**
	 * Returns the activ coordinate mode.
	 */
	GuiManager::GuiCoordinateMode getCoordinateMode() const;

	/**
	 * Injects a new opengl viewport. It's not important if you use the relative coordinate mode.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 */
	void injectViewport(int x, int y, int width, int height);
	
	/**
	 * Injects a mouse hover event. If a widget is affected, the virtual mouseEnteredEvent or 
	 * mouseLeavedEvent and the mouseHoverEvent of the widget will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 */
	void injectMouseHover(int x, int y);
	
	/**
	 * Injects a mouse left click event. If a widget is affected, the virtual mouseLeftClickEvent
	 * of the widget will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	void injectMouseLeftClick(int x, int y, bool pressed = true);
	
	/**
	 * Injects a mouse right click event. If a widget is affected, the virtual mouseRightClickEvent
	 * of the widget will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	void injectMouseRightClick(int x, int y, bool pressed = true);
	
	/**
	 * Injects a mouse middle click event. If a widget is affected, the virtual mouseMiddleClickEvent
	 * of the widget will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 */
	void injectMouseMiddleClick(int x, int y, bool pressed = true);
	
	/**
	 * Injects a mouse wheel event. If a widget is affected, the virtual mouseWheelEvent
	 * of the widget will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param ticks A positive value if the mouse wheel goes up, a negative value if the mouse
	 * wheel goes down.
	 */
	void injectMouseWheel(char ticks);
	
	/**
	 * Injects a key pressed event. Only the virtual method keyPressEvent of the active widget
	 * will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param key @TODO
	 */
	void injectKeyPress(unsigned char key);
	
	/**
	 * Injects a key released event. Only the virtual method keyReleaseEvent of the active widget
	 * will be called.
	 * This method will called by the Context class automatically. Use the Context class
	 * method instead!
	 * @param key @TODO
	 */
	void injectKeyRelease(unsigned char key);
	
	/**
	 * Gets all names actually stored in the manager. With the names you can get
	 * access to the managed using getManaged(name) method. Note that these methods
	 * are not optimal for performance. Use handler (pointer) to the managed instead.
	 * @param names Pass any vs container.
	 * @code // Example
	 * ...
	 * List<string> myList;
	 * myManager->getManagedNames(&myList);
	 * ...
	 * @endcode
	 */
	void getManagedNames(vs::base::cont::JavaStyleContainer<std::string> *names) const;

	/**
	 * Getter for managed elements.
	 * @name The search string of the managed.
	 * @return A pointer to the managed or a NULL pointer if the managed name not exist.
	 */
	vs::base::interfaces::AbstractManaged* getManaged(const std::string &name) const;
	
	/**
	 * Removes an gui widget element from the manager finally (no deactivate).
	 * @name The search string of the managed. If the managed does not exist nothing
	 * will happen.
	 */
	void removeManaged(const std::string &name);
	
	/**
	 * Updates the manager and with this all containing managed widget elements. Note that
	 * the Context::update will update this automatically.
	 * If the widgets contains child widgets, they will update these again (recursively).
	 */
	void update(double time);

	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "GuiManager"; }
	
	/**
	 * This method clears all managed from the manager.
	 */
	virtual void clear();
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;

private:
	friend class AbstractGuiFactory;
	friend class GuiManagment;
	void checkMouseEntered(core::gui::Widget *widget);	// called by GuiManagment when widget activated
	
	/**
	 * Adds a managed object to the manager. The method is private. 
	 * Only the AbstractUpdateableFactory's (sub classes) can use this operation!
	 */
	void addManaged(vs::base::interfaces::AbstractManaged *managed);
	
private:
	// Only important in relative coordinate mode. In this case this help function converts the
	// real coordinates to relative.
	void checkCoordinateMode(int &x, int &y);
	
	int viewportX, viewportY, viewportWidth, viewportHeight;
	int refViewportX, refViewportY, refViewportWidth, refViewportHeight;
	enum GuiCoordinateMode coordinateMode;

	int oldX, oldY;		// save last mouse position
	core::gui::Widget *selectedWidget;
	GuiManagment managment;
};


} // gui
} // managed
} // vs

#endif  // GUI_MANAGER_H
