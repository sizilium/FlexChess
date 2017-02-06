/**
 * @file WidgetContainer.hpp
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef WIDGET_CONTAINER_HPP
#define WIDGET_CONTAINER_HPP

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/Widget.h>
#include <vs/base/cont/List.h>

namespace vs
{
namespace core
{
namespace gui
{

/** @class WidgetContainer
 * 
 */
class VS_EXPORT WidgetContainer : public Widget
{
public:
	WidgetContainer()
	{
		
	}
	
	virtual ~WidgetContainer()
	{
		
	}
	
	void add(Widget *widget)
	{
		
	}
	
	void remove(Widget *widget)
	{
		
	}
	
	void removeAll()
	{
		
	}
	
	void updateChildWidgets(double deltaT = 0)
	{
		
	}
	
private:
	base::cont::List<Widget *> childWidgets;
};

} // gui
} // core
} // vs

#endif  // WIDGET_CONTAINER_HPP
