/**
 * @file Color.h
 * @author maccesch
 * @date 18.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef COLOR_H_
#define COLOR_H_

// includes
#include <vs/Build.hpp>
#include <memory>
#include <boost/shared_array.hpp>

// TODO? Remove this if the tr1 standard is implemented in c++
// makes the namespace tr1 known by using boost implementation
namespace std { namespace tr1 = ::boost; }

namespace vs
{
namespace core
{
namespace gl
{

class VS_EXPORT Color
{
public:
	Color();
	Color(float r, float g, float b, float a = 1);
	//Color(short r, short g, short b, short a = 255);
	Color(float *c);
	//Color(short *c);
	~Color() {}

	void setRgba(float r, float g, float b, float a = 1);
	//void setRgba(short r, short g, short b, short a = 255);
	
	float red() const	{ return cRed; }
	float green() const	{ return cGreen; }
	float blue() const	{ return cBlue; }
	float alpha() const	{ return cAlpha; }
	
    float &operator[](short i);
    //float operator[](short i) const;
    
    /**
     * Gets a float array of the color. Useful for OpenGl functions for example.
     * Delete is necessary!
     * @return A pointer to an array (float color[4]).
     */
    float* toArray() const;
    
    /**
     * Gets a float array of the color. Useful for OpenGl functions for example.
     * No delete of the array is necessary, because of the smart pointer.
     * @code // Example
     * Color color(1.0f, 0.3f, 0,5f, 1.0f);
     * ...
     * glMaterialfv(GL_FRONT, GL_AMBIENT, color.toSmartArray().get());
     * @endcode
     * @return A smart pointer holding a pointer to an array (float color[4]).
     */
    std::tr1::shared_array<float> toSmartArray() const;
    
protected:
	float cRed;
	float cGreen;
	float cBlue;
	float cAlpha;
};

} // gl
} // core
} // vs

#endif /*COLOR_H_*/
