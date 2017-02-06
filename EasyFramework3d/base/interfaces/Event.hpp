/**
 * @file Event.hpp
 * @author sizilium
 * @date 23.08.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_EVENT_HPP
#define VS_EVENT_HPP

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class Event
 * 
 */
class VS_EXPORT Event
{
public:
	enum Type
	{
		None,
		OpenGlSettingsEvent,
		OStreamEvent,
		GuiEvent
	};

	Event(Type type)
	: mvarType(type), accepted(false)
	{}
	
	virtual ~Event() 
	{}

	Event::Type type() const	
	{ 
		return mvarType; 
	}
	
	void accept()
	{
		accepted = true;
	}
	
	bool isAccepted() const
	{
		return accepted;
	}
	
	template<class T>
	T* castTo()
	{
		return dynamic_cast<T*>(this);
	}
	
protected:
	Type mvarType;
	
private:
	bool accepted;
};

} // interfaces
} // base
} // vs

#endif  // VS_EVENT_HPP
