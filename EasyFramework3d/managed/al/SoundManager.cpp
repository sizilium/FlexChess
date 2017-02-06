#include <vs/managed/al/SoundManager.h>
#include <vs/managed/al/AlException.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace managed
{
namespace al
{
using namespace base::interfaces;
using namespace base::util;

SoundManager::SoundManager()
{
	int error;

	alutInit(NULL, 0);

	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		throw ALException ( "SoundManager.cpp", "SoundManager::SoundManager",
							"Could not init alut!", error, ALUT_ERROR);
	}

	// set default listener attributes
	ALfloat listenerPos[] =
		{
			0.0, 0.0, 0.0
		};
	ALfloat listenerVel[] =
		{
			0.0, 0.0, 0.0
		};
	ALfloat listenerOri[] =
		{
			0.0, 0.0, -1.0, 0.0, 1.0, 0.0
		};

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	// set cleanup function on exit
	atexit( killALData );

	// set the default distance model (can be changed by SoundListener.h)
	alDistanceModel(AL_LINEAR_DISTANCE);
}


SoundManager::~SoundManager()
{
	map<string, ALuint>::iterator it = buffers.begin();

	while (it != buffers.end() )
	{
		alDeleteBuffers(1, &it->second );
		++it;
	}

	buffers.clear();

	alutExit();
}


void SoundManager::update(double time)
{
	
}


ALuint SoundManager::getBuffer(string path)
{
	int error;

	// falls buffer noch nicht vorhanden ist neuen buffer anlegen und laden
	if (!buffers[path])
	{
		ALuint newBuffer;
		alGenBuffers(1, &newBuffer);

		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			throw ALException ( "SoundManager.cpp", "SoundManager::getBuffer",
								"Could not generate buffer!", error, AL_ERROR);
		}

		// sound datei in buffer laden
		newBuffer = alutCreateBufferFromFile(path.c_str() );
		if (newBuffer == AL_NONE)
		{
			ALenum error;
			error = alutGetError ();

			throw ALException("SoundManager.cpp", "SoundManager::getBuffer",
							  "Could not create buffer from file: " + path +
							  "(\nis the path and filename correct? is the wav format correct?)"
							  , error, ALUT_ERROR);
		}

		return buffers[path] = newBuffer;
	}
	// falls buffer schon vorhanden war den alten buffer verwenden
	else
		return buffers[path];

}

void SoundManager::delBuffer(ALuint fd)
{
	--refCounts[fd];

	// falls buffer nicht mehr gebraucht wird, l�schen
	if (refCounts[fd] <= 0)
	{
		map<string, ALuint>::iterator it = buffers.begin();
		while (it != buffers.end())
		{
			if (it->second == fd)
				break;
			it++;
		}
		alDeleteBuffers(1, &it->second);    // buffer aus al l�schen
		buffers.erase(it);                  // buffer aus verwaltung l�schen
		refCounts.erase(fd);                // refCounter l�schen
	}

	ALenum error;

	if (error = alGetError () != AL_NO_ERROR)
	{
		throw ALException( "SoundManager.cpp", "SoundManager::delBuffer",
						   "Could not delete buffer", error, AL_ERROR);
	}

}

void SoundManager::outDebug() const
{
	
}


void killALData()
{
	// TODO (Administrator#1#): funktion �berhaupt notwendig?

}


} // al
} // managed
} // vs
