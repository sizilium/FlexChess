/**
 * @file AbstractProgressive.h
 * @author maccesch
 * @date 30.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACTPROGRESSIVE_H_
#define ABSTRACTPROGRESSIVE_H_

// include
#include <vs/Build.hpp>
#include <vs/base/interfaces/Updateable.h>

namespace vs
{

namespace base
{

namespace interfaces
{

/**
 * Abstract base class for everything that is playable, pausable and seekable.
 * You could say everything that looks like a mp3 player: it has a button play and
 * a button pause and a progress bar.
 * An example is ObjectAnimation.
 */
class VS_EXPORT AbstractProgressive : public vs::base::interfaces::Updateable
{
public:
	AbstractProgressive();
	virtual ~AbstractProgressive();

	/**
	 * Starts playback.
	 */
	virtual void play();
	
	/**
	 * Pauses playback.
	 */
	virtual void stop();

	/**
	 * Sets the progress to the specified time.
	 * @param time Time in milliseconds.
	 */
	virtual void seek(double time);
	
	/**
	 * Sets the progress to the specified fraction.
	 * @param fraction Fraction from 0 to 1 that the progress is to be set to.
	 * For example 0 means to go to the start, 1 to the end and 0.5 to the exact middle.
	 */
	void seekFractional(double fraction)		// 0 = start, 1 = end
	{
		seek(duration*fraction);
	}
	
	/**
	 * Returns the current time of the progress.
	 * @return Current time in milliseconds.
	 */
	virtual double tell() const;
	
	/**
	 * Returns the current fractional progress.
	 * @return Current progress as fraction, i.e. 0 means the beginning,
	 * 1 means the end etc.
	 */
	double tellFractional() const
	{
		return tell() / duration;
	}

	/**
	 * Sets the animation to cyclic, i.e. when it is playing and the end is reached
	 * it automatically starts over.
	 * @param cyclic The new cyclic state to be set.
	 */
	virtual void setCyclic(bool cyclic);
	
	/**
	 * Tells if the animation is cylcic.
	 * @return True if the animation is cyclic.
	 */
	bool isCyclic() const
	{
		return cyclic;
	}

	/**
	 * Tells if the animation is paused.
	 * @return True if the animaiton is paused, false if it is playing
	 */
	bool isPaused() const
	{
		return paused;
	}

	/**
	 * Sets the speed factor of the animation.
	 * @param speedFactor 1 means normal playback, 2 means twice as fast as normal,
	 * 0.5 half. You can also set negative values. -1 means backwards in normal speed
	 * for example.
	 */
	virtual void setSpeedFactor(float speedFactor);
	
	/**
	 * Returns the current speed factor.
	 * @return Current speed factor.
	 */
	double getSpeedFactor() const
	{
		return speedFactor;
	}

	/**
	 * Returns the duration of the animation.
	 * @return Duration in milliseconds.
	 */
	double getDuration() const
	{
		return duration;
	}
	
	/**
	 * Sets the duration of the animation.
	 * @param duration Duration in milliseconds.
	 */
	virtual void setDuration(double duration);
	
	/**
	 * See Updateable::update()
	 */
	virtual void update(double deltaT);


protected:
	/**
	 * Sets the animation progress to the start (like seek(0)). It is called
	 * in update() and seek() when it is certain that the animation has to be set
	 * to the start.
	 */
	virtual void toStart();
	
	/**
	 * Sets the animation progress to the end (like seekFractional(1)). It is called
	 * in update() and seek() when it is certain that the animation has to be set
	 * to the start.
	 */
	virtual void toEnd();

    double currentTime; ///< current progress of the animation in milliseconds
	double duration; ///< duration of the animation in milliseconds

	bool cyclic; ///< true, when this animation is performed repeatedly
	double speedFactor; ///< factor which is multiplied to the animation speed. A factor of 2 would double the animation speed, -1 would play the animation backwards
	bool paused; ///< true, when the animation is paused
	
};

}

}

}

#endif /*ABSTRACTPROGRESSIVE_H_*/
