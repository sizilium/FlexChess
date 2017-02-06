/**
 * @file HeapStuff.hpp
 * @author sizilium
 * @date 22.08.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef HEAP_STUFF_H
#define HEAP_STUFF_H

// includes
#include <vs/Build.hpp>
#include <list>
#include <vs/base/util/Exception.h>

namespace vs
{
namespace base
{
namespace util
{

/**
 * Prevents that a class can instantiate on heap (with new).\n
 * The new, new[], delete and delete[] operators are private!
 */
class VS_EXPORT NotOnHeap
{
private:
	static void *operator new(size_t size);
	static void *operator new[](size_t size);
	static void operator delete(void *ptr);
	static void operator delete[](void *ptr);
};

/**
 * Subclasses can check if there was created on heap (with new operator) or not, if they
 * inherits from this class and calling isOnHeap().\n
 * So you can check if you allowed to call the delete operator or not!\n
 * A second advantage is that the class will throw an exception if you try to
 * delete an object existing on the stack!
 */
template<class BeingT>
class VS_EXPORT HeapTracked
{
public:
	/**
	 * This exception will be thrown if you try to delete an object that does not
	 */
	class MissingAddressException : public base::util::Exception 
	{
	public:
		MissingAddressException()
		:base::util::Exception(__FILE__, __LINE__, "A HeapTracked object detected a illegal delete operation!")
		{}
	};
	
	virtual ~HeapTracked()
	{}
	
	/**
	 * This static overloaded new operator behaves like the normal new operator
	 * of course. Additional it record pointer addresses in background.
	 */
	static void *operator new (size_t size)
	{
		// reserve memory
		void *memPtr = ::operator new(size);
		
		// remarking pointer
		addresses.push_front(memPtr);
		return memPtr;
	}
	
	/**
	 * This static overloaded new operator behaves like the normal new operator
	 * of course. Additional it checks pointer addresses in background.
	 * @exception MissingAddresses When you call the delete operator on a object
	 * that doesn't exists on the heap, an exception will be thrown!
	 */
	static void operator delete (void *ptr)
	{
		// search for ptr
		std::list<RawAdress>::iterator it = find(addresses.begin(), 
		                                           addresses.end(), ptr);
		
		// if there a remarking ptr call the standart delete implementation
		if (it != addresses.end())
		{
			addresses.erase(it);
			::operator delete (ptr);
		}
		// else the object exists not on heap!!
		else
			throw MissingAddressException();
	}
	
	/**
	 * Checks if the class was created with new (existing on heap).
	 * @return True if the class existing on heap.
	 */
	bool isOnHeap() const
	{
		// get the adress of "this" object
		const void *rawAddress = dynamic_cast<const void*> (this);
		
		// if the object was calles with new, there are an entry in addresses.
		// search for this entry...
		std::list<RawAdress>::iterator it = find(addresses.begin(), 
		                                         addresses.end(), rawAddress);
		// if the entry was found return true ("this" exists on heap)
		return it != addresses.end();
	}
	
private:
	typedef const void *RawAdress;
	// list for remarking
	static std::list<RawAdress> addresses;
};

// definition of static member addresses
template<class BeingT>
std::list<const void *> HeapTracked<BeingT>::addresses;


/**
 * The class simply gets a new_handler in constructor and sets this in 
 * destructor again.
 */
class VS_EXPORT NewHandlerHolder
{
public:
	/**
	 * @param nh A new handler to hold.
	 */
	explicit NewHandlerHolder(std::new_handler nh)
	:handler(nh)
	{}
	
	/**
	 * Sets the old new_handler again.
	 */
	~NewHandlerHolder()
	{
		std::set_new_handler(handler);
	}
private:
	std::new_handler handler;
	
	// make the class uncopyable
	NewHandlerHolder(const NewHandlerHolder&);
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};


/**
 * This class make it easy to install userdefined new handlers for classes (not
 * for objects). A new handler will called if a new operation fails (no memory).
 * Normally there are only one global new handler. With this technique you can
 * specify several new handlers for separate error handling for classes.
 * 
 * @code // Example:
 * void outOfMem();	// user defined function for memory handling (if exception throwed)
 * 
 * class MyClass : public NewHandlerSupport<MyClass>	// "mixin class"
 * { ... }; 
 * ...
 * MyClass::set_new_handler(outOfMem);	// set new handler (only for this class)	
 * MyClass *object = new MyClass;		// calls outOfMem() if new abort
 * ...
 * std::string *s = new std::string;	// calls the global new handler if new abort 
 * 
 * MyClass::set_new_handler(NULL);		// sets new_handler to NULL
 * MyClass *object2 = new MyClass;		// throws an exception immediately! if new abort 
 * 
 * @endcode
 */
// T is never used. CRPTP - curiously recurring template pattern.
// The template cares for a copy for each class (because static methods).
template<class T>
class VS_EXPORT NewHandlerSupport
{
public:
	/**
	 * 
	 */
	static std::new_handler set_new_handler(std::new_handler p) throw ()
	{
		std::new_handler oldHandler = currentHandler;
		currentHandler = p;
		return oldHandler;
	}
	
	static void *operator new(std::size_t size) throw (std::bad_alloc)
	{
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		return ::operator new(size);
	}
	
	// other operator new versions
	
private:
	static std::new_handler currentHandler;
};

// initialize all currentHandler with NULL
template<class T>
std::new_handler NewHandlerSupport<T>::currentHandler = NULL;

} // util
} // base
} // vs

#endif  // HEAP_STUFF_H
