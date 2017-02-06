#include <vs/cmd/gl/CmdsOpenGl.h>
#include <vs/core/gl/OpenGlSettings.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/managed/gl/OpenGlFactory.h>
#include <vs/Context.h>

namespace vs
{
namespace cmd
{
namespace gl
{
using namespace managed::gl;
using namespace managed::ph;
using namespace core::ph;
using namespace core::gl;
using namespace base::math;
using namespace base::cont;

OpenGlSettings* OpenGlSettingsCommand::settings() const
{
	if (getContext() && getContext()->isOpenGlManager())
	{
		OpenGlManager *manager = getContext()->getOpenGlManager();
		return manager->getOpenGlSettings();
	}
	else
		return NULL;
}


void CmdEnableCullFace::execute()
{
	if (settings() != NULL)
	{
		settings()->enableCullFace();
		settings()->applyToOpenGl();
	}
}
	
void CmdEnableCullFace::undo()
{
	if (settings() != NULL)
	{
		settings()->disableCullFace();
		settings()->applyToOpenGl();
	}
}

void CmdDisableCullFace::execute()
{
	if (settings() != NULL)
	{
		settings()->disableCullFace();
		settings()->applyToOpenGl();
	}
}

void CmdDisableCullFace::undo()
{
	if (settings() != NULL)
	{
		settings()->enableCullFace();
		settings()->applyToOpenGl();
	}
}


void CmdSetCullFaceFront::execute()
{
	if (settings() != NULL)
	{
		settings()->setCullFaceFront();
		settings()->applyToOpenGl();
	}
}

void CmdSetCullFaceFront::undo()
{
	if (settings() != NULL)
	{
		settings()->setCullFaceBack();
		settings()->applyToOpenGl();
	}
}

void CmdSetCullFaceBack::execute()
{
	if (settings() != NULL)
	{
		settings()->setCullFaceBack();
		settings()->applyToOpenGl();
	}
}

void CmdSetCullFaceBack::undo()
{
	if (settings() != NULL)
	{
		settings()->setCullFaceFront();
		settings()->applyToOpenGl();
	}
}

void CmdEnableDepthTest::execute()
{
	if (settings() != NULL)
	{
		settings()->enableDepthTest();
		settings()->applyToOpenGl();
	}
}

void CmdEnableDepthTest::undo()
{
	if (settings() != NULL)
	{
		settings()->disableDepthTest();	
		settings()->applyToOpenGl();
	}
}

void CmdDisableDepthTest::execute()
{
	if (settings() != NULL)
	{
		settings()->disableDepthTest();
		settings()->applyToOpenGl();
	}
}

void CmdDisableDepthTest::undo()
{
	if (settings() != NULL)
	{
		settings()->enableDepthTest();
		settings()->applyToOpenGl();
	}
}

void CmdSetFrontFaceCW::execute()
{
	if (settings() != NULL)
	{
		settings()->setFrontFaceCW();
		settings()->applyToOpenGl();
	}
}

void CmdSetFrontFaceCW::undo()
{
	if (settings() != NULL)
	{
		settings()->setFrontFaceCCW();
		settings()->applyToOpenGl();
	}
}

void CmdSetFrontFaceCCW::execute()
{
	if (settings() != NULL)
	{
		settings()->setFrontFaceCCW();
		settings()->applyToOpenGl();
	}
}

void CmdSetFrontFaceCCW::undo()
{
	if (settings() != NULL)
	{
		settings()->setFrontFaceCW();
		settings()->applyToOpenGl();
	}
}

CmdSetPolygonModeFront::CmdSetPolygonModeFront(GLenum type)
{	
	this->type = type;
}

void CmdSetPolygonModeFront::execute()
{
	if (settings() != NULL)
		oldType = settings()->getPolygonModeFront();
		
	if (settings() != NULL)
	{
		settings()->setPolygonModeFront(type);
		settings()->applyToOpenGl();
	}
}

void CmdSetPolygonModeFront::undo()
{
	if (settings() != NULL)
	{
		settings()->setPolygonModeFront(oldType);
		settings()->applyToOpenGl();
	}
}

CmdSetPolygonModeBack::CmdSetPolygonModeBack(GLenum type)
{
	this->type = type;
}

void CmdSetPolygonModeBack::execute()
{
	if (settings() != NULL)
		oldType = settings()->getPolygonModeBack();
		
	if (settings() != NULL)
	{
		settings()->setPolygonModeBack(type);
		settings()->applyToOpenGl();
	}
}

void CmdSetPolygonModeBack::undo()
{
	if (settings() != NULL)
	{
		settings()->setPolygonModeBack(oldType);
		settings()->applyToOpenGl();
	}
}

CmdPointSize::CmdPointSize(float size)
{
	this->size = size;
}

void CmdPointSize::execute()
{
	if (settings() != NULL)
		oldSize = settings()->getPointSize();
		
	if (settings() != NULL)
	{
		settings()->setPointSize(size);
		settings()->applyToOpenGl();
	}
}

void CmdPointSize::undo()
{
	if (settings() != NULL)
	{
		settings()->setPointSize(oldSize);
		settings()->applyToOpenGl();
	}

}

CmdLineWidth::CmdLineWidth(float width)
{
	this->width = width;
}

void CmdLineWidth::execute()
{
	if (settings() != NULL)
		oldWidth = settings()->getLineWidth();
		
	if (settings() != NULL)
	{
		settings()->setLineWidth(width);
		settings()->applyToOpenGl();
	}
}

void CmdLineWidth::undo()
{
	if (settings() != NULL)
	{
		settings()->setLineWidth(oldWidth);
		settings()->applyToOpenGl();
	}
}

void CmdEnableLineStipple::execute()
{
	if (settings() != NULL)
	{
		settings()->setLineStipple(true);
		settings()->applyToOpenGl();
	}
}

void CmdEnableLineStipple::undo()
{
	if (settings() != NULL)
	{
		settings()->setLineStipple(false);
		settings()->applyToOpenGl();
	}
}

void CmdDisableLineStipple::execute()
{
	if (settings() != NULL)
	{
		settings()->setLineStipple(false);
		settings()->applyToOpenGl();
	}
}

void CmdDisableLineStipple::undo()
{
	if (settings() != NULL)
	{
		settings()->setLineStipple(true);
		settings()->applyToOpenGl();
	}
}

CmdLineStippleFactor::CmdLineStippleFactor(int factor)
{
	this->factor = factor;
}

void CmdLineStippleFactor::execute()
{
	if (settings() != NULL)
		oldFactor = settings()->getLineStippleFactor();
		
	if (settings() != NULL)
	{
		settings()->setLineStippleFactor(factor);
		settings()->applyToOpenGl();
	}
}

void CmdLineStippleFactor::undo()
{
	if (settings() != NULL)
	{
		settings()->setLineStippleFactor(oldFactor);
		settings()->applyToOpenGl();
	}
}

CmdLineStipplePattern::CmdLineStipplePattern(short pattern)
{
	this->pattern = pattern;
}

void CmdLineStipplePattern::execute()
{
	if (settings() != NULL)
		oldPattern = settings()->getLineStipplePattern();
		
	if (settings() != NULL)
	{
		settings()->setLineStipplePattern(pattern);
		settings()->applyToOpenGl();
	}
}

void CmdLineStipplePattern::undo()
{
	if (settings() != NULL)
	{
		settings()->setLineStipplePattern(oldPattern);
		settings()->applyToOpenGl();
	}
}

void CmdEnableColorMaterial::execute()
{
	if (settings() != NULL)
	{
		settings()->enableColorMaterial();
		settings()->applyToOpenGl();
	}
}

void CmdEnableColorMaterial::undo()
{
	if (settings() != NULL)
	{
		settings()->disableColorMaterial();
		settings()->applyToOpenGl();
	}
}

void CmdDisableColorMaterial::execute()
{
	if (settings() != NULL)
	{
		settings()->disableColorMaterial();
		settings()->applyToOpenGl();
	}
}

void CmdDisableColorMaterial::undo()
{
	if (settings() != NULL)
	{
		settings()->enableColorMaterial();
		settings()->applyToOpenGl();
	}
}

void CmdShadeModelFlat::execute()
{
	if (settings() != NULL)
	{
		settings()->setShadeModelFlat();
		settings()->applyToOpenGl();
	}
}

void CmdShadeModelFlat::undo()
{
	if (settings() != NULL)
	{
		settings()->setShadeModelSmooth();
		settings()->applyToOpenGl();
	}
}

void CmdShadeModelSmooth::execute()
{
	if (settings() != NULL)
	{
		settings()->setShadeModelSmooth();
		settings()->applyToOpenGl();
	}
}

void CmdShadeModelSmooth::undo()
{
	if (settings() != NULL)
	{
		settings()->setShadeModelFlat();
		settings()->applyToOpenGl();
	}
}

void CmdEnableTexture::execute()
{
	if (settings() != NULL)
	{
		settings()->enableTexture();
		settings()->applyToOpenGl();
	}
}

void CmdEnableTexture::undo()
{
	if (settings() != NULL)
	{
		settings()->disableTexture();
		settings()->applyToOpenGl();
	}
}

void CmdDisableTexture::execute()
{
	if (settings() != NULL)
	{
		settings()->disableTexture();
		settings()->applyToOpenGl();
	}
}

void CmdDisableTexture::undo()
{
	if (settings() != NULL)
	{
		settings()->enableTexture();
		settings()->applyToOpenGl();
	}
}

void CmdEnableLighting::execute()
{
	if (settings() != NULL)
	{
		settings()->enableLighting();
		settings()->applyToOpenGl();
	}
}

void CmdEnableLighting::undo()
{
	if (settings() != NULL)
	{
		settings()->disableLighting();
		settings()->applyToOpenGl();
	}
}

void CmdDisableLighting::execute()
{
	if (settings() != NULL)
	{
		settings()->disableLighting();
		settings()->applyToOpenGl();
	}
}

void CmdDisableLighting::undo()
{
	if (settings() != NULL)
	{
		settings()->enableLighting();
		settings()->applyToOpenGl();
	}
}

void CmdEnableNormalize::execute()
{
	if (settings() != NULL)
	{
		settings()->enableNormalize();
		settings()->applyToOpenGl();
	}
}

void CmdEnableNormalize::undo()
{
	if (settings() != NULL)
	{
		settings()->disableNormalize();
		settings()->applyToOpenGl();
	}
}

void CmdDisableNormalize::execute()
{
	if (settings() != NULL)
	{
		settings()->disableNormalize();
		settings()->applyToOpenGl();
	}
}

void CmdDisableNormalize::undo()
{
	if (settings() != NULL)
	{
		settings()->enableNormalize();
		settings()->applyToOpenGl();
	}
}

CmdSetBackgroundColor::CmdSetBackgroundColor(Color color)
{
	this->color = color;
}

void CmdSetBackgroundColor::execute()
{
	if (settings() != NULL)
		oldColor = settings()->getClearColor();
		
	if (settings() != NULL)
	{
		settings()->setClearColor(color);
		settings()->applyToOpenGl();
	}
}

void CmdSetBackgroundColor::undo()
{
	if (settings() != NULL)
	{
		settings()->setClearColor(oldColor);
		settings()->applyToOpenGl();
	}
}

CmdNewLight::CmdNewLight(const std::string &lightName)
{
	this->lightName = lightName;
}

void CmdNewLight::execute()
{
	if (getContext() && getContext()->isOpenGlManager())
	{
		OpenGlFactory factory;
		factory.createLight(lightName);
	}
}

void CmdNewLight::undo()
{
	if (getContext() && getContext()->isOpenGlManager())
	{
		getContext()->getOpenGlManager()->removeManaged(lightName);
	}
}



CmdDeleteLight::CmdDeleteLight(const std::string &lightName)
{
	this->lightName = lightName;
}

void CmdDeleteLight::execute()
{
	if (getContext() && getContext()->isOpenGlManager())
	{
		getContext()->getOpenGlManager()->removeManaged(lightName);
	}
}

void CmdDeleteLight::undo()
{
	if (getContext())
	{
		OpenGlFactory factory;
		factory.setManager(this->getContext()->getOpenGlManager());
		factory.createLight(lightName);
	}
}


CmdLightAmbient::CmdLightAmbient(Light *light, Color ambient)
{
	this->light = light;
	this->color = ambient;
	oldColor = this->light->getAmbient();
}

void CmdLightAmbient::execute()
{
	this->light->setAmbient(color);
}

void CmdLightAmbient::undo()
{
	this->light->setAmbient(oldColor);
}

CmdLightDiffuse::CmdLightDiffuse(Light *light, Color diffuse)
{
	this->light = light;
	this->color = diffuse;
	oldColor = this->light->getDiffuse();
}

void CmdLightDiffuse::execute()
{
	this->light->setDiffuse(color);
}

void CmdLightDiffuse::undo()
{
	this->light->setDiffuse(oldColor);
}

CmdLightSpecular::CmdLightSpecular(Light *light, Color specular)
{
	this->light = light;
	this->color = specular;
	oldColor = this->light->getSpecular();
}

void CmdLightSpecular::execute()
{
	this->light->setSpecular(color);
}

void CmdLightSpecular::undo()
{
	this->light->setSpecular(oldColor);
}

void CmdClearOpenGlManager::execute()
{
	if (getContext() && getContext()->isOpenGlManager())
		getContext()->getOpenGlManager()->clear();
}

void CmdClearOpenGlManager::undo()
{
	// possible?
}




} // gl
} // cmd
} // vs
