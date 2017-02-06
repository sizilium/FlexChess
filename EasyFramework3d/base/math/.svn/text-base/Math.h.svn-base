/**
 * @file Math.h
 * @author sizilium
 * @date 04.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MATH_HPP
#define MATH_HPP

// includes
#include <vs/Build.hpp>
#include <assert.h>
#include <math.h>
#include <sstream>

#define PI		3.141592653589
#define PI2 	6.2831853
#define E		2.71828183

namespace vs
{
namespace base
{
namespace math
{
using namespace std;

/**
 * A little help function to round double values.
 * @param value Value to round.
 * @param precision Number of decimal places.
 * @return The rounded value.
 */
VS_EXPORT double round(double value, int precision);

/**
 * A little help function to convert a value to a string.
 * @code
 * double d = 3.141;
 * double ld = 3.14159262;
 * string str = toString\<double\>(d)
 * string strl = toString\<double\>(d, 10);
 * @endcode
 * 
 * @param valueToString The value convert to std::string. Specify the type with the
 * template (\<int\>, \<double\>, \<float\> ...).
 * @param precision The precision of the convert (the value automatically will
 * round if the precision is to low).
 * @return The result string.
 */
template <class T>
VS_EXPORT std::string toString(T valueToString, int precision = 5)
{
	assert("Invalid precision for the toString function!" && precision > 0);
	std::stringstream stream;
	stream.precision(precision);
	stream << valueToString;
	return stream.str();
}

/**
 * Converts a double to a string (like function toString\<double\>). You must pass the
 * number of chars (digits + decimal point).
 * @code
 * double d = 12345.6789;
 * string str1 = doubleToString(d, 10);		// str1 = 12345.6789
 * string str2 = doubleToString(d, 14);		// str2 = 12345.6789
 * string str3 = doubleToString(d, 7);		// str3 = 12345.7
 * string str4 = doubleToString(d, 6);		// str4 = 12346
 * 
 * @endcode
 * @param d The double converts to a std::string.
 * @param numChars The number of chars the string will have. If there are not enough
 * the last digits of the double will cut.
 */
VS_EXPORT std::string doubleToString(double d, int numChars);

/**
 * Calcs radian measure do degree.
 * Tip: If you want to save performance, simple copy an paste the source.
 */
VS_EXPORT float toRad(float degree);

/**
 * Calcs degree to radian measure.
 * Tip: If you want to save performance, simple copy an paste the source.
 */
VS_EXPORT float toDegree(float rad);

} // math
} // base
} // vs

#endif // MATH_HPP
