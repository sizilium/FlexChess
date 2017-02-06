/**
 * @file AbstractButton.hpp
 * @author sizilium
 * @date 25.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_BUTTON_HPP
#define ABSTRACT_BUTTON_HPP

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/Widget.hpp>
#include <vs/base/interfaces/MsgObservable.hpp>
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/core/gl/Color.h>

namespace vs
{
namespace core
{
namespace gui
{

/** @class AbstractButton
 * 
 */
class VS_EXPORT AbstractButton : 	public Widget,
									public base::interfaces::MsgObservable<base::interfaces::Event>
{
public:
	AbstractButton(float x = 0, float y = 0, float sizeX = 100, float sizeY = 30)
	:Widget(x, y, sizeX, sizeY)
	{
	}

	virtual ~AbstractButton()
	{
	}
	

	virtual void attachEventHandler(base::interfaces::MsgObserver<base::interfaces::Event> *handler)		
	{
		// area deallocation for the right attach method (else ambiguous)
		base::interfaces::MsgObservable<base::interfaces::Event>::attach(handler);
	}
	

	virtual void detachEventHandler(base::interfaces::MsgObserver<base::interfaces::Event> *handler)		
	{
		// area deallocation for the right detach method (else ambiguous)
		base::interfaces::MsgObservable<base::interfaces::Event>::detach(handler);
	}
	
	virtual void setText(const std::string &text) = 0;
	virtual std::string getText() const = 0;
	
	virtual void setFontSize(int fontSize) = 0;
	virtual int getFontSize() const = 0;
	
	virtual void setSize(float width, float height) = 0;
	virtual void getSize(float &width, float &height) const = 0;
	
	virtual void setFontColor(gl::Color fontColor) = 0;
	virtual void setBackgroundColor(gl::Color backgroundColor) = 0;
	
	virtual gl::Color getFontColor() const = 0;
	virtual gl::Color getBackgroundColor() const = 0;

};

} // gui
} // core
} // vs

#endif  // ABSTRACT_BUTTON_HPP
