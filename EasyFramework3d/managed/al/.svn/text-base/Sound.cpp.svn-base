#include <vs/managed/al/Sound.h>
#include <iostream>

namespace vs
{
namespace managed
{
namespace al
{


Sound::Sound()
{
	source = 0;
}


Sound::~Sound()
{
	int result;
	alSourceStop(source);

	// buffer lschen lassen
	try
	{
		// TODO reference to context is invalid
//		SoundManager *soundManager = Context::getCurrentContext()->getSoundManager();
//		soundManager->delBuffer(buffer);
	}
	catch (ALException e)
	{
		e.addPlaceOfError("Sound.cpp", "Sound::~Sound");
		throw e;
	}

	// source lschen
	alDeleteSources(1, &source);

	if ((result = alGetError()) != AL_NO_ERROR)
	{
		ALException e("Sound.cpp", "Sound::~Sound",
					  "Could not delete source", result, AL_ERROR);
		throw e;
	}
}


void Sound::open(string path)
{
    int result;

    load(path);

	// prfen ob sound mehr als 1 channel hat (ansonsten 3d infos -> unerwnscht)
	ALint channels;
	alGetBufferi(buffer, AL_CHANNELS, &channels);

	if (channels == 1)
	{
		// buffer loeschen lassen
		try
		{
			// TODO! ...
//			SoundManager *soundManager = Context::getCurrentContext()->getSoundManager();
//			soundManager->delBuffer(buffer);
		}
		catch (ALException e)
		{
			e.addPlaceOfError("Sound.cpp", "Sound::open");
		}

		// source loeschen
		alDeleteSources(1, &source);

		if ((result = alGetError()) != AL_NO_ERROR)
		{
			ALException e("Sound.cpp", "Sound::open",
						  "could not delete Source (want to delete Source because only 1 channel)",
						  result, AL_ERROR);
			throw e;
		}

		throw Exception("Sound.cpp", "Sound::open",
						"only multi channels are tolerated by the Sound Class");
	}

}


void Sound::load(string path)
{
    ALenum result;

	// source anlegen
	alGenSources(1, &source);

	if ((result = alGetError()) != AL_NO_ERROR)
	{
		throw ALException ("Sound.cpp", "Sound::load",
						   "Could not create al source", result, AL_ERROR);
	}

	// buffer anlegen lassen
	try
	{
		// TODO! ...
//		SoundManager *soundManager = Context::getCurrentContext()->getSoundManager();
//		buffer = soundManager->getBuffer(path);
	}
	catch (ALException e)
	{
		e.addPlaceOfError("Sound.cpp", "Sound::load");
		throw e;
	}
	catch (...)
	{
		cout << "no exception catch in Sound.cpp Sound::Sound!!" << endl;
	}

	// sound einstellungen setzen (ausser position und geschw.)
	alSourcei (source, AL_BUFFER, buffer );

	if ((result = alGetError()) != AL_NO_ERROR)
	{
		throw ALException ("Sound.cpp", "Sound::load",
						   "Could not setup source", result, AL_ERROR);
	}
}


void Sound::play() const
{
	ALenum stat;
	alGetSourcei(source, AL_SOURCE_STATE, &stat);
	if (stat == AL_PLAYING)
        return;

	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::play",
						  "to play a file, you must load it first");
	alSourcePlay(source);
}


void Sound::stop() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::stop", "no file is loaded");
	alSourceStop(source);
}


void Sound::pause() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::pause", "no file is loaded");
	alSourcePause(source);
}


void Sound::gain(float percent)
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::gain", "no file is loaded");

	ALfloat maxGain, minGain;

	alGetSourcef(source, AL_MAX_GAIN, &maxGain);
	alGetSourcef(source, AL_MIN_GAIN, &minGain);

	if (percent > maxGain)
		percent = maxGain;
	else if (percent < minGain)
		percent = minGain;

	alSourcef (source, AL_GAIN, static_cast<ALfloat> (percent) );
}


ALfloat Sound::gain() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::gain", "no file is loaded");

	ALfloat retval;
	alGetSourcef(source, AL_GAIN, &retval);
	return retval;
}

void Sound::pitch(float percent)
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::pitch", "no file is loaded");

	if (percent < 0)
		percent = 0;

	alSourcef (source, AL_PITCH, static_cast<ALfloat> (percent) );
}


ALfloat Sound::pitch() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::pitch", "no file is loaded");

	ALfloat retval;
	alGetSourcef(source, AL_PITCH, &retval);
	return retval;
}


ALenum Sound::state() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::state", "no file is loaded");

	ALenum stat;

	alGetSourcei(source, AL_SOURCE_STATE, &stat);

	return stat;
}


void Sound::enableLoop() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::enableLoop", "no file is loaded");

	alSourcei (source, AL_LOOPING, AL_TRUE );
}


void Sound::disableLoop() const
{
	if (source == 0)
		throw Exception ( "Sound.cpp", "Sound::disableLoop", "no file is loaded");

	alSourcei (source, AL_LOOPING, AL_FALSE );
}


void Sound::display() const
{
	ALint channels;
	ALint freq;
	ALint bits;
	ALint size;

	alGetBufferi(buffer, AL_CHANNELS, &channels);
    alGetBufferi(buffer, AL_FREQUENCY, &freq);
    alGetBufferi(buffer, AL_BITS, &bits);
    alGetBufferi(buffer, AL_SIZE, &size);

	cout
	<< "channels        " << channels << endl
    << "frequency (hz)  " << freq << endl
    << "bit depth       " << bits << endl
    << "size (bytes)    " << size << endl
	<< endl;

	cout << endl;
}


} // al
} // managed
} // vs
