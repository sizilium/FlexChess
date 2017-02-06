/**
 * @file JavaStyleIterator.hpp
 * @author sizilium
 * @date 02.06.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef JAVASTYLE_ITERATOR_H
#define JAVASTYLE_ITERATOR_H

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace cont
{
/** @class JavaStyleIterator
 * This is an interfaces for all EasyFramework iterators. Look out for "iterator pattern"
 * to get further informations.\n
 * This interfaces instruct all EasyFramework iterators to implements the typical iterator
 * methods in java style (hasNext, next, remove).\n
 * This is a template iterator, so you don't need to cast the types! If casts are
 * necessary, of course you can use casts as usual.
 * 
 * @code // Example
 * vs::ut::StringList<double> myStringList;
 * myStringList.push_back(15.1, "length");
 * ...
 * // vs::ut::List<double> myList;		// maybe you want to exchange your container one time
 * // myList.push_front(15.1);
 * ...
 * 
 * // this code will be static! independent from the container and iterator! 
 * JavaStyleContainer<short> *abstractContainer = &myStringList;
 * // JavaStyleContainer<short> *abstractContainer = &myList;		// here you can use an other container
 *
 * // the SmartIterator holds a JavaStyleIterator!
 * SmartIterator<short> abstractIterator = abstractContainer->iterator();
 * while (abstractIterator.hasNext())				// this operations never changed
 *     cout << abstractIterator.next() << " ";
 * @endcode
 *
 * TODO : picture
 * Container:
 *        __     __     __     __    ..
 *       |__|   |__|   |__|   |__|  :..:
 * STL  begin()                     end() 
 *        /\     /\     /\     /\    /\
  * Java  next()...
 *    /\    /\     /\      /\    /\    
 * 
 * @see SmartIterator, JavaStyleContainer, StringList
 */
template<class T>
class VS_EXPORT JavaStyleIterator
{
public:
	virtual ~JavaStyleIterator();
   	/**
	 * Java style iterator method. Checks if there is a next element after the iterator
	 * position (Equivalent to - if (it != myContainer.end()) - in STL style).
	 * @return True if there is a next element depending on the iterator position.
	 */
	virtual bool hasNext() const = 0;

	/**
	 * Java style iterator method. Returns the current element and shift the iterator to
	 * next position (Equivalent to - *it++ - in STL style).
	 * @return The element (note the template type, no cast is needed).
	 */
	virtual T next() = 0;
	
	/**
	 * Returns the current element without iterator shifting!
	 * (no java style, but sometimes useful)
	 * @return The current element (note the template type, no cast is needed).
	 */
	virtual T current() const = 0;

	/**
	 * Java style iterator method (optional). Removes the current element from container,
	 * depending on the iterator position (no Equivalent in STL style). Implementation is
	 * optional, the default do nothing.
	 */
	virtual void remove()	{}

};

template<class T>
JavaStyleIterator<T>::~JavaStyleIterator()
{}

} // cont
} // base
} // vs

#endif	// JAVASTYLE_ITERATOR_H
