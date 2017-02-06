/**
 * @file Sound.h
 * This file provides sound classes for single sounds.
 * The 'Sound' class is designed for non 3d usage.
 * @see SoundManager
 */

#ifndef SOUND
#define SOUND

// includes
#include <vs/Build.hpp>
#include <vs/managed/al/SoundManager.h>
#include <vs/managed/al/ALException.h>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

namespace vs
{

namespace managed
{
namespace al
{
using namespace std;
using namespace base::util;

/** @class Sound
 * Sound class for a single sound.
 * No 3d informations, wav file should be stereo. Can used for menu interfaces
 * sounds or background music for example.
 */
class VS_EXPORT Sound
{
public:

    Sound();
    virtual ~Sound();

    /**
     * Opens and loads a wav file into buffer. Important: The sound sorce must
     * have more than 1 channel, else a ex::Exception will thrown.
     * @param path path to a wav file.
     */
    virtual void open(string path);

    /**
     * Value between 0 and 1 for loudness.
     * A value of 0.5 is equivalent to an attenuation of 6 dB.
     * (exceed limits automatical will be fixed)
     * @exception ex::Exception, first sound must be loadedd
     */
    void gain(float percent);
    
    /**
     * Getter for gain.
     * @return the actual gain (value 0 to 1)
     * @exception ex::Exception, first sound must be loadedd
     */
    ALfloat gain() const;

    /**
     * Value between 0 and any for speed.
     * 0 is identically with a paused sound...
     * (exceed limits automatical will be fixed)
     * @exception ex::Exception, first sound must be loadedd
     */
    void pitch(float percent);
    
    /**
     * Getter for pitch.
     * @return the actual pitch (value 0 to any)
     * @exception ex::Exception, first sound must be loadedd
     */
    ALfloat pitch() const;

    /**
     * Starts the sound source. state() is currently AL_PLAYING.
     * @exception ex::Exception, first sound must be loadedd
     */
    void play() const;
    
    /**
     * Pause the sound source. state() is currently AL_PAUSED.
     * @exception ex::Exception, first sound must be loadedd
     */
    void pause() const;
    
    /**
     * Stops the sound source. state() is currently AL_STOPPED.
     * @exception ex::Exception, first sound must be loadedd
     */
    void stop() const;

    /**
     * If the source is in a AL_PLAYING state, it will playing in loop.
     */
    void enableLoop() const;

    /**
     * If the source isn't in a AL_PLAYING state, it will playing only once.
     */
    void disableLoop() const;

    /**
     * Getter for al state.
     * @return the current state of sound sorce (type ALenum):
     * - AL_PLAYING 
     * - AL_PAUSED 
     * - AL_STOPPED 
     * - AL_INITIAL
     * @exception ex::Exception, first sound must be loaded
     */
    ALenum state() const;

	/**
	 * Print some informations to the console. Useful for debugging.
	 * (channels, ...)
	 */
    void display() const;

protected:
    ALuint source;
    ALuint buffer;

    void load(string path);
};


} // al
} // managed
} // vs

#endif  // SOUND
