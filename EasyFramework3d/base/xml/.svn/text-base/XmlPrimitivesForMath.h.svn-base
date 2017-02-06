/**
 * @file XmlPrimitivesForMath.h
 * @author sizilium
 * @date 06.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLPRIMITIVES_FORMATH_H
#define XMLPRIMITIVES_FORMATH_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/xml/XmlPrimitives.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/base/cont/Tree.hpp>

namespace vs
{
namespace base
{
namespace xml
{
using namespace std;
using namespace base::cont;
using namespace base::math;

/** @class DoubleVectorTag
 * 
 */
class VS_EXPORT DoubleVectorTag : public XmlTag
{
public:
	DoubleVectorTag()	{}
	DoubleVectorTag(const string &name, const DoubleVector vector3d);
	DoubleVectorTag(const string &name, double x, double y, double z);
	
	virtual const string getName() const;
	
	virtual void cout(ofstream &os) const;
	virtual void cout(ostream &os) const;

private:
	string name;
	DoubleVector vector3d;
};

VS_EXPORT bool getDoubleVector(const string &name, const Tree<XmlTag*> *tree, DoubleVector &vec);


} // xml
} // base
} // vs

#endif  // XMLPRIMITIVES_FORMATH_H
