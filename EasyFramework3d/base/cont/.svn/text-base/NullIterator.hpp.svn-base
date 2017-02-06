/**
 * @file NullIterator.hpp
 * @author sizilium
 * @date 03.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/JavaStyleIterator.hpp>

namespace vs
{
namespace base
{
namespace cont
{


/** @class NullIterator
 * This is an special iterator in java style: a null iterator wich is directed nowhere.
 * Search for Null Object Pattern for further informations.\n
 * The advantage is: More safety, less savage pointers (iterators).
 */
template<class T>
class VS_EXPORT NullIterator : public JavaStyleIterator<T>
{
public:
	/**
	 * This method ever returns false, because the null iterator is directed nowhere.
	 */
	bool hasNext() const
	{
		return false;
	}
	
	/**
	 * This method ever returns 0 and does nothing else.
	 */
	T next()
	{
		T tmp = T();
		return tmp;
	}
	
	T current() const
	{
		T tmp = T();
		return tmp;
	}
	
	/**
	 * This method do nothing! It's verty important that a null iterator do not delete
	 * some stuff!
	 */
	void remove()
	{
		// do nothing! 
		// todo: throw exception?
	}
	
};

} // cont
} // base
} // vs

#endif	// NULL_ITERATOR_H
