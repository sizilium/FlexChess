/**
 * @file CmdsAnimation.h
 * @author sizilium
 * @date 25.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef CMDS_ANIMATION_H
#define CMDS_ANIMATION_H

// includes
#include <vs/Build.hpp>
#include <vs/cmd/Command.hpp>
#include <string>

namespace vs
{
// predeclarations
namespace managed {namespace gl{ namespace model {class ManagedModel;}}}

namespace cmd
{
namespace gl
{

class VS_EXPORT CmdNewAnimation : public Command
{
public:
	CmdNewAnimation(const std::string &animationPath,
	                vs::managed::gl::model::ManagedModel *model,
	                const std::string &animationName);
	void execute();
	void undo();
	const std::string name() const { return "vsa animation created"; }
private:
	std::string animationPath;
	vs::managed::gl::model::ManagedModel *model;
	std::string animationName;
};

class VS_EXPORT CmdDeleteAnimation : public Command
{
public:
	CmdDeleteAnimation(const std::string &animationName);
	void execute();
	void undo();
	const std::string name() const { return "vsa animation deleted"; }
private:
	std::string animationName;
};

class VS_EXPORT CmdClearAnimationManager : public Command
{
public:
	CmdClearAnimationManager() {}
	void execute();
	void undo();
	const std::string name() const { return "AnimationManager cleared";	}
private:
};

} // gl
} // cmd
} // vs

#endif  // CMDS_ANIMATION_H
