/**
 * @file VertexData.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VERTEXDATA_H_
#define VERTEXDATA_H_

// include
#include <vs/Build.hpp>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

/**
 * Containes the vertex index, normal vector and UV texture coordinate
 */
struct VS_EXPORT VertexData
{
	unsigned int index;							///< Index of the vertex in ObjectData::verts
	float norm[3];								///< Normal vector of the vertex
	float u;									///< U-Texture-coordinate
	float v;									///< V-Texture-coordinate

	VertexData();								// standard constructor
	VertexData(const VertexData &rhs);		// copy constructor
	VertexData &operator=(const VertexData &rhs);
};

} // model
} // gl
} // core
} // vs

#endif /*VERTEXDATA_H_*/
