/**
 * @file PointBody.h provides PointBody class, which represents a body without
 * any rotation feature
 */

#ifndef POINTBODY_H
#define POINTBODY_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/AcceleratingPoint.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class PointBody
 * body without rotation features
 */
class VS_EXPORT PointBody : public AcceleratingPoint
{
public:
	PointBody();
	~PointBody();

    /** setter for mass
     * @param setMass
     */
    void setMass(double setMass)	{mass = setMass;}
    
    /** getter for mass
     * @return
     */
    double getMass() const			{return mass;}

protected:
    double mass;
private:

};

} // ph
} // core
} // vs

#endif
