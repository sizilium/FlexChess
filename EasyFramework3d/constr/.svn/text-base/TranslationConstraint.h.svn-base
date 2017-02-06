/**
 * @file TranslationConstraint.h
 * @author sizilium
 * @date 27.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef TRANSLATION_CONSTRAINT_H
#define TRANSLATION_CONSTRAINT_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>

namespace vs
{
// predeclarations
namespace core { namespace ph {class Point; }}

namespace constr
{

/** @class TranslationConstraint
 * 
 */
class VS_EXPORT TranslationConstraint : public ConstraintDecorator
{
public:
	struct Init
	{
		core::ph::Point *p1;
		const core::ph::Point *p2;
	};
	
	TranslationConstraint(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~TranslationConstraint();
	
	void update(double deltaT);	

private:
	core::ph::Point *p1;
	const core::ph::Point *p2;
};

} // constr
} // vs

#endif	// TRANSLATION_CONSTRAINT_H
