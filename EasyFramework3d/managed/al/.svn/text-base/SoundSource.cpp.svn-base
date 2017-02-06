#include <vs/managed/al/SoundSource.h>
#include <iostream>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;
using namespace base::util;
using namespace core::ph;

SoundSource::SoundSource()
{}


SoundSource::SoundSource(MovingPoint point)
		: MovingPoint(point)
{

}


SoundSource::~SoundSource()
{}


void SoundSource::open(string path)
{
    int result;

    try
    {
        load(path);
    }
    catch(ALException e)
    {
        e.addPlaceOfError("SoundSource.cpp", "SoundSource::open");
        throw e;
    }

	// prfen ob sound mehr als 1 channel hat (ansonsten 3d infos -> unerwnscht)
	ALint channels;
	alGetBufferi(buffer, AL_CHANNELS, &channels);

	if (channels != 1)
	{
		// buffer lschen lassen
		try
		{
			// TODO! reference to context is invalid
//			SoundManager *soundManager = Context::getCurrentContext()->getSoundManager();
//			soundManager->delBuffer(buffer);
		}
		catch (ALException e)
		{
			e.addPlaceOfError("Sound.cpp", "SoundSource::open");
			throw e;
		}

		// source lschen
		alDeleteSources(1, &source);

		if ((result = alGetError()) != AL_NO_ERROR)
		{
			ALException e("Sound.cpp", "SoundSource::open",
						  "could not delete Source (want to delete Source because wav isn't mono",
						  result, AL_ERROR);
			throw e;
		}

		throw Exception("Sound.cpp", "SoundSources::open",
						"only 1 channel are tolerated by the SourceSource Class");
	}

    // spezielle sound SOURCE default einstellungen setzen
	alSourcef (source, AL_ROLLOFF_FACTOR, 0.5);
	alSourcef (source, AL_REFERENCE_DISTANCE, 50);
	alSourcef (source, AL_MAX_DISTANCE, 100);
	alSourcef (source, AL_PITCH, 1.0f );
	alSourcef (source, AL_GAIN, 1.0f );

	ALfloat sourcePos[] =
		{
			1000.0f, 0.0f, 0.0f
		};
	ALfloat sourceVel[] =
		{
			0.0f, 0.0f, 0.0f
		};
	alSourcefv(source, AL_POSITION, sourcePos);
	alSourcefv(source, AL_VELOCITY, sourceVel);

	if ((result = alGetError()) != AL_NO_ERROR)
	{
		throw ALException ("Sound.cpp", "Sound::open",
						   "Could not setup source", result, AL_ERROR);
	}

}


void SoundSource::update(double deltaT)
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

    // openAL source position und geschw. sezten
    alSourcefv(source, AL_VELOCITY, vel);
    alSourcefv(source, AL_POSITION, pos);
}


void SoundSource::setMaxDistance(float maxDistance) const
{
    alSourcef(source, AL_MAX_DISTANCE, maxDistance);
}

float SoundSource::getMaxDistance() const
{
    ALfloat retval;
    alGetSourcef(source, AL_MAX_DISTANCE, &retval);
    return static_cast<float> (retval);
}


void SoundSource::setRolloffFactor(float rolloffFactor) const
{
    alSourcef(source, AL_ROLLOFF_FACTOR, rolloffFactor);
}

float SoundSource::getRolloffFactor() const
{
    ALfloat retval;
    alGetSourcef(source, AL_ROLLOFF_FACTOR, &retval);
    return static_cast<float> (retval);
}

void SoundSource::setReferenceDistance(float refDistance) const
{
    alSourcef(source, AL_REFERENCE_DISTANCE, refDistance);
}

float SoundSource::getReferenceDistance() const
{
    ALfloat retval;
    alGetSourcef(source, AL_REFERENCE_DISTANCE, &retval);
    return static_cast<float> (retval);
}


} // al
} // managed
} // vs
