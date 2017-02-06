/**
 * @file SmartIterator.hpp
 * @author sizilium
 * @date 02.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_SMARTITERATOR_H
#define VS_SMARTITERATOR_H

// includes
#include <vs/Build.hpp>
#include <assert.h>
#include <iterator>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/cont/NullIterator.hpp>
//#include <vs/util/cont/Tree.hpp>
//#include <vs/util/cont/StringList.hpp>
//#include <vs/util/cont/List.hpp>

namespace vs
{
namespace base
{
namespace cont
{

// predeclarations
//template <class T> class Tree;
///template <class T> class StringList;
//template <class T> class List;
template <class T> class VS_EXPORT JavaStyleContainer;


/** @class SmartIterator
 * All vs containers have own specialized iterators. But you also have the possibility
 * for abstract programming. The SmartIterator is a common iterator wich can iterate over
 * every vs container.
 * Additional you can cast to specialized iterators. With the isNullIterator() method you
 * can check if the iterator is valid.\n
 * The SmartIterator also can used like a STL iterator, it implements all std::forward_iterator
 * features (you can apply STL algorithms).
 * 
 * @code // Example
 * // this code will be static! independent from the container and iterator! 
 * JavaStyleContainer<short> *abstractContainer = new Tree<short>;	// here you can change the container
 *
 * // the SmartIterator can iterate over all vs container!
 * SmartIterator<short> smartIterator = abstractContainer->iterator();
 * while (smartIterator.hasNext())				// this operations never changed
 *     cout << smartIterator.next() << " ";
 * 
 * smartIterator = abstractContainer->iterator();
 * ...
 * 
 * @endcode
 */
template <class T>
class SmartIterator : public JavaStyleIterator<T>, public std::iterator<std::forward_iterator_tag, T>
{
public:
	// typedefs
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;	// the minimal for all vs container

	SmartIterator()
	{
		jIterator = new JIteratorPtr(new NullIterator<T>, 1);
	}

	SmartIterator(JavaStyleIterator<T> *it)
	{
		jIterator = new JIteratorPtr(it, 1);
	}
	
	SmartIterator(const JavaStyleContainer<T> *cont)
	{
		*this = cont->iterator();
	}
	
	SmartIterator(const JavaStyleContainer<T> &cont)
	{
		*this = cont.iterator();
	}
	
	virtual ~SmartIterator()
	{
		deleteIterator();
	}
	
	SmartIterator(const SmartIterator<T> &it)
	{
		assert(it.jIterator != NULL);

		jIterator = it.jIterator;
		jIterator->refCount++;
	}
	
	void operator=(const SmartIterator<T> *it)
	{
		assert(it->jIterator != NULL);

		jIterator = it->jIterator;
		jIterator->refCount++;
	}
	
	void operator=(const SmartIterator<T> &it)
	{
		assert(it.jIterator != NULL);

		jIterator = it.jIterator;
		jIterator->refCount++;
	}
	
	bool isNullIterator()
	{
		assert(jIterator != NULL);
		
 		// RTTI with dynamic cast
		//NullIterator<T> derive, *derive_ptr;
 		//JavaStyleIterator<T> *base_ptr = &derive;
		//if (derive_ptr = dynamic_cast<NullIterator<T> *>(base_ptr))
		//	return true;
 		
 		// RTTI with type id
 		if (typeid(*(jIterator->ptr)) == typeid(NullIterator<T>))
 			return true;
		else
			return false;
	}
	
	bool hasNext() const
	{
		if (jIterator == NULL)
			return false;
		return jIterator->ptr->hasNext();
	}
	
	T next()
	{
		assert ("The SmartIterator isn't initilized!" && jIterator != NULL);
		return jIterator->ptr->next();
	}
	
	T current() const
	{
		assert ("The SmartIterator isn't initilized!" && jIterator != NULL);
		return jIterator->ptr->current();
	}
	
	operator bool() const
	{
		return bool (jIterator);
	}
	
//	/**
//	 * Returns the value of the entry dependent of the actual iterator position.
//	 * @return The entries value.
//	 */
//	reference operator*() const
//	{
//		assert ("The SmartIterator isn't initilized!" && jIterator != NULL);
//		return jIterator->ptr->operator*();
//	}
//
//	/**
//	 * Returns the value of the entry dependent of the actual iterator position.
//	 * return The entries value.
//	 */
//	pointer operator->() const
//	{
//		assert ("The SmartIterator isn't initilized!" && jIterator != NULL);
//		return &(operator*());
//	}

	/**
	 * The ++it prefix operator shifts the iterator to the next entry and returns it
	 * then.
	 * @return Iterator to the new position.
	 */
	SmartIterator& operator++()
	{
		next();
		return *this;
	}

	/**
	 * The it++ postfix operator returns the iterator first and then shifts it
	 * to the next entry.
	 * @return Iterator to the new position.
	 */
	SmartIterator operator++(int)
	{
		SmartIterator it = *this;
		next();
		return it;
	}

	/**
	 * The '==' operator checks if two iterators are directed to the same
	 * TreeNode, say to the same entry of a list. 
	 * @return True if it == op2
	 */
	bool operator==(const SmartIterator& op2) const
	{
		if (this->jIterator == op2.jIterator)
			return true;
		else
			return false;
	}

	/**
	 * The opposite of '==' operator. Checks if two iterators not directed to the
	 * same TreeNode.
	 * @return True if it != op2
	 */
	bool operator!=(const SmartIterator &op2) const
	{
		return !(*this == op2);
	}

	
//	List<T>::Iterator getListIterator() const
//	{
//		List<T>::Iterator *it = dynamic_cast<List<T>::Iterator*> (jIterator);
//		if (it)
//		{
//			return List<T>::Iterator(it->currentNode);
//		}
//		else
//			return List<T>::Iterator;
//	}
//	
//	StringList<T>::Iterator getStringListIterator() const
//	{
//		StringList<T>::Iterator *it = dynamic_cast<StringList<T>::Iterator*> (jIterator);
//		if (it)
//		{
//			return StringList<T>::Iterator(it->currentNode);
//		}
//		else
//			return StringList<T>::Iterator;
//	}
	
//	Tree<T>::Iterator getTreeIterator() const
//	{
//		Tree<T>::Iterator *it = dynamic_cast<Tree<T>::Iterator*> (jIterator);
//		if (it)
//			return Tree<T>::Iterator(it->currentNode);
//		else
//			// null
//			return Tree<T>::Iterator;
//	}
	
//	NullIterator<T> getNullIterator() const
//	{
//		return NullIterator<T>;
//	}
	
	bool toNullIterator()
	{
		if (jIterator)
			deleteIterator();
		jIterator = new NullIterator<T>;
		return true;
	}
	
private:
	void deleteIterator()
	{
		if (jIterator == NULL)
			return;
		
		jIterator->refCount--;
		if (jIterator->refCount <= 0)
			delete jIterator;
		jIterator = NULL;
	}
	
	class JIteratorPtr
	{
	public:
		JIteratorPtr(JavaStyleIterator<T> *it, int initRefCount = 0)
		:ptr(it), refCount(initRefCount)
		{
		}
		
		~JIteratorPtr()
		{
			delete ptr;
			ptr = NULL;
		}
		
	private:
		friend class SmartIterator;
		JavaStyleIterator<T> *ptr;
		int refCount;
	};
	
	JIteratorPtr *jIterator;
};

} // cont
} // base
} // vs

#endif  // VS_SMARTITERATOR_H
