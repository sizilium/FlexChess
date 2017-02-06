/**
 * @file Observer.hpp provides Observer class for the observer pattern in java
 * style; means: observable can send a parameter in the update method when
 * an update occured (more performance).
 * @see Observer, Observable
 */
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

// includes
#include <vs/Build.hpp>
#include <list>
#include <vs/base/interfaces/Object.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{
using namespace std;

/**
 * @class Observer 
 * Support for observer pattern. The Observer is just a interfaces wich expect the
 * notifyEvent() method in subclasses. With this interfaces the class will be able to
 * attach to an observable.
 * @see Observable
 * @code // Example:
 *
 * class Model : public vs::Observable
 * { //... }
 * class View1 : public vs::Observer
 * {
 *     void notify()
 *   	{ 
 * 			cout << "view1 updated!" << endl; 
 *		}
 * };
 * class View2 : public Observer
 * {
 *     void notify()
 *     {
 *          cout << "view2 updated!" << endl;
 *     }
 * };
 *
 * Model model;  View1 view1;  View2 view2
 * model.attach(&view1);  model.attach(&view2);
 *
 * model.notify(message);	// view1 and view2 will be updated!
 * @endcode
 */
class VS_EXPORT Observer
{
public:
	Observer()
	{
		blocking = false;
	}
	virtual ~Observer() {}

	/**
	 * Called by Observable. Do not reimplement this in subclasses! Use the virtual notify 
	 * method instead!
	 */
	void notifyEvent()
	{
		if (!blocking)
			notify();
	}
	
    /**
     * Write this method (stub) to handle incoming events from an Observable.
     */
	virtual void notify() = 0;
	
	void blockEvents(bool enable)
	{
		this->blocking = enable;
	}
	
private:
	bool blocking;
};


} // interfaces
} // base
} // vs

#endif // OBSERVER_HPP
