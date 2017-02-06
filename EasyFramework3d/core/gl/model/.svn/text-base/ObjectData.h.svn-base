/**
 * @file ObjectData.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef OBJECTDATA_H_
#define OBJECTDATA_H_

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

struct FaceGroupData;

/**
 * Contains the data of an model object
 * (in a vsm Model this corresponds to a Blender object).
 */
struct VS_EXPORT ObjectData
{
	string name;						///< Name of the Object (since v1.01)
	unsigned int vertNum;				///< Number of vertices
	list<string> texNames;  			///< Filename of textures if the object is textured
	list<unsigned int> stripsNum;		///< Number of Triangle Strips for every texture (since v1.10)
	list<unsigned int> fansNum;			///< Number of Triangle Fans for every texture (since v1.10)
	list<FaceGroupData> facesGroups;	///< Before v1.10:
                                        ///< The triangles of each list entry share
                                        ///< the same texture. If there aren't texs,
                                        ///< this list contains only one entry.
                                        ///< Since v1.10:
                                        ///< Triangle Strips, Triangle Fans and then Triangles
                                        ///< are stored per texture in this order in the list

	float *verts;               	///< Vertex-array
	char textured;					///< If object ist textured = '1' else '0'
	int texNum;						///< Number of textures of object
	float center[3];				///< Objects center (since v1.02)
	float rotation[3];				///< Objects rotation (since v1.10)
	float size[3];  				///< Objects size (since v1.10)
	float color[4];					///< RGBA-color of object-material

	ObjectData();							// default constructor
	ObjectData(const ObjectData &rhs);		// copy constructor
	ObjectData &operator=(const ObjectData &rhs);
	~ObjectData();								// destructor
};

} // model
} // gl
} // core
} // vs

#endif /*OBJECTDATA_H_*/
