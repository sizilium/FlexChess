/** @file Exception.h
 * file contains the root vs::ex::Exception class wich contains place information
 * where an error occures. On right usage a stacktrace can be display.
 * It derives from the
 */

#ifndef VS_EXCEPTION_H
#define VS_EXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <stack>
#include <exception>
#include <string>
#include <iostream>

namespace vs
{
namespace base
{
namespace util
{

/**
 * Base exception class with the stacktrace. The class can record the
 * place an error occured (by manually naming)
 */
class VS_EXPORT Exception : public std::exception
{
public:
    /**
     * Creates an exception.
     * @param fileOfOccuredError Specify the file of occured error.
     * @param placeOfOccuredError Specify the place of occured error.
     * @param description Write a good description about the error. If you need
     * additional informations look at the subclasses or write your own subclass!
     * For right usage name the place where the error is occured!
     * @code // Example
     * ...
     * Exception e("math.cpp", "sqrt()", "sqrt(-1) is invalid!");
     * throw e
     * ...
     * @endcode
     */
    Exception(std::string fileOfOccuredError, std::string placeOfOccuredError,
              std::string description);
    
    /**
     * This constructor is the better way to create an exception. Use the __FILE__ and
     * __LINE__ makros, so the file and place of error automatically will be added in
     * source code.
     * @param fileOfOccuredError Specify the file of occured error.
     * @param placeOfOccuredError Specify the place of occured error.
     * @param description Write a good description about the error. If you need
     * @code // Example
     * ...
     * throw Exception(__FILE__, __LINE__, "An error has occured while reading the file ...");
     * ...
     * catch (Exception e)
     * {
     *    e.addPlaceOfError(__FILE__, __LINE__);
     *    ...
     *    throw e;
     * }
     * ...
     * @endcode
     */
    Exception(std::string fileOfOccuredError, int placeOfOccuredError,
              std::string description);
    
    virtual ~Exception() throw();

    /**
     * By catching and throwing an existing Exception, you can name further
     * places (function, methods) in the stackTrace.\n
     * Use the predefined c++ macros __FILE__ and __LINE__!
     * @code // Example
     * 
     * Exception e;
     * // e.addPlaceOfError("myFile.cpp", "MyClass::myMethod");	// manually
     * e.addPlaceOfError(__FILE__, __LINE__);			// automatically!
     * ...
     * throw e;
     * ...
     *
     * @endcode
     * 
     */
    void addPlaceOfError(std::string fileOfOccuredError, std::string functionOfOccuredError);

    /**
     * Overloaded method to use the __FILE__ and __LINE__ makros.
     */
    void addPlaceOfError(std::string fileOfOccuredError, int lineOfOccuredError);


    /**
     * Shows the stacktrace (reversed -> top-down) and error description
     */
    void printStackTrace();

    /**
     * shows the error description
     */
    virtual const char* what() const throw();

protected:
    std::string errorDescription;

private:

    struct ErrPlace
    {
        std::string file;
        std::string function;
    };

    std::stack<ErrPlace> stackTrace;
};


} // util
} // base
} // vs

#endif  // VS_EXCEPTION_H
