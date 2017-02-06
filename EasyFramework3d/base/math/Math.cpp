#include <vs/base/math/Math.h>
#include <stdlib.h>
#include <sstream>

namespace vs
{
namespace base
{
namespace math
{

double round(double value, int precision)
{
	assert("Invalid precision for the round function!" && precision >= 0 && precision < 9);
    double v[] = {1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
    return floor(value * v[precision] + 0.5) / v[precision];
}

std::string doubleToString(double d, int numChars)
{
	assert("Error while convert double to string! Invalid number of chars." && numChars > 0);
	//string retVal;
	//char buffer[numChars-1];
	//_gcvt(d, numChars-1, buffer);
	//return retVal.append(buffer);
	
	stringstream retVal;
	retVal.precision(numChars);
	retVal << d;

	return retVal.str();
}

float toRad(float degree)
{
	return PI2 * (degree / 360);
}

float toDegree(float rad)
{
	return 360 * (PI2 / rad);
}


} // math
} // base
} // vs
