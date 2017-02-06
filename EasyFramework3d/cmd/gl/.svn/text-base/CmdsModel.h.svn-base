/**
 * @file CmdsModel.h
 * @author sizilium
 * @date 25.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef CMDS_MODEL_H
#define CMDS_MODEL_H

// includes
#include <vs/Build.hpp>
#include <vs/cmd/Command.hpp>
#include <string>

namespace vs
{
namespace cmd
{
namespace gl
{

class VS_EXPORT CmdNewModel : public Command
{
public:
	CmdNewModel(const std::string &modelPath, const std::string &modelName);
	void execute();
	void undo();
	const std::string name() const { return "vsm model created"; }
private:
	std::string modelPath;
	std::string modelName;
};

class VS_EXPORT CmdDeleteModel : public Command
{
public:
	CmdDeleteModel(const std::string &modelName);
	void execute();
	void undo();
	const std::string name() const { return "vsm model deleted"; }
private:
	std::string modelPath;
	std::string modelName;
};

class VS_EXPORT CmdNewModelWithAnimation : public Command
{
public:
	CmdNewModelWithAnimation(const std::string &modelPath, 
	                         const std::string &modelName,
	                         const std::string &animationPath,
	                         const std::string &animationName);
	void execute();
	void undo();
	const std::string name() const { return "vsm & vsa created"; }
private:
	std::string modelPath;
	std::string modelName;
	std::string animationPath;
	std::string animationName;
};

class VS_EXPORT CmdClearModelManager : public Command
{
public:
	CmdClearModelManager() {}
	void execute();
	void undo();
	const std::string name() const { return "ModelManager cleared"; }
private:
};

} // gl
} // cmd
} // vs

#endif  // CMDS_MODEL_H
