/**
 * @file FaceGroupData.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FACEGROUPDATA_H_
#define FACEGROUPDATA_H_

// includes
#include <vs/Build.hpp>
#include <GL/gl.h>
#include <list>
#include <vs/core/gl/model/VertexData.h>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{


/**
 * Contains the data of a faces group.
 */
struct VS_EXPORT FaceGroupData
{
	GLenum drawMode;				///< Draw mode postet to glBegin() when
                                    ///< drawing the faces. Possible Values:
                                    ///<   GL_TRIANGLES
                                    ///<   GL_TRIANGLE_STRIP
                                    ///<   GL_TRIANGLE_FAN
	unsigned int faceNum;			///< Number of Faces in this Group
	list<VertexData> verts;			///< Vertexindices, -normals and -UVs in the correct order
                                    ///< according to drawMode (since version 1.10)
    GLenum smooth;                  ///< the triangle strip/fan is drawn with GL_SMOOTH
                                    ///< or with GL_FLAT. If this group is GL_TRIANGLES
    								///< smooth is always GL_SMOOTH.

	FaceGroupData();		// default constructor
};

} // model
} // gl
} // core
} // vs
#endif /*FACEGROUPDATA_H_*/
