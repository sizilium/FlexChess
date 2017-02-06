/**
 * @file SoundManager.h
 * This file manages all sound buffers in a SoundManager singleton.
 * All Sounds (a alSound with position, velocity, attributes..) and there
 * buffers are automatically managed in background.
*/

#ifndef SOUNDMANAGER
#define SOUNDMANAGER
#define NS_VSAL

// includes
#include <vs/Build.hpp>
#include <string>
#include <iostream>
#include <map>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <vs/managed/al/Sound.h>
#include <vs/managed/al/ALException.h>
#include <vs/base/interfaces/AbstractManager.hpp>

namespace vs
{
namespace base {namespace interfaces {class AbstractManaged; }}

namespace managed
{
/**
 * OpenAL sound managment namespace.
 * Note: SoundManager, Sound, SoundSource, SoundListener are wrappers for the OpenAL api.
 * You can use OpenAL directly, visit www.openal.org for further informations. Don't use
 * both simultanous: OpenAL api and vs::al.
 * @see vs::managed::al::SoundManager  
 */
namespace al
{
using namespace std;

/** @class SoundManager
 * SoundManager class works in background (ever when a Sound or a SoundSource
 * was created) and manage all openAL buffers. So there are no multiple buffers.
 * Do not instantiate this class!
 */
class VS_EXPORT SoundManager : public base::interfaces::AbstractManager<SoundManager>
{
public:
    /**
    * alutInit() will call by the constructor so you never must intial the al
    * environment manually
     * @exception ALException, Exception
    */
    SoundManager();
    
    /**
     * alutExit() will call in constructor so you never must deinitial the al
     * environment manually
     */
    ~SoundManager();

    /**
     * All SoundSource's will updated, because there are moving points. The sound
     * listener will updated too, because it is an moving orientated point.\n
     * Sounds needs no update, sounds are buffered in the sound card an playing simultaneous.\n
     * Use the update method in the context for global update!
     * @param deltaT Inject the time difference in milliseconds (has no effect to sound pitch, 
     * on only sound/listener positions...)
     * @see vs::Context
     */
    void update(double deltaT);

	/**
	 * Gets all names actually stored in the manager. With the names you can get
	 * access to the managed using getManaged(name) method. Note that these methods
	 * are not optimal for performance. Use handler (pointer) to the managed instead.
	 * @param names Pass any vs container.
	 * @code // Example
	 * ...
	 * List<string> myList;
	 * myManager->getManagedNames(&myList);
	 * ...
	 * @endcode
	 */
	void getManagedNames(base::cont::JavaStyleContainer<std::string> *names) const {}
    
    base::interfaces::AbstractManaged* getManaged(const string &name) const {return NULL;}
    void removeManaged(const string &name) {}
    
	/**
	 * This method clears all managed from the manager.
	 */
	void clear() {}
    
	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "SoundManager"; }
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
private:
	
	void addManaged(base::interfaces::AbstractManaged *managed) {}
	
    /**
     * this method make a internally lookup of the path parameter and search for
     * existing buffers
     * @param path the path to a wav file is the key of the buffer
     * @return if there are no buffer with a specific path, the SoundManager will
     * generate a new buffer. Else an existing buffer will return
     * @exception ALException
     */
    ALuint getBuffer(string path);

    /**
     * deletes a buffer if no other Sound classes has a reference on it.
     * @param fd unique buffer number (likely a file descriptor)
     * @exception Exception
     */
    void delBuffer(ALuint fd);

    friend void killALData();
    friend class Sound;
    friend class SoundSource;

    map<string, ALuint> buffers;
    map<ALuint, int> refCounts;
};


/**
 * Clears all buffers and sources and terminates alut. It's a help function.
 */
VS_EXPORT void killALData();


} // al
} // managed
} // vs

#endif    // SOUNDMANAGER
