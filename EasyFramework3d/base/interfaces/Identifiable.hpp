/**
 * @file Equality.hpp
 * @author sizilium
 * @date 26.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef IDENTIFIABLE_HPP
#define IDENTIFIABLE_HPP

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class Equality
 * This Interface class make it easy to create own classes with equality propertys (==, !=).\n
 * First make a subclass from this class and implement the operator==(). The operator!=()
 * will be added automatically!\n
 * Google for "Barton-Nackman Trick" ;-)
 * @see Comparable
 */
class VS_EXPORT Equality
{
public:
	/**
	 * Implement this operator in subclasses.
	 * @param op2 Represents the right hand operator in an == expression (op1 == op2).\n
	 * Note: You must cast this value in subclasses!
	 * @return You must return a value >0 if the two operands are equal!
	 */
	virtual int operator==(const Identifiable &op2) const = 0;

	/**
	 * You don't must implements this operand! The default implementation is easily the
	 * opposite of operator==()
	 * @param op2 Represents the right hand operator in an != expression (op1 != op2).\n
	 * Note: If you want to reimplement this operator, you must cast this value in subclass!
	 * @return You must return a value >0 it the two operands are not equal!
	 */
	virtual int operator!=(const Identifiable &op2) const
	{
		return !( *this == op2 );
	}
};

} // interfaces
} // base
} // vs

#endif	// IDENTIFIABLE_HPP
