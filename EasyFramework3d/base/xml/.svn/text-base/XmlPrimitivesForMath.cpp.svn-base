#include <vs/base/xml/XmlPrimitivesForMath.h>

namespace vs
{
namespace base
{
namespace xml
{


DoubleVectorTag::DoubleVectorTag(const string &name, const DoubleVector vector3d)
{
	this->name = name;
	this->vector3d = vector3d;
}

DoubleVectorTag::DoubleVectorTag(const string &name, double x, double y, double z)
{
	this->name = name;
	vector3d = DoubleVector(x, y, z);
}

const string DoubleVectorTag::getName() const
{
	return this->name;
}

void DoubleVectorTag::cout(ofstream &os) const
{
	os 	<< "<" << name << "> "
		<< "<x>" << vector3d.x() << "</x>"
		<< "<y>" << vector3d.y() << "</y>"
		<< "<z>" << vector3d.z() << "</z>"
		<< " </" << name << ">";
}

void DoubleVectorTag::cout(ostream &os) const
{
	os 	<< "<" << name << "> "
		<< "<x>" << vector3d.x() << "</x>"
		<< "<y>" << vector3d.y() << "</y>"
		<< "<z>" << vector3d.z() << "</z>"
		<< " </" << name << ">";
}

bool getDoubleVector (const string &name, const Tree<XmlTag*> *tree, DoubleVector &vec)
{
	Tree<XmlTag*>::Const_Iterator it (tree);

	while (it.hasNext())
	{
		// search for DoubleVector's name
		if (it.current()->getName() == name)
		{
			it.goChild();
			
			// read x y z
			bool x = false;
			bool y = false;
			bool z = false;
			while (it.hasNextSibling())
			{
				if (it.current()->getName() == "x")
				{
					vec.x(atof(it.current()->getValue().c_str()));
					x = true;
				}
				else if (it.current()->getName() == "y")
				{
					vec.y(atof(it.current()->getValue().c_str()));
					y = true;
				}
				else if (it.current()->getName() == "z")
				{
					vec.z(atof(it.current()->getValue().c_str()));
					z = true;
				}
				it.nextSibling();
			}
			if (x && y && z)
				return true;
			else
				return false;
		}
		it.next();
	}
	return false;
}


} // xml
} // base
} // vs
