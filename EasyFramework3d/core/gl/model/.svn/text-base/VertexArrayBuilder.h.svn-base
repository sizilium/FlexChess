/**
 * @file VertexArrayBuilder.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VERTEXARRAYBUILDER_H_
#define VERTEXARRAYBUILDER_H_

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/model/ModelVisitorInterface.h>
#include <list>
#include <vector>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

// TODO : isn't finished yet
/**
 * Builds an OpenGL Vertex Array from a ModelData object.
 * It is implemented as a ModelVisitor (@see ModelVisitorInterface).
 */
class VS_EXPORT VertexArrayBuilder : public ModelVisitorInterface
{
public:
	VertexArrayBuilder();
	virtual ~VertexArrayBuilder();

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
	
	vector<float> currentVertexArray;
	list<float> currentIndexArray;
};

} // model
} // gl
} // core
} // vs

#endif /*VERTEXARRAYBUILDER_H_*/
