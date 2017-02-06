#include <vs/core/gl/ObjectAnimation.h>
#include <sstream>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;

ObjectAnimation::ObjectAnimation() :
	channelNo(0)
{
}

ObjectAnimation::~ObjectAnimation()
{
}

void ObjectAnimation::updateForward(double deltaT)
{
	float lastValue; // value of the just passed keyframe
	float nextValue; // value of the next keyframe
	double nextTime; // time period from the just passed to the next keyframe

	// update each channel
	for (unsigned int i = minChannel; i <= maxChannel; i++)
	{
		if (!(channelsEmpty[i]))
		{
			timesLeftToNext[i] -= deltaT * speedFactor;

			// next keyframe reached
			if (timesLeftToNext[i] < 0)
			{
				// maybe there is more than one keyframe passed (for example with
				// a high speedFactor or a large deltaT such as when seeking)
				do
				{
					if (nextTimesIts[i] == channelsTimes[i].end())
					{
						nextTimesIts[i] = channelsTimes[i].begin();
						nextValueIts[i] = channelsValues[i].begin();
					}
					lastValue = *nextValueIts[i];
					++(nextValueIts[i]);
					nextTime = *(nextTimesIts[i]);
					++(nextTimesIts[i]);

					timesLeftToNext[i] += nextTime;

				} while (timesLeftToNext[i] < 0);

				nextValue = *(nextValueIts[i]);
				currentVelocities[i] = (nextValue - lastValue) / nextTime;
				currentValues[i] = lastValue + (nextTime - timesLeftToNext[i]) * currentVelocities[i];
			}
			else
			{
				// just update the values with the velocity values
				currentValues[i] += currentVelocities[i] * deltaT * speedFactor;
			}
		}
	}
}

void ObjectAnimation::updateBackward(double deltaT)
{
	float lastValue; // value of the just passed keyframe
	float nextValue; // value of the next keyframe
	double nextTime; // time period from the just passed to the next keyframe

	// update each channel
	for (unsigned int i = minChannel; i <= maxChannel; i++)
	{
		if (!(channelsEmpty[i]))
		{
			timesLeftToNext[i] += deltaT * speedFactor;

			// next keyframe reached
			if (timesLeftToNext[i] < 0)
			{
				// maybe there is more than one keyframe passed (for example with
				// a high speedFactor or a large deltaT such as when seeking)
				do
				{
					lastValue = *nextValueIts[i];
					if (nextTimesIts[i] == channelsTimes[i].begin())
					{
						nextTimesIts[i] = channelsTimes[i].end();
						nextValueIts[i] = channelsValues[i].end();
					}
					--(nextValueIts[i]);
					--(nextTimesIts[i]);

                    nextTime = *(nextTimesIts[i]);
					timesLeftToNext[i] += nextTime;

				} while (timesLeftToNext[i] < 0);

				nextValue = *(nextValueIts[i]);

				// currentVelocities has to be negative velocity,
				// because is is multiplied with the negative speedFactor later
				currentVelocities[i] = (lastValue - nextValue) / nextTime;

				// this is + instead of - because currentVelocities is negative (see above)
				currentValues[i] = lastValue + (timesLeftToNext[i] - nextTime) * currentVelocities[i];
			}
			else
			{
				// just update the values with the velocity values
				currentValues[i] += currentVelocities[i] * deltaT * speedFactor;
			}
		}
	}
}

void ObjectAnimation::update(double deltaT)
{
	AbstractProgressive::update(deltaT);
	
	if (speedFactor > 0)
		updateForward(deltaT);
	else
		updateBackward(deltaT);
	
	transformObject();
}

void ObjectAnimation::load(ifstream &animationFile, const string &filename,
						   unsigned int framesPerSecond)
{
	unsigned int readChannel = 0;
	unsigned int keyframeNo;

	channelNo = 9;

	bool minContinuous = true; // true as long as there have been discovered empty channels only
	minChannel = 0;
	maxChannel = channelNo - 1;

	float fps = framesPerSecond / 1000.0f;

	duration = 0;
	unsigned int maxKeyFrame = 0;
	for (unsigned int channel = 0; channel < channelNo; channel++)
	{
		// TODO : try catch block around this function

		// read channel number. is its not the same as the counted one, something went wrong
		animationFile.read(reinterpret_cast<char *>(&readChannel), sizeof(unsigned int));
		if (readChannel != channel)
		{
			stringstream desc;
			desc << "The animation channel " << channel << " couldn't be read.";
			throw new base::util::FileException("ObjectAnimation.cpp", "ObjectAnimation::load", desc.str(), filename);
		}
		// read channel the number of keyframes which are saved for the current channel
		animationFile.read(reinterpret_cast<char *>(&keyframeNo), sizeof(unsigned int));

		// empty channels have only one keyframe -> no animation
		if (keyframeNo == 1)
		{
			channelsEmpty[channel] = true;
		}
		else
		{
			// calc minChannel and maxChannel
			if (minContinuous)
			{
				minChannel = channel;
				minContinuous = false;
			}
			maxChannel = channel;
			channelsEmpty[channel] = false;
		}

		// start reading the timestamps and values for every keyframe.
		// channelsValues[channel]: value1, value2, value3, ..., valueN
		// channelsTimes[channel]: time_to_keyframe2, time_to_keyframe3, ..., time_to_animation_end
		unsigned int lastFrame;
		unsigned int currentFrame;
		float currentValue;

		animationFile.read(reinterpret_cast<char *>(&currentFrame), sizeof(unsigned int));
		animationFile.read(reinterpret_cast<char *>(&currentValue), sizeof(float));

		channelsValues[channel].push_back(currentValue);

		for (unsigned int i = 1; i < keyframeNo; i++)
		{

			lastFrame = currentFrame;
			animationFile.read(reinterpret_cast<char *>(&currentFrame), sizeof(unsigned int));
			channelsTimes[channel].push_back((currentFrame - lastFrame) / fps);

			if (currentFrame > maxKeyFrame)
				maxKeyFrame = currentFrame;

			animationFile.read(reinterpret_cast<char *>(&currentValue), sizeof(float));
			channelsValues[channel].push_back(currentValue);
		}
		channelsTimes[channel].push_back((maxKeyFrame - currentFrame) / fps);

		duration = maxKeyFrame / fps;

		// initialize animation data for the current channel
		nextValueIts[channel] = channelsValues[channel].begin();
		nextTimesIts[channel] = channelsTimes[channel].begin();
		timesLeftToNext[channel] = 0.0;
		currentValues[channel] = channelsValues[channel].front();
	}
	// initialize channel independent animation data
	currentTime = 0.0;
	speedFactor = 1.0;
	paused = true;
	cyclic = false;
}

void ObjectAnimation::toStart()
{
	for (unsigned int channel = minChannel; channel <= maxChannel; channel++)
	{
		nextValueIts[channel] = channelsValues[channel].begin();
		nextTimesIts[channel] = channelsTimes[channel].begin();
		// keyframe reached. see updateFor/Backward
		timesLeftToNext[channel] = -1.0;
		currentValues[channel] = *(nextValueIts[channel]);
	}
	currentTime = 0.0;

	transformObject();
}

void ObjectAnimation::toEnd()
{
	for (unsigned int channel = minChannel; channel <= maxChannel; channel++)
	{
		nextValueIts[channel] = channelsValues[channel].end();
		nextTimesIts[channel] = channelsTimes[channel].end();

		--(nextValueIts[channel]);
		currentValues[channel] = *(nextValueIts[channel]);
		++(nextValueIts[channel]);

		// keyframe reached. see updateFor/Backward
		timesLeftToNext[channel] = -1.0;
	}
	currentTime = duration;

	transformObject();
}

void ObjectAnimation::seek(double time)
{
	AbstractProgressive::seek(time);
	transformObject();
}

void ObjectAnimation::setSpeedFactor(float speedFactor)
{
	// if the animation direction has changed there is a little more
	// work to do than just setting the speedFactor:
	// the channels next keyframes and the times left to them has to
	// be ajusted

	// play animation backward
	if (this->speedFactor > 0 && speedFactor < 0)
	{
		for (unsigned int i = minChannel; i <= maxChannel; ++i)
		{
			--(nextTimesIts[i]);
			--(nextValueIts[i]);
			timesLeftToNext[i] = *(nextTimesIts[i]) - timesLeftToNext[i];
		}
	}
	// play animation forward
	else if (this->speedFactor < 0 && speedFactor > 0)
	{
		for (unsigned int i = minChannel; i <= maxChannel; ++i)
		{
			timesLeftToNext[i] = *(nextTimesIts[i]) - timesLeftToNext[i];
			++(nextTimesIts[i]);
			++(nextValueIts[i]);
		}
	}

	this->speedFactor = speedFactor;
}

} // gl
} // core
} // vs
