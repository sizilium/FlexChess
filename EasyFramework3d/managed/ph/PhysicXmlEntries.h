/**
 * @file PhysicXmlEntries.h
 * @author sizilium
 * @date 06.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PHYSICXML_ENTRIES_H
#define PHYSICXML_ENTRIES_H

// includes
#include <vs/Build.hpp>
#include <vs/base/xml/AbstractXmlEntry.h>

namespace vs
{
// predeclarations
namespace core
{
namespace ph
{
class Point;
class Euler;
class OrientatedPoint;
class MovingPoint;
class MovingEuler;
class MovingOrientatedPoint;
class AcceleratingPoint;
class PointBody;
class RigidBody;
class AcceleratingEuler;
}
}

namespace managed
{
namespace ph
{

using namespace base::interfaces;

/** @class PointXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT PointXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::Point *ptr;
public:
	PointXmlEntry() {}	// for read
	PointXmlEntry(std::string name, core::ph::Point *point);	// for write
	virtual ~PointXmlEntry() {}
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "Point"; }
};


/** @class EulerXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT EulerXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::Euler *ptr;
public:
	EulerXmlEntry() {}	// for read
	EulerXmlEntry(std::string name, core::ph::Euler *euler);	// for write
	virtual ~EulerXmlEntry() {}
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "Euler"; }
};


/** @class OrientatedPointXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT OrientatedPointXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::OrientatedPoint *ptr;
public:
	OrientatedPointXmlEntry() {}	// for read
	OrientatedPointXmlEntry(std::string name, core::ph::OrientatedPoint *orientatedPoint);	// for write
	virtual ~OrientatedPointXmlEntry() {}
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "OrientatedPoint"; }
};


/** @class MovingPointXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT MovingPointXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::MovingPoint *ptr;
public:
	MovingPointXmlEntry() {}	// for read
	MovingPointXmlEntry(std::string name, core::ph::MovingPoint *movingPoint);	// for write
	virtual ~MovingPointXmlEntry() {}
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "MovingPoint"; }
};


/** @class MovingEulerXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT MovingEulerXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::MovingEuler *ptr;
public:
	MovingEulerXmlEntry() {}	// for read
	MovingEulerXmlEntry(std::string name, core::ph::MovingEuler *movingEuler);	// for write
	virtual ~MovingEulerXmlEntry() {}
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "MovingEuler"; }
};


/** @class MovingOrientatedPointXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT MovingOrientatedPointXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::MovingOrientatedPoint *ptr;
public:
	MovingOrientatedPointXmlEntry() {}	// for read
	MovingOrientatedPointXmlEntry(std::string name, core::ph::MovingOrientatedPoint *movingEuler);	// for write
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "MovingOrientatedPoint"; }
};


/** @class AcceleratingPointXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT AcceleratingPointXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::AcceleratingPoint *ptr;
public:
	AcceleratingPointXmlEntry() {}	// for read
	AcceleratingPointXmlEntry(std::string name, core::ph::AcceleratingPoint *accp);	// for write
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "AcceleratingPoint"; }
};


/** @class AcceleratingEulerXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT AcceleratingEulerXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::AcceleratingEuler *ptr;
public:
	AcceleratingEulerXmlEntry() {}	// for read
	AcceleratingEulerXmlEntry(std::string name, core::ph::AcceleratingEuler *acce);	// for write
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "AcceleratingEuler"; }
};


/** @class PointBodyXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT PointBodyXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::PointBody *ptr;
public:
	PointBodyXmlEntry() {}	// for read
	PointBodyXmlEntry(std::string name, core::ph::PointBody *pointBody);	// for write
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "PointBody"; }
};


/** @class RigidBodyXmlEntry
 * 
 * @throw XmlException
 */
class VS_EXPORT RigidBodyXmlEntry : public base::xml::AbstractXmlEntry
{
	core::ph::RigidBody *ptr;
public:
	RigidBodyXmlEntry() {}	// for read
	RigidBodyXmlEntry(std::string name, core::ph::RigidBody *rigidBody);	// for write
	
	virtual AbstractManaged* read(const base::cont::Tree<base::xml::XmlTag*> *input);
	virtual void write(base::cont::Tree<base::xml::XmlTag*> *fillTreeToWrite);

	virtual std::string getNamespace() const	{ return "ph"; }
	virtual std::string getTypeName() const		{ return "RigidBody"; }
};

} // ph
} // managed
} // vs

#endif  // PHYSICXML_ENTRIES_H
