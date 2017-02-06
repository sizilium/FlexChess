#include <vs/core/gl/Color.h>
#include <cassert>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{

Color::Color()
: cRed(0), cGreen(0), cBlue(0), cAlpha(1)
{}

Color::Color(float r, float g, float b, float a)
: cRed(r), cGreen(g), cBlue(b), cAlpha(a)
{}

//Color::Color(short r, short g, short b, short a)
//		: cRed(r / 255.0f), cGreen(g / 255.0f), cBlue(b / 255.0f), cAlpha(a / 255.0f)
//{}

Color::Color(float *c)
: cRed(c[0]), cGreen(c[1]), cBlue(c[2]), cAlpha(c[3])
{}

//Color::Color(short *c)
//: cRed(c[0]), cGreen(c[1]), cBlue(c[2]), cAlpha(c[3])
//{}

void Color::setRgba(float r, float g, float b, float a)
{
	cRed = r;
	cGreen = g;
	cBlue = b;
	cAlpha = a;
}

//void Color::setRgba(short r, short g, short b, short a)
//{
//	cRed = r / 255.0f;
//	cGreen = g / 255.0f;
//	cBlue = b / 255.0f;
//	cAlpha = a / 255.0f;
//}

float &Color::operator[](short i)
{
    assert(i >= 0 && i < 4);
    switch (i)
    {
    case 0:
        return cRed;
    case 1:
        return cGreen;
    case 2:
        return cBlue;
    case 3:
        return cAlpha;
    }
    
    // to prevent a warning
    return cAlpha;
}

/*
float Color::operator[](short i) const
{
    // TODO codeverdopplung mit const_cast verhindern!
	//return const_cast<const float&> (operator[](i));
}
*/

float* Color::toArray() const
{
	float *retVal = new float[4];
	retVal[0] = cRed;
	retVal[1] = cGreen;
	retVal[2] = cBlue;
	retVal[3] = cAlpha;
	return retVal;
}

std::tr1::shared_array<float> Color::toSmartArray() const
{
	float *array = toArray();
	return std::tr1::shared_array<float> (array);
}

} // gl
} // core
} // vs
