#ifndef OBJECTANIMATION_H_
#define OBJECTANIMATION_H_

// includes
#include <vs/Build.hpp>

#include <string>
#include <fstream>
#include <list>
#include <cassert>

#include <vs/base/interfaces/Updateable.h>
#include <vs/base/util/FileException.h>
#include <vs/base/interfaces/AbstractProgressive.h>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;

class VS_EXPORT ObjectAnimation : public base::interfaces::AbstractProgressive
{

public:
	ObjectAnimation();
	virtual ~ObjectAnimation();

	void load(ifstream &animationFile, const string &filename, unsigned int fps);

	void update(double deltaT);

	void seek(double time);						// time in milliseconds

	void setSpeedFactor(float speedFactor);

	void toStart();
	void toEnd();
protected:
	
	// template method used in update()
	virtual void transformObject() = 0;

	/**
	 * Called in update() if speedFactor > 0. It does the actual channel updating work.
	 */
    void updateForward(double deltaT);
    
	/**
	 * Called in update() if speedFactor < 0. It does the actual channel updating work.
	 */
    void updateBackward(double deltaT);

	list<float> channelsValues[9]; ///< array of the 9 channels keyframe values
	list<double> channelsTimes[9]; ///< array of the 9 channels keyframe times periods to each last keyframe in milliseconds
	bool channelsEmpty[9]; ///< true when the according channel has no animation

	list<float>::iterator nextValueIts[9]; ///< pointers to the next values
	list<double>::iterator nextTimesIts[9]; ///< pointers to the next time period

	float currentValues[9]; ///< current channel values
	float currentVelocities[9]; ///< current channel velocities in 1/milliseconds
	double timesLeftToNext[9]; ///< time periods left until the next keyframe will be reached (in milliseconds)

	unsigned int channelNo; ///< number of channels for the animation
	unsigned int minChannel; ///< minimal channel that is not empty
	unsigned int maxChannel; ///< maximal channel that is not empty
};

} // gl
} // core
} // vs

#endif /*OBJECTANIMATION_H_*/
