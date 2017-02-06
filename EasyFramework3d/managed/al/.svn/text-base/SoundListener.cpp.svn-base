#include <vs/managed/al/SoundListener.h>
#include <vs/core/ph/Point.h>
#include <iostream>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;
using namespace vs::core::ph;

SoundListener::SoundListener()
{

	ALfloat pos[] =
		{
			0.0f, 0.0f, 0.0f
		};
	ALfloat vel[] =
		{
			0.0f, 0.0f, 0.0f
		};
	ALfloat ori[] =
		{
			0.0, 0.0, -1.0, 0.0, 1.0, 0.0
		};

	// openAL listener position und geschw. sezten
	alListenerfv(AL_VELOCITY, vel);
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_ORIENTATION, ori);
}


SoundListener::SoundListener(MovingOrientatedPoint mop)
: MovingOrientatedPoint(mop)
{
	update(0);

	ALfloat ori[] =
		{
// TODO (Administrator#1#): lookat function benutzen (noch schreiben)

            0,0,0,
            mop.getRotation()[0],
            mop.getRotation()[1],
            mop.getRotation()[2],
		  };

	alListenerfv(AL_ORIENTATION, ori);
}


SoundListener::~SoundListener()
{}


void SoundListener::update(double deltaT)
{
	MovingPoint::update(deltaT);  // zuerst den Punkt setzen

	ALfloat pos[] = { getCoords().x(),
					  getCoords().y(),
					  getCoords().z()
					};
	ALfloat vel[] = { getV().x(),
					  getV().y(),
					  getV().z()
					};

// TODO (Administrator#1#): orientierung richtig berechnen

	ALfloat ori[] =
		{
			0.0, 0.0, -1.0, 0.0, 0.0, 1.0
		};

	// openAL listener position geschwindigkeit und orientierung sezten
	alListenerfv(AL_VELOCITY, vel);
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_ORIENTATION, ori);
}


void SoundListener::set(Point point, Point lookAt)
{
    // funktion dient als not lösung für knights projekt!

    float pos [] =
        {   point.getCoords()[0],
            point.getCoords()[1],
            point.getCoords()[2]    };
    float ori [] =
        {
            lookAt.getCoords()[0],
            lookAt.getCoords()[1],
            lookAt.getCoords()[2],
            0, 1, 0
        };

	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_ORIENTATION, ori);
}


void setDistanceModelLinear()
{
    alDistanceModel(AL_LINEAR_DISTANCE);
}

void setDistanceModelLinearClamped()
{
    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

void setDistanceModelExponent()
{
    alDistanceModel(AL_EXPONENT_DISTANCE);
}

void setDistanceModelExponentClamped()
{
    alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
}

void setDistanceModelNone()
{
    alDistanceModel(AL_NONE);
}


} // al
} // managed
} // vs
