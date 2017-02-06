/**
 * @file ModelVisitorInterface.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELVISITOR_H_
#define MODELVISITOR_H_

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

struct ModelData;
struct ObjectData;
struct FaceGroupData;
struct VertexData;

/**
 * Basic interface of a Visitor (as in the Visitor design pattern)
 * appliable to ModelData (@see ModelData).
 * An simple example of how to write a ModelVisitor provides @example TexNamesExtractor.cpp
 * This ModelVisitor extracts all texture names of a ModelData object and returns
 * them in a std::set<string>.
 */
class VS_EXPORT ModelVisitorInterface
{
public:
	virtual ~ModelVisitorInterface();

protected:
	/**
	 * Visit ModelData (@see ModelData)
	 * @param model The ModelData object to visit.
	 */
	virtual void visit(ModelData &model) = 0;
	/*
	 * Visit ObjectData (@see ObjectData)
	 * @param object The ObjectData object to visit.
	 */
	virtual void visit(ObjectData &object) = 0;
	/*
	 * Visit FaceGroupData (@see FaceGroupData)
	 * @param faceGroup The FaceGroupData object to visit.
	 */
	virtual void visit(FaceGroupData &faceGroup) = 0;
	/*
	 * Visit VertexData (@see VertexData)
	 * @param vertex The VertexData object to visit.
	 */
	virtual void visit(VertexData &vertex) = 0;
};

} // model
} // gl
} // core
} // vs

#endif /*MODELVISITOR_H_*/
