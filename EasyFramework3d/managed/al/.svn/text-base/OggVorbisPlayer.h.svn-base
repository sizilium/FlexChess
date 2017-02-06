/**
 * @file OggVorbisPlayer.h
 * This file provides a ogg vorbis player. Common methods are start(),
 * stop(), pause(), open() for example
 * @see SoundManager
 */

#ifndef OGGVORBIS
#define OGGVORBIS

// includes
#include <vs/Build.hpp>

#include <string>
#include <iostream>
#include <al/al.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <vs/managed/al/SoundManager.h>
#include <vs/managed/al/OggException.h>
#include <vs/base/util/Exception.h>
#include <vs/base/util/FileException.h>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/interfaces/Uncopyable.hpp>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;


/**
 * the BUFFER_SIZE defines the buffer size for decompressed ogg stream data.
 * The player uses a two-buffer technique (one for playing, one for loading).
 * If the sound hears hissing increase the bufferr!
 */
#define BUFFER_SIZE (4096 * 20)

/** @class OggVorbisPlayer
 * a *.ogg file must loading first by the open() method. Then you can play()
 * it. Important: the update() function must call regularly!
 */
class VS_EXPORT OggVorbisPlayer : 	public base::interfaces::Updateable, 
									private base::interfaces::Uncopyable
{
public:

	/**
	 * opens a *.ogg file. state() is 'AL_INITIAL' now
	 * @param path location of the ogg vorbis file
     * @exception ex::OggException, ex::FileException
	 */
	void open(string path);     // datei �ffnen
	/**
	 * close the ogg file and cleans up the buffers
     * @exception ex::OggException
	 */
	void release();
	/**
	 * print some informations to the console
	 * (artist, title, lenghts ...)
	 */
	void display();             // infos zur sound datei ausgeben
	/**
	 * play the stream. state() is 'AL_PLAYING' now
	 */
	bool play();
	/**
	 * pause the stream. state() is 'AL_PAUSE' now
     * @exception ex::OggException
	 */
	void pause();
	/**
	 * stop the stream. state() is 'AL_STOP' now
     * @exception ex::OggException
	 */
	void stop();

	/**
	 * @return true if the stream is in a playing state, else false
	 */
	bool playing();             // pr�ft ob file auch wirklich l�uft
	/**
	 * @return the state of the OggVorbisPlayer:
	 * 'AL_PLAYING' | 'AL_PAUSED' | 'AL_STOPPED' | 'AL_INITIAL'
	 */
	ALenum state() const;       // AL_PLAYING, AL_PAUSED, AL_STOPPED

	/**
	 * this function must be updated regularly in the main loop of the
	 * application. Buffers will be updated if necessary. If there is no
	 * update() call for a long time (depends on buffer size), an error
	 * occures!
	 * @return true if the stream isn't run out, else false
     * @exception ex::OggException, ex::FileException
	 */

// TODO ogg vorbis player als thread laufen lassen?

	// stream in puffer laden falls notwendig
	void update(double dummy);              

	/**
	 * value between 0 and 1 for loudness.
	 * A value of 0.5 is equivalent to an attenuation of 6 dB.
	 * (exceed limits automatical will be fixed)
	 */
	void gain(ALfloat percent); // lautst�rke einstellen
    /**
     * @return the actual gain (value 0 to 1)
     */
	ALfloat gain();
    /**
     * value between 0 and any for speed.
     * 0 is identically with a paused sound...
     * (exceed limits automatical will be fixed)
     */
	void pitch(ALfloat percent); // geschw. einstellen
    /**
     * @return the actual pitch (value 0 to any)
     */
	ALfloat pitch();

protected:

	bool stream(ALuint buffer); // von update aufgerufen. stream->puffer
	void empty();               // puffer leeren

private:

	string path;
	FILE* oggFile;
	OggVorbis_File oggStream;
	vorbis_info* vorbisInfo;
	vorbis_comment* vorbisComment;

	ALuint buffers[2];
	ALuint source;
	ALenum format;
};
} // al
} // managed
} // vs

#endif
