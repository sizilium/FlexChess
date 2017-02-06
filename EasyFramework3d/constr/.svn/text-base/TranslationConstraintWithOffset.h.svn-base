/**
 * @file TranslationConstraintWithOffset.h
 * @author sizilium
 * @date 27.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef TRANSLATION_CONSTRAINT_WITHOFFSET_H
#define TRANSLATION_CONSTRAINT_WITHOFFSET_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
// predeclarations
namespace core { namespace ph {class Point; }}

namespace constr
{

/** @class TranslationConstraintWithOffset
 * 
 */
class VS_EXPORT TranslationConstraintWithOffset : public ConstraintDecorator
{
public:
	struct Init
	{
		core::ph::Point *p1;
		const core::ph::Point *p2;
	};
	
	TranslationConstraintWithOffset(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~TranslationConstraintWithOffset();
	
	void update(double time);	

private:
	core::ph::Point *p1;
	const core::ph::Point *p2;
	base::math::DoubleVector offset;
};

} // constr
} // vs

#endif	// TRANSLATION_CONSTRAINT_WITHOFFSET_H
