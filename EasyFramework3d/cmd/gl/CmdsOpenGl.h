/**
 * @file CmdsOpenGl.h
 * @author sizilium
 * @date 25.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef CMDS_OPENGL_H
#define CMDS_OPENGL_H

// includes
#include <vs/Build.hpp>
#include <GL/gl.h>
#include <vs/cmd/Command.hpp>
#include <vs/core/gl/Color.h>
#include <vs/core/gl/Light.h>
#include <string>

namespace vs
{
// predeclaration
namespace core {namespace gl {class OpenGlSettings; }}

namespace cmd
{
namespace gl
{

class VS_EXPORT OpenGlSettingsCommand : public Command
{
public:
	virtual ~OpenGlSettingsCommand() {}
	const std::string name() const		{ return "OpenGl settings changed"; }
protected:
	core::gl::OpenGlSettings* settings() const;
};

class VS_EXPORT CmdEnableCullFace : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableCullFace() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableCullFace : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableCullFace() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetCullFaceFront : public OpenGlSettingsCommand
{
public:
	virtual ~CmdSetCullFaceFront() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetCullFaceBack : public OpenGlSettingsCommand
{
public:
	virtual ~CmdSetCullFaceBack() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdEnableDepthTest : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableDepthTest() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableDepthTest : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableDepthTest() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetFrontFaceCW : public OpenGlSettingsCommand
{
public:
	virtual ~CmdSetFrontFaceCW() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetFrontFaceCCW : public OpenGlSettingsCommand
{
public:
	virtual ~CmdSetFrontFaceCCW() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetPolygonModeFront : public OpenGlSettingsCommand
{
public:
	CmdSetPolygonModeFront(GLenum type);
	virtual ~CmdSetPolygonModeFront()  {}
	void execute();
	void undo();
private:
	GLenum type;
	GLenum oldType;
};

class VS_EXPORT CmdSetPolygonModeBack : public OpenGlSettingsCommand
{
public:
	CmdSetPolygonModeBack(GLenum type);
	virtual ~CmdSetPolygonModeBack() {}
	void execute();
	void undo();
private:
	GLenum type;
	GLenum oldType;
};

class VS_EXPORT CmdPointSize : public OpenGlSettingsCommand
{
public:
	CmdPointSize(float size);
	virtual ~CmdPointSize() {}
	void execute();
	void undo();
private:
	float size;
	float oldSize;
};

class VS_EXPORT CmdLineWidth : public OpenGlSettingsCommand
{
public:
	CmdLineWidth(float width);
	virtual ~CmdLineWidth() {}
	void execute();
	void undo();
private:
	float width;
	float oldWidth;
};

class VS_EXPORT CmdEnableLineStipple : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableLineStipple() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableLineStipple : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableLineStipple() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdLineStippleFactor : public OpenGlSettingsCommand
{
public:
	CmdLineStippleFactor(int factor);
	virtual ~CmdLineStippleFactor() {}
	void execute();
	void undo();
private:
	int factor;
	int oldFactor;
};

class VS_EXPORT CmdLineStipplePattern : public OpenGlSettingsCommand
{
public:
	CmdLineStipplePattern(short pattern);
	virtual ~CmdLineStipplePattern() {}
	void execute();
	void undo();
private:
	short pattern;
	short oldPattern;
};

class VS_EXPORT CmdEnableColorMaterial : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableColorMaterial() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableColorMaterial : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableColorMaterial() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdShadeModelFlat : public OpenGlSettingsCommand
{
public:
	virtual ~CmdShadeModelFlat() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdShadeModelSmooth : public OpenGlSettingsCommand
{
public:
	virtual ~CmdShadeModelSmooth() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdEnableTexture : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableTexture() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableTexture : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableTexture() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdEnableLighting : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableLighting() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableLighting : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableLighting() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdEnableNormalize : public OpenGlSettingsCommand
{
public:
	virtual ~CmdEnableNormalize() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdDisableNormalize : public OpenGlSettingsCommand
{
public:
	virtual ~CmdDisableNormalize() {}
	void execute();
	void undo();
};

class VS_EXPORT CmdSetBackgroundColor : public OpenGlSettingsCommand
{
public:
	CmdSetBackgroundColor(core::gl::Color color);
	virtual ~CmdSetBackgroundColor() {}
	void execute();
	void undo();
private:
	core::gl::Color color;
	core::gl::Color oldColor;
};

class VS_EXPORT CmdNewLight : public Command
{
public:
	CmdNewLight(const std::string &lightName);
	virtual ~CmdNewLight() {}
	void execute();
	void undo();
	const std::string name() const	{ return "light created"; }
private:
	std::string lightName;
};

class VS_EXPORT CmdDeleteLight : public Command
{
public:
	CmdDeleteLight(const std::string &lightName);
	virtual ~CmdDeleteLight() {}
	void execute();
	void undo();
	const std::string name() const	{ return "light deleted"; }
private:
	std::string lightName;
};


class VS_EXPORT CmdLightAmbient : public Command
{
public:
	CmdLightAmbient(core::gl::Light *light, core::gl::Color ambient);
	virtual ~CmdLightAmbient() {}
	void execute();
	void undo();
	const std::string name() const	{ return "light ambient changed"; }
private:
	core::gl::Light *light;
	core::gl::Color color;
	core::gl::Color oldColor;
};

class VS_EXPORT CmdLightDiffuse : public Command
{
public:
	CmdLightDiffuse(core::gl::Light *light, core::gl::Color diffuse);
	virtual ~CmdLightDiffuse() {}
	void execute();
	void undo();
	const std::string name() const	{ return "light diffuse changed"; }
private:
	core::gl::Light *light;
	core::gl::Color color;
	core::gl::Color oldColor;
};

class VS_EXPORT CmdLightSpecular : public Command
{
public:
	CmdLightSpecular(core::gl::Light *light, core::gl::Color specular);
	virtual ~CmdLightSpecular() {}
	void execute();
	void undo();
	const std::string name() const	{ return "light specular changed"; }
private:
	core::gl::Light *light;
	core::gl::Color color;
	core::gl::Color oldColor;
};

class VS_EXPORT CmdClearOpenGlManager : public Command
{
public:
	CmdClearOpenGlManager() {}
	void execute();
	void undo();
	const std::string name() const { return "OpenGlManager cleared"; }
private:
};

} // gl
} // cmd
} // vs

#endif  // CMDS_OPENGL_H
