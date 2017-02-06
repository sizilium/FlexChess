#ifndef MANAGEDMODELBINDER_H_
#define MANAGEDMODELBINDER_H_

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/core/gl/model/ModelVisitorInterface.h>

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{
using namespace std;

/**
 * 
 */
class VS_EXPORT ManagedModelBinder : public core::gl::model::ModelVisitorInterface
{
protected:
	string modelpath;				///< model path + filename (see visit(ModelData))
	string path;					///< model path (see visit(ModelData))
	unsigned int currentModelId;	///< model id of the current object (see visit(ObjectData))
	bool currObjTextured;			///< is the current object textured? (see visit(ObjectData))
	float *verts;					///< pointer to the vertex array of the current object

	/**
	 * @see core::gl:model::ModelVisitorInterFace::visit(ModelData &model)
	 */
	void visit(core::gl::model::ModelData &model);
	/**
	 * @see core::gl:model::ModelVisitorInterFace::visit(ObjectData &object)
	 */
	void visit(core::gl::model::ObjectData &object);
	/**
	 * @see core::gl:model::ModelVisitorInterFace::visit(FaceGroupData &faceGroup)
	 */
	void visit(core::gl::model::FaceGroupData &faceGroup);
	/**
	 * @see core::gl:model::ModelVisitorInterFace::visit(VertexData &vertex)
	 */
	void visit(core::gl::model::VertexData &vertex);

public:
	void bind(core::gl::model::ModelData &model);

	// no copy constructor needed because all attributes are just temporary variables
	// only needed during binding.
};

} // model
} // gl
} // managed
} // vs

#endif /*MANAGEDMODELBINDER_H_*/
