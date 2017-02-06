/**
 * @file ReferenceCounting.h
 * @author sizilium
 * @date 23.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 * \n
 * Two helper classes for reference counting support. 
 */

#ifndef REFERENCE_COUNTING_H
#define REFERENCE_COUNTING_H

// includes
#include <vs/Build.hpp>
#include <stdlib.h>

namespace vs
{
namespace base
{
namespace util
{

/** @class RcObject
 * This class is one of two helper classes for reference counting support.
 * It capsules the reference counter and provides some methods to get some informations.
 * If the counter will be 0, the class deletes automatically. Put all values you want to
 * equip with reference counting in an extra structure wich inherit this class. Then
 * direct a vs::RcPtr to this structure to get access to the values (and get automatic
 * reference handling).\n
 * \n
 *               vs::RcObject
 *                   /_\
 * MyObject           |
 * -vs::RcPtr ---> MyValue ---> (Heap) optional
 * 
 * @see RcPtr
 */
class VS_EXPORT RcObject
{
public:
	/**
	 * Increased the reference counter.
	 */
	void addReference();
	
	/**
	 * Lessens the reference counter. If the counter is 0, the class deleted 
	 * automatically!
	 */
	void removeReference();
	
	/**
	 * Marks this class as unshareable. If the class is once marked unshareable, you
	 * cannot mark is shareable never again!\n
	 * A vs::RcPtr uses this information (only sharable objects will referenced).\n
	 * Whenever you return a reference to value in your subclass, mark it as unshareable!
	 * Else all referenced objects will changed too (copy on write)!
	 */
	void markUnshareable();
	
	/**
	 * Returns if the object is shareable.
	 * @return True if the object is shareable.
	 */
	bool isShareable() const;
	
	/**
	 * Returns if the object is shared by others. In this case the reference counter 
	 * is higher than 1.
	 * @return True if the object is shared.
	 */
	bool isShared() const;

protected:
	// no intance of this class
	RcObject();

	// uncopyable
	RcObject(const RcObject &op2);
	RcObject& operator=(const RcObject& op2);
	
	virtual ~RcObject();

private:
	int refCount;
	bool shareable;
};



/** @class RcPtr
 * This class is one of two helper classes for reference counting support.
 * It capsules the reference counting logic! Direct this smart pointer to
 * an RcObject struct. See example...
 * @code // Example
 * class MyClass
 * {
 * public:
 *     MyClass() : value(new Value) {}  // create Value with new!
 *     virtual ~MyClass() {}            // here is nothing to do...
 *	
 *     void setValue(const string &name)
 *     {
 *         if (value->isShared())   // copy on write. Create an extra value to change... 
 *             value = new Value;
 *         value->name = name;      // set name
 *     }
 * 
 *     const string& getValue() const
 *     {
 *         return value->name;     // return the string value (a copy or a CONST reference)
 *     }
 * 
 *     string& getValueRef()
 *     {
 *         if (value->isShared())    // because the reference you must make a copy eventually
 *             value = new Value;
 *         value->markUnshareable(); // mark the value as unshareable (forever)
 *         return value->name;       // return the reference to string value
 *     }
 *	
 * private:
 *     struct Value : public RcObject  // use struct for public access
 *     {
 *         string name;          // in this example the value is a string
 *     };
 *	
 *     RcPtr<Value> value;    // the smart pointer to the string value
 * };
 * 
 * ...
 * Value test, test2, test3;
 * test.setValue("a very long string should share with other object for more performance and memory reduce");
 * test2 = test;      // two objects but one string (shared)!
 * test3 = test2;     // three objects but one string ditto.
 * test.setValue("new string value");  // copy on write. 
 *
 * cout << test.getValue() << endl;    // output: new string value
 * cout << test2.getValue() << endl;    // output: a very long string should share with other object for more performance and memory reduce
 * cout << test3.getValue() << endl;    // output: a very long string should share with other object for more performance and memory reduce
 *
 * string *ref;
 * ref = test.getValueRef(); // test is unshareable now (forever) ...
 * ref->clear();             // ... because everytime it can happens unpredictably like this
 * 
 * @endcode
 */
template<class T>
class VS_EXPORT RcPtr
{
public:
	/**
	 * Standard constructor (with default NULL pointer).
	 * @param realPtr Optionally you can init the smart pointer with a reat
	 * pointer to an RcObject object. The reference will counted automatically 
	 * by this class.
	 */
	RcPtr (T *realPtr = NULL)
	:pointee(realPtr)
	{
		init();
	}
	
	/**
	 * Copyconstructor. The reference will counted automatically.
	 * @param op2 Another RcPtr with same type.
	 */
	RcPtr (const RcPtr &op2)
	:pointee(op2.pointee)
	{
		init();
	}
	
	/**
	 * Destructor will decrement the count automatically. If the RcObject's
	 * counter is 0, it will be deleted.
	 */
	~RcPtr()
	{
		if (pointee)
			pointee->removeReference();
	}
	
	/**
	 * Redirection of the RcPtr. Decrements the counter to the old RcObject
	 * and increase the counter of the new RcObject automatically.
	 */
	RcPtr& operator=(const RcPtr &op2)
	{
		if (pointee != op2.pointee)
		{
			if (pointee)
				pointee->removeReference();
			pointee = op2.pointee;
			init();
		}
		return *this;
	}
	
	/**
	 * Access to pointer.
	 */ 
	T* operator->() const
	{
		return pointee;
	}
	
	/**
	 * Access to pointers value.
	 */
	T& operator*() const
	{
		return *pointee;
	}
	
//	/**
//	 * Operator for implicit type cast. With this operator the smart pointer is 
//	 * comparable with NULL, 0 or not NULL, 0. Simultaneously it is dangerous because
//	 * the smart pointer can convert to a normal dumb pointer in undesirable situations.
//	 * @code // Example
//	 * {
//	 *     RcPtr<MyClass> ptr;
//	 *     ...
//	 *     if (ptr == NULL)    // this is possible now!
//	 *         ...
//	 * 
//	 *     delete ptr;         // unfortunately this is possible too!
//	 * }                       // the program crashes here (becaus two delete's)
//	 * 
//	 * @endcode
//	 * 
//	 */
//	operator void*()
//	{
//		return pointee;
//	}
	
	/**
	 * Method to check if the smart pointer is NULL, 0 or not. Because the operator void*()
	 * for implicit cast is not safety you should use this function.
	 * @code // Example
	 * RcPtr<MyClass> ptr;
	 * ...
	 * // if (ptr == NULL)    // is not possible
	 * 
	 * if (ptr.isNull())      // use this instead
	 *     ...
	 * @endcode
	 */
	bool isNull() const
	{
		if (pointee)
			return false;
		else
			return true;
	}
	
	/**
	 * Resets the pointer to NULL. Like destructor but you can use the RcPtr
	 * again by using the operator=().\n
	 * The old pointee will decrement the reference count if exist.
	 */
	void clear()
	{
		if (pointee)
			pointee->removeReference();
		pointee = NULL;
	}
	
private:
	T *pointee;
	
	// private init method reduces code doubling
	void init()
	{
		// if the RcPtr is a NULL ptr do nothing (see operator= for future use)
		if (pointee == NULL)
			return;
		
		// make a copy of the pointee if there is unshareable!
		if (pointee->isShareable() == false)
			pointee = new T(*pointee);
		
		// increase reference count of pointee
		pointee->addReference();
	}
};


} // util
} // base
} // vs

#endif  // REFERENCE_COUNTING_H
