/**
 * @file MsgObserver.hpp
 * @author sizilium
 * @date 23.08.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MSG_OBSERVER_HPP
#define MSG_OBSERVER_HPP

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

/**
 * For observer pattern in java style. Means: observable can send a parameter
 * in the notifyEvent method when an update occured. This is useful in some
 * cases to avoid callbacks.\n
 * An Observer can be attached dynamic in an Observable object.
 * @code // Example:
 * 
 * class Message
 * {
 * public:
 *      void what()  
 * 		{ 
 * 			cout << "  message has passed ;-)" << endl; 
 * 		}
 * };
 * 
 * class Model : public vs::MsgObservable<Message>
 * { //... }
 * class View : public vs::MsgObserver<Message>
 * {
 *     void notify(Message &message)
 *   	{ 
 * 			cout << "view updated!" << endl;
 * 			message.what(); 
 *		}
 * };
 *
 * Model model;  View view; Message message;
 * model.attach(&view);
 *
 * model.notify(message);	// view be updated with a message!
 * 
 * 
 * @endcode
 * @see MsgObservable
 */
template<class T = Object>
class VS_EXPORT MsgObserver
{
public:
	MsgObserver()
	{
		blocking = false;
	}
	virtual ~MsgObserver() {}

	/**
	 * Called by Observable. Do not reimplement this in subclasses! Use the virtual notify 
	 * method instead!
	 */
	void notifyEvent(T &message)		// TODO? : make this private / protected? 
	{
		if (!blocking)
			notify(message);
	}
	
    /**
     * Implement this method (stub) to handle incoming events from an Observable.
     * @param message The message from the observed object (object state).
     */
	virtual void notify(T &message) = 0;
	
	void blockEvents(bool enable)
	{
		this->blocking = enable;
	}
	
private:
	bool blocking;
};

} // util
} // base
} // vs

#endif  // MSG_OBSERVER_HPP
