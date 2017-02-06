/**
 * @file CmdsPhysic.h
 * @author sizilium
 * @date 14.08.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef CMDS_PHYSIC_H
#define CMDS_PHYSIC_H

// includes
#include <vs/Build.hpp>
#include <vs/cmd/Command.hpp>
#include <vs/base/math/DoubleVector.h>
#include <string>

namespace vs
{
// predeclarations
namespace core {namespace ph { class Point; }}

namespace cmd
{
namespace ph
{

class VS_EXPORT CmdSetCoords : public Command
{
public:
	CmdSetCoords(core::ph::Point *point, base::math::DoubleVector coords);
	void execute();
	void undo();
	const std::string name() const		{ return "setCoords"; }
	
private:
	core::ph::Point *point;
	base::math::DoubleVector coords;
	base::math::DoubleVector oldCoords;
};

} // ph
} // cmd
} // vs

#endif  // CMDS_PHYSIC_H
