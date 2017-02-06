/**
 * @file Counted.hpp
 * @author sizilium
 * @date 11.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_COUNTED_H
#define VS_COUNTED_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>

namespace vs
{
namespace base
{
namespace util
{

/** @class Counted
 * With this base class you can controll the number of objects a class can have at the
 * same time. With the objectCount() method you can get the actual object count.
 * If anybody try to instantiate too much objects, an exception will be thrown.
 * @code // Example
 * 
 * // in *.h file:
 * MyTestClass : private Counted<MyTestClass>   // inherite private, else you need a virtual destructor!
 * {
 * public:
 * 
 *     ... custom stuff ...
 *     
 *     // make the objectCount() method public again (because private heredity)
 *     using Counted<MyTestClass>::objectCount;
 * };
 * // specify the maximum number of object for this class
 * template <class T> int Counted<MyTestClass>::maxObjects = 3;
 * 
 * ...
 * 
 * // in *.cpp file:
 * cout << MyTestClass::objectCount() << endl;    // output: 0
 * 
 * try
 * {
 *     MyTestClass a;    // ok
 *     MyTestClass b;    // ok
 *     MyTestClass c;    // ok
 *     MyTestClass d;    // not ok!
 * }
 * catch (ex::Exception &e)
 * {
 *     e.addPlaceOfError(__FILE__, __LINE__);
 *     e.printStackTrace();
 * }
 * 
 * cout << MyTestClass::objectCount() << endl;    // output: 3 (maximum)
 * @endcode 
 * 
 * If you forget the ::maxObjects definition an error occured at compile time.
 * Only define ONE class inherits Counted per header file, else an error occured!
 * (Commonly it's better to create a file per class everytime). 
 */
template<class BeingCounted> class VS_EXPORT Counted
{
public:
	/**
	 * This static method returns the actual number of object of this a class.
	 * @return A value between 0 and maxObjects.
	 */
	static int objectCount()
	{
		return numObjects;
	}

protected:
	/**
	 * Constructor is protected. This is only a base class. You can not instantiate it.
	 * Only subclasses can instantiate (this constructor is protected, not private).
	 * The constructor increment the object count.
	 */
	Counted()
	{
		init();
	}

	/**
	 * Copyconstructor is protected. This is only a base class. You can not instantiate it.
	 * The copyconstructor increment the object count.
	 */
	Counted(const Counted &op2)
	{
		init();
	}

	/**
	 * The destructor decrement the object count.
	 */
	~Counted()
	{
		--numObjects;
	}

private:
	static numObjects;
	static maxObjects;

	void init()
	{
		//assert ("There are too many instances of this class!" && numObjects < maxObjects);

		if (numObjects >= maxObjects)
		{
			Exception e(__FILE__, __LINE__, 
			                "There are too many instances of this class! (only " /*+
			                maxObjects +*/ " instances allowed)");
			throw e;
		}

		++numObjects;
	}
};

template<class BeingCounted>
int Counted<BeingCounted>::numObjects;

} // util
} // base
} // vs

#endif  // VS_COUNTED_H
