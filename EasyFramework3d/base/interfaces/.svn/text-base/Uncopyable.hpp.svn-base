/**
 * @file Uncopyable.hpp
 * This file simply provides an Uncopyable class wich can be used by other
 * classes to prevent copies (some classes should not be copy)
 */

#ifndef UNCOPYABLE_HPP
#define UNCOPYABLE_HPP

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/**
 * @class Uncopyable
 * Use this class for defining other classes as uncopyable.
 * How it works: the constructor, copy-constructor and the '=' operator are NOT
 * public! So when you try to copy an Uncopyable class, an error occures at
 * compile time
 */
class VS_EXPORT Uncopyable
{
    protected:
    	/**
    	 * Protected because this class is only thought for sub classes.
    	 */
        Uncopyable()    {};
        
    	/**
    	 * Protected because this class is only thought for sub classes.
    	 */
        ~Uncopyable()   {};
        
    private:
    	/**
    	 * The copy constructor is private! You cannot copy this.
    	 * @code
    	 * class Test : public Uncopyable
    	 * { ... }
    	 * 
    	 * Test test;
    	 * Test test_2;
    	 * // test = test_2;		// error! cannot copy with operator=
    	 * // Test test_3 (test);	// error! cannot copy with copy constructor
    	 * // Test test_4 = test;	// error! cannot copy with copy constructor
    	 * // myFunc(test);			// error! cannot copy with copy constructor
    	 * 
    	 * @endcode
    	 */
        Uncopyable(const Uncopyable &)   {};
        
        /**
         * The operator= is private! You cannot copy this.
         */
        const void operator=(const Uncopyable &)   {};
};

} // interfaces
} // base
} // vs


#endif // UNCOPYABLE_HPP
