/**
 * @file TexNamesExtractor.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef TEXNAMESEXTRACTOR_H_
#define TEXNAMESEXTRACTOR_H_

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/model/ModelVisitorInterface.h>
#include <set>
#include <string>

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
 * Extracts all texture names of a ModelData object.
 * Implemented as a ModelVisitor (@see ModelVisitorInterface).
 */
class VS_EXPORT TexNamesExtractor : public ModelVisitorInterface
{
public:
	/**
	 * Extract the texture names from a ModelData object.
	 * @param model
	 * The ModelData object which the names are to be extracted from
	 * @return A set of the texture names (strings) of the ModelData object.
	 */
	set<string> extractTexNames(ModelData &model);

protected:
	/**
	 * @see ModelVisitorInterFace::visit(ModelData &model)
	 */
	void visit(ModelData &model);
	/**
	 * @see ModelVisitorInterFace::visit(ObjectData &object)
	 */
	void visit(ObjectData &object);
	/**
	 * @see ModelVisitorInterFace::visit(FaceGroupData &faceGroup)
	 */
	void visit(FaceGroupData &faceGroup);
	/**
	 * @see ModelVisitorInterFace::visit(VertexData &vertex)
	 */
	void visit(VertexData &vertex);
	
	set<string> textureNames;
};

} // model
} // gl
} // core
} // vs

#endif /*TEXNAMESEXTRACTOR_H_*/
