/**
 * @file ModelConstraintFactory.h
 * @author sizilium
 * @date 13.01.2008
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODEL_CONSTRAINT_FACTORY_H
#define MODEL_CONSTRAINT_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/AbstractConstraintFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
// predeclarations
namespace managed {namespace gl {namespace model {class ManagedModel; }}}

namespace constr
{

/** @class ModelConstraintFactory
 * 
 */
class VS_EXPORT ModelConstraintFactory : 	public AbstractConstraintFactory, 
											public base::xml::AbstractXmlFactory
{
public:
	ModelConstraintFactory();
	~ModelConstraintFactory();
	const std::string getName() const;
	
	/**
	 * 
	 */
	base::interfaces::AbstractConstraint* createModelMoveConstraint (
													managed::gl::model::ManagedModel *model,
													unsigned int modelId,
													base::math::DoubleVector startCoord,
													base::math::DoubleVector endCoord,
													double time,
													const std::string &name = "");	
private:

};

} // constr
} // vs

#endif  // MODEL_CONSTRAINT_FACTORY_H
