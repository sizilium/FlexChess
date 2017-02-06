/**
 * @file XmlPrimitivesForPhysic.h
 * @author sizilium
 * @date 06.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLPRIMITIVES_FORPHYSIC_H
#define XMLPRIMITIVES_FORPHYSIC_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/xml/XmlPrimitives.h>
#include <vs/base/cont/Tree.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace core
{
namespace ph 
{
// predeclarations
class Point;
class Euler;
class OrientatedPoint;
class MovingPoint;
class MovingEuler;
class AcceleratingPoint;
class AcceleratingEuler;
class MovingOrientatedPoint;
class PointBody;
class RigidBody;

using namespace std;
using namespace base::xml;


/** @class PointTag
 * 
 */
class VS_EXPORT PointTag : virtual public XmlTag
{
	base::math::DoubleVector coords;
public:
	PointTag()	{}
	PointTag(const core::ph::Point &point);
	PointTag(double x, double y, double z);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getPointTag(const base::cont::Tree<XmlTag*> *tree, core::ph::Point &point);


/** @class EulerTag
 * 
 */
class VS_EXPORT EulerTag : virtual public XmlTag
{
	base::math::DoubleVector rotation;
public:
	EulerTag()	{}
	EulerTag(const core::ph::Euler &euler);
	EulerTag(double a, double b, double c);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getEulerTag(const base::cont::Tree<XmlTag*> *tree, core::ph::Euler &rotation);


/** @class OrientatedPointTag
 * 
 */
class VS_EXPORT OrientatedPointTag : public PointTag, public EulerTag
{
public:
	OrientatedPointTag()	{}
	OrientatedPointTag(const core::ph::OrientatedPoint &orientatedPoint);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getOrientatedPointTag(const base::cont::Tree<XmlTag*> *tree, core::ph::OrientatedPoint &orientatedPoint);


/** @class MovingPointTag
 * 
 */
class VS_EXPORT MovingPointTag : public PointTag
{
	base::math::DoubleVector velocity;
public:
	MovingPointTag()	{}
	MovingPointTag(const core::ph::MovingPoint &movingPoint);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getMovingPointTag(const base::cont::Tree<XmlTag*> *tree, core::ph::MovingPoint &movingPoint);


/** @class MovingEulerTag
 * 
 */
class VS_EXPORT MovingEulerTag : public EulerTag
{
	base::math::DoubleVector torque;
public:
	MovingEulerTag()	{}
	MovingEulerTag(const core::ph::MovingEuler &movingEuler);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getMovingEulerTag(const base::cont::Tree<XmlTag*> *tree, core::ph::MovingEuler &movingEuler);


/** @class MovingOrientatedPointTag
 * 
 */
class VS_EXPORT MovingOrientatedPointTag : public MovingPointTag, public MovingEulerTag
{
public:
	MovingOrientatedPointTag()	{}
	MovingOrientatedPointTag(const core::ph::MovingOrientatedPoint &mop);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getMovingOrientatedPointTag(const base::cont::Tree<XmlTag*> *tree, core::ph::MovingOrientatedPoint &mop);


/** @class AcceleratingPointTag
 * 
 */
class VS_EXPORT AcceleratingPointTag : public MovingPointTag
{
	base::math::DoubleVector acceleration;
public:
	AcceleratingPointTag()	{}
	AcceleratingPointTag(const core::ph::AcceleratingPoint &accelerationPoint);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getAcceleratingPointTag(const base::cont::Tree<XmlTag*> *tree, core::ph::AcceleratingPoint &accp);


/** @class AcceleratingEulerTag
 * 
 */
class VS_EXPORT AcceleratingEulerTag : public MovingEulerTag
{
	base::math::DoubleVector torqueA;
public:
	AcceleratingEulerTag()	{}
	AcceleratingEulerTag(const core::ph::AcceleratingEuler &acceleratingEuler);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getAcceleratingEulerTag(const base::cont::Tree<XmlTag*> *tree, core::ph::AcceleratingEuler &acce);


/** @class PointBodyTag
 * 
 */
class VS_EXPORT PointBodyTag : public AcceleratingPointTag
{
	double mass;
public:
	PointBodyTag()	{}
	PointBodyTag(const core::ph::PointBody &pointBody);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getPointBodyTag(const base::cont::Tree<XmlTag*> *tree, core::ph::PointBody &pointBody);


/** @class RigidBody
 * 
 */
class VS_EXPORT RigidBodyTag : public PointBodyTag, public AcceleratingEulerTag
{

public:
	RigidBodyTag()	{}
	RigidBodyTag(const core::ph::RigidBody &rigidBody);
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;
};

VS_EXPORT bool getRigidBodyTag(const base::cont::Tree<XmlTag*> *tree, core::ph::RigidBody &rigidBody);


} // ph
} // core
} // vs

#endif // XMLPRIMITIVES_FORPHYSIC_H
