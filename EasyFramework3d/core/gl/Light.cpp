#include <vs/core/gl/Light.h>
#include <iostream>

namespace vs
{
namespace core
{
namespace gl
{

int Light::lightSum = 0;

Light::Light()
{
	lightNr = lightSum;
	
	lightSum++;
	// if maximum number of lights is reached still the last one will changed
	if (lightSum > GL_MAX_LIGHTS)
	lightSum = GL_MAX_LIGHTS;

	colorAmbient = Color(0.7f, 0.7f, 0.7f, 1.0f);
	colorDiffuse = Color(0.8f, 0.8f, 0.8f, 1.0f);
	colorSpecular = Color(1.0f, 1.0f, 1.0f, 1.0f);
	
	glEnable(getGlNr());
	update();
}

Light::~Light()
{
	glDisable(getGlNr());
}

GLenum Light::getGlNr() const
{
	switch (lightNr)
	{
		case 0: return GL_LIGHT0;
		case 1: return GL_LIGHT1;
		case 2: return GL_LIGHT2;
		case 3: return GL_LIGHT3;
		case 4: return GL_LIGHT4;
		case 5: return GL_LIGHT5;
		case 6: return GL_LIGHT6;
		case 7: return GL_LIGHT7;
		default: cerr << "Warning in Light::getGlNr: lightNr not implemented!\n";
	}
	return GL_LIGHT0;
}

void Light::setAmbient(Color color)
{
	colorAmbient = color;
	glLightfv(getGlNr(), GL_AMBIENT,  color.toSmartArray().get());
}

void Light::setDiffuse(Color color)
{
	colorDiffuse = color;
	glLightfv(getGlNr(), GL_DIFFUSE,  color.toSmartArray().get());
}

void Light::setSpecular(Color color)
{
	colorSpecular = color;
	glLightfv(getGlNr(), GL_SPECULAR,  color.toSmartArray().get());
}

void Light::activate()
{
	glEnable(getGlNr());
	base::util::DefaultManaged::activate();
}

void Light::deactivate()
{
	glDisable(getGlNr());
	base::util::DefaultManaged::deactivate();
}

void Light::update(double /*deltaT*/)
{
//	GLenum nr = getGlNr();
//	
//	float *pos = this->getCoords().toArrayF();
	
	// TODO there is a flicker by light pos update
//	glLightfv(nr, GL_POSITION, pos);
//	delete pos;
}

void Light::pointHasChanged()
{
	update();
}

} // gl
} // core
} // vs
