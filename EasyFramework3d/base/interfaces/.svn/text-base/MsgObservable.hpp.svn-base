/**
 * @file MsgObservable.hpp
 * @author sizilium
 * @date 23.08.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MSG_OBSERVABLE_HPP
#define MSG_OBSERVABLE_HPP

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/base/interfaces/Event.hpp>
#include <vs/base/interfaces/Object.hpp>
#include <vs/base/cont/List.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/**
 * @class MsgObservable
 * For observer pattern in java style. An observable can attach and detach 
 * several observers.\n 
 * Useful for MVC pattern for example (model, view, controller).\n
 * The MsgObservable be able to send a message to the observers. So you can avoid
 * callbacks in some cases. Because the template you need no cast!
 * @see MsgObserver
 */
template <class T = Object>
class VS_EXPORT MsgObservable
{
public:

	MsgObservable()
	{
		it = observers.begin();
	}
	
	virtual ~MsgObservable()
	{}

	/**
	 * Register a new observer on this model.
	 * @param observer pointer to observer
	 */
	void attach(MsgObserver<T> *observer)
	{
		observers.push_back(observer);
	}

	/**
	 * Unregister a known observer on this model.
	 * @param observer pointer to observer
	 */
	void detach(MsgObserver<T> *observer)
	{
		it = observers.begin();
		while (it != observers.end())
		{
			if (*it == observer)
			{
				observers.erase(it);
				break;
			}
			++it;
		}
	}

	/**
	 * Tells all observers that the model has changed and calls the observers
	 * notifyUpdates methods.\n
	 * @param message You can tell what has changed in particular. The
	 * advantage in comparison to the default Observer is more performance:
	 * The observer doesn't have to query the state from the object (no callback).
	 */
	void notify(T &message)
	{
		it = observers.begin();
		while (it != observers.end())
		{
			(*it)->notifyEvent(message);
			++it;
		}
	}

	/**
	 * @todo notify all observers in an extra thread (create thread, do work,
	 * destroy thread)
	 */
	void notifyThreaded(T &message)
	{
		// TODO? multithreaded notify in observable

	}
	
	int numObservers() const
	{
		return observers.size();
	}

private:
	cont::List<MsgObserver<T>* > observers;
	
	// within a template you need the typename specifier to declare a sub template
	typename cont::List<MsgObserver<T>* >::Iterator it;
};


// -------------------------------------------------------------------------------


/**
 * Specialized MsgObservable template class for vs::Event messages. Whenever you
 * instantiate a MsgObservable<Event> object, this implementation will be used 
 * instead the standard implementation.\n
 * The notify method is modified in this specialized template class. When an
 * Event is accepted by any MsgObserver, the notifiing will stopped (more performance)!
 * @see MsgObservable, vs::Event
 */
template<> 
class MsgObservable<Event>
{
public:

	MsgObservable()
	{
		it = observers.begin();
	}
	
	virtual ~MsgObservable()
	{}

	/**
	 * Register a new observer on this model.
	 * @param observer pointer to observer
	 */
	void attach(MsgObserver<Event> *observer)
	{
		observers.push_back(observer);
	}

	/**
	 * Unregister a known observer on this model.
	 * @param observer pointer to observer
	 */
	void detach(MsgObserver<Event> *observer)
	{
		it = observers.begin();
		while (it != observers.end())
		{
			if (*it == observer)
			{
				observers.erase(it);
				break;
			}
			++it;
		}
	}

	/**
	 * Tells all observers that the model has changed and calls the observers
	 * notifyUpdates methods. The message is an Event\n
	 * If any Observer accepted the Event, the notifiing will stopped.
	 * @param message You can tell what has changed in particular. The
	 * advantage is more performance: The observer must not search the change in
	 * the model (no callback).
	 * @see vs::Event
	 */
	void notify(Event &message)
	{
		it = observers.begin();
		while (it != observers.end())
		{
			(*it)->notifyEvent(message);
			
			// check the accepted flag
			if (message.isAccepted())
				return;
			++it;
		}
	}

	/**
	 * @todo notify all observers in an extra thread (create thread, do work,
	 * destroy thread)
	 */
	void notifyThreaded(Event &message)
	{
		// TODO? multithreaded notify in observable

	}
	
	int numObservers() const
	{
		return observers.size();
	}

private:
	cont::List<MsgObserver<Event>* > observers;
	cont::List<MsgObserver<Event>* >::Iterator it;
};

} // util
} // base
} // vs

#endif  // MSG_OBSERVABLE_HPP
