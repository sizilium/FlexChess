/**
 * @file Observable.hpp provides Observable class,
 *
 */
#ifndef  OBSERVABLE_HPP
#define  OBSERVABLE_HPP

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/Observer.hpp>
#include <vs/base/interfaces/Object.hpp>
#include <vs/base/cont/List.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/**
 * @class Observable 
 * For observer pattern. An observable can attach and detach several observers.\n 
 * Useful for MVC pattern for example (model, view, controller).
 * @see Observer
 */
class VS_EXPORT Observable
{
public:

	Observable()
	{
		it = observers.begin();
	}
	virtual ~Observable()
	{}

	/**
	 * Register a new observer to this model
	 * @param observer pointer to observer
	 */
	void attach(Observer *observer)
	{
		observers.push_back(observer);
	}

	/**
	 * Unregister a known observer on this model
	 * @param observer pointer to observer
	 */
	void detach(Observer *observer)
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
	 * Tells all observers that the model has changed and calls the attached observers
	 * notifyEvent() methods.
	 */
	void notify()
	{
		it = observers.begin();
		while (it != observers.end())
		{
			static_cast<Observer*> (*it)->notifyEvent();
			++it;
		}
	}

	/**
	 * @todo notify all observers in an extra thread (create thread, do work,
	 * destroy thread)
	 */
	void notifyThreaded()
	{
		// TODO? multithreaded notify in observable

	}
	
	int numObservers() const
	{
		return observers.size();
	}

private:
	base::cont::List<Observer*> observers;
	base::cont::List<Observer*>::Iterator it;
};


} // interfaces
} // base
} // vs

#endif // OBSERVABLE_HPP
