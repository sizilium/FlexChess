/**
 * @file ButtonEvent.hpp
 * @author sizilium
 * @date 26.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef BUTTON_EVENT_H
#define BUTTON_EVENT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/Event.hpp>
#include <string>

namespace vs
{
namespace core
{
namespace gui
{

/** @class ButtonEvent
 * 
 */
class VS_EXPORT ButtonEvent : public base::interfaces::Event
{
public:
	ButtonEvent(const std::string &name, int x, int y)
	:base::interfaces::Event(base::interfaces::Event::GuiEvent), name(name), x(x), y(y)
	{}

	std::string getName() const
	{
		return name;
	}

	void getClickCoords(int &x, int &y) const
	{
		x = this->x;
		y = this->y;
	}

private:
	std::string name;
	int x, y;
};

} // gui
} // core
} // vs

#endif  // BUTTON_EVENT_H
