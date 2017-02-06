/**
 * @file JavaStyleContainer.hpp
 * @author sizilium
 * @date 03.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef JAVASTYLE_CONTAINER_H
#define JAVASTYLE_CONTAINER_H

#include <vs/Build.hpp>
#include <vs/base/cont/SmartIterator.hpp>
#include <boost/shared_array.hpp>
#include <iostream>
#include <typeinfo>
#include <memory>

// TODO? Remove this if the tr1 standard is implemented in c++
// makes the namespace tr1 known by using boost implementation
namespace std { namespace tr1 = ::boost; }

namespace vs
{
namespace base
{
namespace cont
{
// predeclarations
template <class T> class SmartIterator;
template <class T> class Tree;


/** @class JavaStyleContainer
 * This is an interfaces for all EasyFramework containers. Look out for "iterator pattern"
 * or "Java collection" to get further informations.\n
 * This interfaces instruct all EasyFramework containers to implements a createIterator(),
 * add() and remove() method in java style.\n
 * The other methods simply will added automatically (by default implementation).
 * @see JavaStyleIterator
 */
template<class T>
class VS_EXPORT JavaStyleContainer
{
public:
	virtual ~JavaStyleContainer();
	
	/**
	 * All containers with this interfaces are able to create JavaStyleIterator's which
	 * placed in a SmartIterator.
	 * Must implement by subclasses. If the container is empty, a SmartIterator will initialized 
	 * with a NullIterator and return!
	 * @return An smart iterator to the first element of the container.
	 * @see SmartIterator, NullIterator
	 */
	virtual SmartIterator<T> iterator() const = 0;

	/**
	 * Adds a new element to the container (by default on the end). This is an interfaces
	 * method (must implement by subclasses).
	 * @param element The element to add.
	 */
	virtual void add(const T element) = 0;

	/**
	 * Adds all elements from a specific container to this container.\n
	 * Method will added automatically by default implementation.
	 * @param cont The specific container with all elements to add.
	 */
	virtual void addAll(const JavaStyleContainer<T> *cont)
	{
		SmartIterator<T> it = cont->iterator();
		while (it.hasNext())
			this->add(it.next());
	}
	
	/**
	 * Removes an element from the container. If there are more than one entry, all
	 * entries will removed.\n
	 * Must implement by subclasses.
	 * @param element The element to remove.
	 * @return True if the container contained the specific element.
	 */
	virtual bool remove(const T element) = 0;

	/**
	 * Removes all elements from a specific container from this container. If there are
	 * more than one entry of same value, all entries will removed.\n
	 * Method will added automatically by default implementation.
	 * @param cont The specific container with elements to remove.
	 * @return True if the container changed as a result of the call.
	 */
	virtual bool removeAll(const JavaStyleContainer<T> *cont)
	{
		bool changed = false;
		SmartIterator<T> it = cont->iterator();
		while (it.hasNext())
			if (this->remove(it.next()))
				changed = true;

		return changed;
	}

	/**
	 * Retains only the elements in this collection that are contained in the specified
	 * container (optional operation). In other words, removes from this container all
	 * of its elements that are not contained in the specified container.\n
	 * Method will added automatically by default implementation.
	 * @ param cont The specific container with elements to be retained.
	 * @return True if the container changed as a result of the call.
	 */
	virtual bool retainAll(const JavaStyleContainer<T> *cont)
	{
		bool changed = false;
		T tmp;
		SmartIterator<T> it = this->iterator();
		while (it.hasNext())
		{
			tmp = it.next();
			if (!cont->contains(tmp))
			{
				this->remove(tmp);
				changed = true;
			}
		}

		return changed;
	}
	
	/**
	 * Checks if the container contains an element.\n
	 * Method will added automatically by default implementation.
	 * @param element Search this element in the container.
	 * @return True if the element is present in this container.
	 */
	virtual bool contains(const T element) const
	{
		SmartIterator<T> it = this->iterator();
		while (it.hasNext())
			if (it.next() == element)
				return true;
		
		return false;
	}
	
	/**
	 * Checks if the container contains ALL elements of a specific container.\n
	 * Method will added automatically by default implementation.
	 * @param cont The specific container with elements to search.
	 * @return True if this container contains all elements of the specific container.
	 */
	virtual bool containsAll(const JavaStyleContainer<T> *cont) const
	{
		SmartIterator<T> it = cont->iterator();
		while (it.hasNext())
		{
			if (!this->contains(it.next()))
				return false;
		}
		return true;
	}
	
	/**
	 * Count the elements.\n
	 * Method will added automatically by default implementation.
	 * @return Hole number of elements in the container.
	 */
	virtual int size() const
	{
		int count = 0;
		SmartIterator<T> it = this->iterator();
		while(it.hasNext())
		{
			++count;
			it.next();
		}
		return count;
	}
	
	/**
	 * Removes all elements from the container.\n
	 * Method will added automatically by default implementation.
	 */
	virtual void clear()
	{
		SmartIterator<T> it = this->iterator();
		while (it.hasNext())
		{
		//	it->remove();	// not all iterators supports remove!
		//	it->next();
			this->remove(it.next());
		}
	}
	
	/**
	 * Checks if the container is empty.\n
	 * Method will added automatically by default implementation.
	 * @return True if there is an element in the container, else false.
	 */
	virtual bool isEmpty() const
	{
		SmartIterator<T> it = this->iterator();
		
		if (it.isNullIterator())
			return true;
		else
			return false;
	}
	
	/**
	 * Convert method. All elements will be created to an c++ array on the heap (copy).\n
	 * Important: First check the maximum limit of the array with the size() method.\n
	 * Method will added automatically by default implementation.
	 * @return A pointer to array with type custom T.
	 */
	virtual T* toArray() const
	{
		T *array = new T[this->size()];
		
		SmartIterator<T> it = this->iterator();
		int i = 0;
		while (it.hasNext())
			array[i++] = it.next();
		
		return array;
	}	

	/**
	 * Convert method. All elements will be created to an c++ array on the heap (copy).\n
	 * Important: First check the maximum limit of the array with the size() method.\n
	 * You can get the array by return value (pointer) or reference parameter (ref pointer).
	 * Don't forget to delete the array after usage!
	 * Method will added automatically in sub classes by default implementation.
	 * @param refArray You can get the array by reference. If there is an old array, it
	 * will be deleted first.
	 * @return A pointer to array with type custom T.
	 */
	virtual T* toArray(T *&refArray) const
	{
		T *array = new T[this->size()];
		
		SmartIterator<T> it = this->iterator();
		int i = 0;
		while (it.hasNext())
			array[i++] = it.next();
		
		if (refArray != NULL)
			delete refArray;
		
		refArray = array;
		return array;
	}
	
	/**
	 * Convert method. All elements will be created to an c++ array on the heap (copy).\n
	 * Important: First check the maximum limit of the array with the size() method.\n
	 * You will get a auto_ptr so you don't have to delete the array manually.
	 * @return A smart pointer (std).
	 * @code // Example
	 * List<int> list;
	 * ...
	 * auto_ptr<int> smartPtr = list.toSmartArray();
	 * for (int i = 0; i < list.size(); i++)
	 *     cout << *smartPtr + i << endl;
	 * // after usage the array will be deleted automatically! (no delete smartPtr)
	 * @end code
	 */
	virtual std::tr1::shared_array<T> toSmartArray() const
	{
		T *array;
		toArray(array);
		return std::tr1::shared_array<T>(array);
	}
};

template<class T>
JavaStyleContainer<T>::~JavaStyleContainer()
{}

} // cont
} // base
} // vs

#endif	// JAVASTYLE_CONTAINER_H
