/**
 * @file Comparable.hpp
 * @author sizilium
 * @date 26.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP

// include
#include <vs/Build.hpp>
#include <vs/base/util/Identifiable.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class Comparable
 * This Interface class make it easy to create own classes with comparison propertys (>,
 * >=, <, <=).\n
 * First make a subclass from this class implement the operator>() and operator==()\n,
 * The other operators operator!=(), operator>=(), operator<() and the operator <=() will
 * be added automatically! This is the advantage of using this interfaces.
 * Google for "Barton-Nackman Trick" ;-) \n
  * @code // Subclass Example
 *
 * class MySubclass : public Comparable
 * {
 * public:
 *     MySubclass(int init)	{value = init;}
 *
 *	   int operator == (const Equality &op2) const
 *     {
 *	       return value == ((MySubclass &)op2).value;	// Note the cast!
 *	   }
 *
 *     int operator > (const Comparable &op2) const
 *	   {
 *	       return value > ((MySubclass &)op2).value;	// Note the cast!
 *     }
 *  private:
 *	    int value;
 * };
 * // Well, thats all! The other 4 operator will be added automatically!
 * // ...
 * MySubclass x1(5);
 * MySubclass x2(10);
 * // if (x1 > x2) ... (x1 >= x2) ... (x1 < x2) ... (x1 == x2) ... etc.
 * // { ... }
 *
 * @endcode
 * @see Equality
 */
class VS_EXPORT Comparable : public Identifiable
{
public:
	/**
	 * Implement this operator in subclasses.
	 * @param op2 Represents the right hand operator in an == expression (op1 > op2).\n
	 * Note: You must cast this value in subclasses!
	 * @return You must return a value >0 if op1 is greater than op2.
	 */
	virtual int operator >(const Comparable &op2) const = 0;

	/**
	 * You don't must implements this operand! There is a default implementation.
	 * @param op2 Represents the right hand operator in an >= expression (op1 >= op2).\n
	 * Note: If you want to reimplement this operator, you must cast this value in subclass!
	 * @return You must return a value >0 it the two operands are equal or op1 > op2!
	 */
	virtual int operator >=(const Comparable &op2) const
	{
		return ( *this > op2 ) || ( *this == op2 );
	}

	/**
	 * You don't must implements this operand! There is a default implementation.
	 * @param op2 Represents the right hand operator in an < expression (op1 < op2).\n
	 * Note: If you want to reimplement this operator, you must cast this value in subclass!
	 * @return You must return a value >0 it op1 is lesser than op2!
	 */
	virtual int operator <(const Comparable &op2) const
	{
		return (op2 > *this);
	}

	/**
	 * You don't must implements this operand! The default implementation is the opposite of
	 * the operator >=().
	 * @param op2 Represents the right hand operator in an <= expression (op1 <= op2).\n
	 * Note: If you want to reimplement this operator, you must cast this value in subclass!
	 * @return You must return a value >0 it the two operands are equal or op1 < op2!
	 */
	virtual int operator <=(const Comparable &op2) const
	{
		return (op2 >= *this);
	}
};

} // interfaces
} // base
} // vs

#endif	// COMPARABLE_HPP
