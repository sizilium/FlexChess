/**
 * @file Variant.hpp
 * @author sizilium
 * @date 18.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_UT_VARIANT_H
#define VS_UT_VARIANT_H

// include
#include <vs/Build.hpp>
#include <string>

namespace vs
{
namespace base
{
namespace cont
{
using namespace std;

/** @class Variant
 * 
 */
class VS_EXPORT Variant
{
/*
public:

	Variant(bool val)			{ valueType = boolValue; value = new bool(val); }
	Variant(unsigned int val)	{ valueType = uIntValue; value = new unsigned int(val); }
	Variant(int val)			{ valueType = intValue; value = new int(val); }
	Variant(float val)			{ valueType = intValue; value = new float(val); }
	Variant(double val)			{ valueType = intValue; value = new double(val); }
	Variant(string val)			{ valueType = intValue; value = new string(val); }

	~Variant()
	{
		delete value;
		value = NULL;
	}
	
	bool toBool() const			
	{ 
		return dynamic_cast<bool> (*value); 
	}
	
	bool toUnsignedInt() const	
	{ 
		return dynamic_cast<unsigned int> (*value); 
	}
	
	int toInt() const			
	{ 
		return dynamic_cast<int> (*value); 
	}
	
	int toFloat() const			
	{ 
		return dynamic_cast<float> (*value); 
	}
	
	int toDouble() const		
	{ 
		return dynamic_cast<double> (*value); 
	}
	
	int toString() const		
	{ 
		return dynamic_cast<string> (*value); 
	}

	Variant::typeEnum type() const	{ return valueType; }
	
	enum typeEnum
	{
		boolValue 	= 1;
		uIntValue 	= 2;
		intValue	= 3;
		floatValue	= 4;
		doubleValue	= 5;
		stringValue = 6;
	};
	
private:
	int valueType;
	void *value;
*/
};

} // cont
} // base
} // vs

#endif  // VS_UT_VARIANT_H
