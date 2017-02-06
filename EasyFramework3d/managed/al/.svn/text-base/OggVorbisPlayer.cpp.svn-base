#include <vs/managed/al/OggVorbisPlayer.h>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;

void OggVorbisPlayer::open(string path)
{
	int result, error;

	if (!(oggFile = fopen(path.c_str(), "rb")))
	{
		OggException e( "OggVorbisPlayer.cpp", "OggVorbisPlayer::open",
					   "Could not open Ogg file", 0);
		throw e;
	}

	if ((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
	{
		fclose(oggFile);
        FileException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::open",
                        "Could not open Ogg stream.", path.c_str() );
	}

	vorbisInfo = ov_info(&oggStream, -1);
	vorbisComment = ov_comment(&oggStream, -1);

	if (vorbisInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;


	alGenBuffers(2, buffers);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
	    OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::open",
                        "Could not generate buffers!", error);
	    throw e;
	}

	alGenSources(1, &source);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
	    OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::open",
                        "Could not generate source!", error);
	    throw e;
	}

	alSourcef (source, AL_GAIN, 1.0f);
	alSourcef (source, AL_PITCH, 1.0f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f );
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f );
	alSource3f(source, AL_DIRECTION, 0.0f, 0.0f, 0.0f );
	alSourcef (source, AL_ROLLOFF_FACTOR, 0.0f );
	alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE );
	
	this->path = path;
}


void OggVorbisPlayer::release()
{
    int error;
	alSourceStop(source);
	empty();
	alDeleteSources(1, &source);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
	    OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::release",
                        "Could not delete source!", error);
	    throw e;
	}

	alDeleteBuffers(2, buffers);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
	    OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::release",
                        "Could not delete buffers!", error);
	    throw e;
	}

	ov_clear(&oggStream);
}


void OggVorbisPlayer::display()
{
	cout
	<< "version         " << vorbisInfo->version << "\n"
	<< "channels        " << vorbisInfo->channels << "\n"
	<< "rate (hz)       " << vorbisInfo->rate << "\n"
	<< "bitrate upper   " << vorbisInfo->bitrate_upper << "\n"
	<< "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
	<< "bitrate lower   " << vorbisInfo->bitrate_lower << "\n"
	<< "bitrate window  " << vorbisInfo->bitrate_window << "\n"
	<< "\n"
	<< "vendor " << vorbisComment->vendor << "\n";

	for (int i = 0; i < vorbisComment->comments; i++)
		cout << "   " << vorbisComment->user_comments[i] << "\n";

	cout << endl;
}


bool OggVorbisPlayer::play()
{
	if (state() == AL_PLAYING)
		return true;

	if (!stream(buffers[0]))
		return false;

	if (!stream(buffers[1]))
		return false;

	alSourceQueueBuffers(source, 2, buffers);

	alSourcePlay(source);

	return true;
}


void OggVorbisPlayer::pause()
{
	alSourceStop(source);

	int processed, error;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

	while (processed--)
	{
		ALuint buffer;
		alSourceUnqueueBuffers(source, 1, &buffer);

        error = alGetError();
        if(error != AL_NO_ERROR)
        {
            OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::pause",
                            "Could not unqueue al buffers!", error);
            throw e;
        }
	}
}


void OggVorbisPlayer::stop()
{
	alSourceStop(source);

	int processed;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

	while (processed--)
	{
		ALuint buffer;
		alSourceUnqueueBuffers(source, 1, &buffer);

        int error = alGetError();
        if(error != AL_NO_ERROR)
        {
            OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::stop",
                            "Could not unqueue al buffers!", error);
            throw e;
        }
	}

	ov_pcm_seek(&oggStream, 0);
}


bool OggVorbisPlayer::playing()
{
	if (state() == AL_PLAYING)
		return true;

	return false;
}


ALenum OggVorbisPlayer::state() const
{
	ALenum stat;

	alGetSourcei(source, AL_SOURCE_STATE, &stat);

	return stat;
}


void OggVorbisPlayer::update(double dummy)
{
	int processed, error;
	bool active = true;

	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

	while (processed--)
	{
		ALuint buffer;

		alSourceUnqueueBuffers(source, 1, &buffer);

        error = alGetError();
        if(error != AL_NO_ERROR)
        {
            OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::update",
                            "Could not unqueue al buffers!", error);
            throw e;
        }

        try
        {
		active = stream(buffer);
        }
        catch(FileException e)
        {
            e.addPlaceOfError("OggVorbis.cpp", "OggVorbisPlayer::update");
            throw e;
        }
        catch(OggException e)
        {
            e.addPlaceOfError("OggVorbis.cpp", "OggVorbisPlayer::update");
        }

		alSourceQueueBuffers(source, 1, &buffer);

        error = alGetError();
        if(error != AL_NO_ERROR)
        {
            OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::update",
                            "Could not queue al buffers!", error);
            throw e;
        }
	}

}


ALfloat OggVorbisPlayer::gain()
{
	ALfloat retval;
	alGetSourcef(source, AL_GAIN, &retval);
	return retval;
}


void OggVorbisPlayer::gain(ALfloat percent)
{
	ALfloat maxGain, minGain;

	alGetSourcef(source, AL_MAX_GAIN, &maxGain);
	alGetSourcef(source, AL_MIN_GAIN, &minGain);

	if (percent > maxGain)
		percent = maxGain;
	else if (percent < minGain)
		percent = minGain;

	alSourcef (source, AL_GAIN, percent);
}


ALfloat OggVorbisPlayer::pitch()
{
	ALfloat retval;
	alGetSourcef(source, AL_PITCH, &retval);
	return retval;
}


void OggVorbisPlayer::pitch(ALfloat percent)
{
	if (percent < 0)
		percent = 0;

	alSourcef (source, AL_PITCH, percent);
}


bool OggVorbisPlayer::stream(ALuint buffer)
{
	char pcm[BUFFER_SIZE];
	int size = 0;
	int section;
	int result, error;

	while (size < BUFFER_SIZE)
	{
		result = ov_read(&oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);

		if (result > 0)
			size += result;
		else
			if (result < 0)
			{
			    FileException e( "OggVorbis.cpp", "OggVorbisPlayer::stream",
                                 "Could not read ogg stream", path);
				throw e;
			}
			else
				break;
	}

	if (size == 0)
		return false;

	alBufferData(buffer, format, pcm, size, vorbisInfo->rate);

    error = alGetError();
    if(error != AL_NO_ERROR)
    {
        OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::stream",
                        "Could not buffer al stream data!", error);
        throw e;
    }

	return true;
}


void OggVorbisPlayer::empty()
{
	int queued;

	alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

	while (queued--)
	{
		ALuint buffer;

		alSourceUnqueueBuffers(source, 1, &buffer);

        int error = alGetError();
        if(error != AL_NO_ERROR)
        {
            OggException e("OggVorbisPlayer.cpp", "OggVorbisPlayer::empty",
                            "Could not unqueue al buffers!", error);
            throw e;
        }
	}
}


} // al
} // managed
} // vs
