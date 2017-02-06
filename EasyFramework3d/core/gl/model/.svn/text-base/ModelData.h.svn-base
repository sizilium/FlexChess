/**
 * @file ModelData.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELDATA_H_
#define MODELDATA_H_

// includes
#include <vs/Build.hpp>
#include <string>
#include <list>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

class ObjectData;

/**
 * Contains the data of a model file.
 */
struct VS_EXPORT ModelData
{
	string filename;								///< model file name
	string path;									///< model file path (w/o filename)
	float formatVersion;                        	///< Version of vsm-format
	short lod;                                      ///< Level of detail of this model
	unsigned int objNum;							///< Number of Blender-objects
	list<ObjectData> objects;						///< List of (Blender)-objects

	ModelData();								// default constructor
	~ModelData();								// destructor
};

} // namespace model
} // namespace gl
} // namespace core
} // namespace vs

#endif /*MODELDATA_H_*/
