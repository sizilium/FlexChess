
/**
 * @file SoundSource.h
 * This file provides sound source classes for single sound sources.
 * 'SoundSource' class is designed for 3d usage.
 * @see SoundManager
 */

#ifndef SOUNDSOURCE
#define SOUNDSOURCE

// includes
#include <vs/Build.hpp>
#include <string>
#include <al/al.h>
#include <vs/core/ph/MovingPoint.h>
#include <vs/managed/al/SoundManager.h>
#include <vs/base/interfaces/Updateable.h>
#include <vs/managed/al/Sound.h>
#include <vs/managed/al/ALException.h>

namespace vs
{

namespace managed
{
namespace al
{
using namespace core::ph;
using namespace std;

/** @class SoundSource
 * SoundSource class for a single sound source in a 3d scene.
 * The wav file must be mono for the 3d effect!
 * Path to a wav file must be passed in constructor.
 * @see Sound
 */
class VS_EXPORT SoundSource : public Sound, public core::ph::MovingPoint
{
public:

    /**
     * Constructor without parameters will set the default position to {0, 0, 0}
     * and velocity to {0, 0, 0}
     */
    SoundSource();
    /**
     * @param point MovingPoint for 3d sound position and velocity
     */
    SoundSource(core::ph::MovingPoint point) ;
    virtual ~SoundSource();

    /**
     * opens and loads a wav file into buffer. Important: The sound sorce must
     * have only 1 channel (mono), else a ex::Exception will thrown
     * @param path path to a wav file.
     * @exception ex::ALException, ex::Exception
     */
    void open(string path);

    /**
     * SoundSource is a ph::MovingPoint. So update calls ph::MovingPoint::update and
     * then updates the al sound position and velocity
     */
    void update(double deltaT);

    /**
     * set the distance where there will no longer be
     * any attenuation of the source
     */
    void setMaxDistance(float maxDistance) const;
    /**
     * @return the rolloff factor
     */
    float getMaxDistance() const;

    /**
     * the rolloff rate for the source
     */
    void setRolloffFactor(float rolloffFactor) const;
    /**
     * @return the rolloff factor
     */
    float getRolloffFactor() const;

    /**
     * the distance under which the volume for the source would normally drop
     * by half (before being influenced by rolloffFactor or maxDistance)
     */
    void setReferenceDistance(float refDistance) const;
    /**
     * @return the reference distance
     */
    float getReferenceDistance() const;


private:

};

} // al
} // managed
} // vs

#endif  // SOUND
