#ifndef OPTIONSMENU_H_
#define OPTIONSMENU_H_

#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/core/gui/ButtonEvent.hpp>
#include <vs/base/util/DefaultManagedGroup.h>
#include <vs/core/gui/VectorButtonSimple.h>

using namespace vs::base::interfaces;
using namespace vs::core::gui;
using namespace vs::base::util;
using namespace std;

enum ControllerType
{
	controller,
	stdChessController
};

class Options
{
public:
	// make default options
	Options()
	{
		controllerType = stdChessController;
	}
	
	enum ControllerType controllerType;
	
};

/**
 * Gui stuff.
 */
class OptionsMenu  : public MsgObserver<Event>
{
public:
	OptionsMenu();
	virtual ~OptionsMenu();
	
	void activate()				{menuGroup.activate();}
	void deactivate()			{menuGroup.deactivate();}
	void notify(Event &message);

	bool isActive() const		{return menuGroup.isActive();}


private:
	void refreshButtons();
	
	VectorButtonSimple *controller_1, *controller_2;
	DefaultManagedGroup menuGroup;
};

#endif /*OPTIONSMENU_H_*/
