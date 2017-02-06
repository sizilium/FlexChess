/**
 * @file AcceleratingPoint.h provides AcceleratingPoint class which simply
 * derives from MovingPoint
 */

#ifndef ACCELERATING_POINT_H
#define ACCELERATING_POINT_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/MovingPoint.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class AcceleratingPoint
 * An accelerating point without mass and rotation. Contains an accelerating vector a.
 */
class VS_EXPORT AcceleratingPoint : public MovingPoint
{
public:
    AcceleratingPoint();
    ~AcceleratingPoint();

    /** Setter for acceleration a.
     * @param setA New acceleration vector.
     */
    void setA(base::math::DoubleVector setA)	{a = setA;}
    
    /** Getter for acceleration a.
     * @return Gets the actual acceleration vector.
     */
    base::math::DoubleVector getA() const	{return a;}

    /**
     * Applies the acceleration vector. This means the velocity will in time.
     */
    virtual void update(double deltaT);
    
protected:
	base::math::DoubleVector a;
private:

};

} // ph
} // core
} // vs

#endif
