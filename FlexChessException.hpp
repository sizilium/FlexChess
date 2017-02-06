#ifndef FLEXCHESSEXCEPTION_HPP_
#define FLEXCHESSEXCEPTION_HPP_

// includes
#include <vs/base/util/Exception.h>
using namespace std;
using namespace vs::base::util;


/**
 * This exception will be thrown by reading invalid xml files or missing xml tag for example.
 * Use the what or the printStackTrace method to get the error message and further informations.
 * If you want to throw an already catched exception use the addPlaceOfError method.
 * @code // Example
 * ...
 * catch(FlexChessException &e)
 * {
 *     // e.addPlaceOfError("myFile.cpp", "MyClass::myMethod");	// manually
 *     e.addPlaceOfError(__FILE__, __LINE__);					// automatically!
 *     throw e;
 * }
 * ...
 * @endcode
 * 
 */
class FlexChessException : public Exception
{
public:
	FlexChessException(string file, int place, string description)
	:Exception(file, place, description)
	{
		
	}
	virtual ~FlexChessException() throw()
	{
		
	}
	

private:
};


#endif /*FLEXCHESSEXCEPTION_HPP_*/
