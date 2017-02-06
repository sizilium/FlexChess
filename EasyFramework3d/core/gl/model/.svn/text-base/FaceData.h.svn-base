/**
 * @file FaceData.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FACEDATA_H_
#define FACEDATA_H_

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/model/VertexData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

/**
 * Contains the three vertices of the face.
 */
struct VS_EXPORT FaceData
{
	VertexData vertices[3];					///< The 3 vertices of the Face

	FaceData();									// default constructor
	FaceData(const FaceData &rhs);			// copy constructor
	FaceData &operator=(const FaceData &rhs);
};

} // model
} // gl
} // core
} // vs

#endif /*FACEDATA_H_*/
