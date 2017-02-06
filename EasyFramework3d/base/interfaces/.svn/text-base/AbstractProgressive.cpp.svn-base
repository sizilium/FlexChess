#include <vs/base/interfaces/AbstractProgressive.h>

namespace vs
{

namespace base
{

namespace interfaces
{

AbstractProgressive::AbstractProgressive() :
	currentTime(0), duration(0), cyclic(false), speedFactor(1), paused(true)
{
}

AbstractProgressive::~AbstractProgressive()
{
}

void AbstractProgressive::setSpeedFactor(float speedFactor)
{
	this->speedFactor = speedFactor;
}

void AbstractProgressive::seek(double time)
{
    // toStart / toEnd would be called anyway by the code after the if clause 
	// when time is 0 / duration but the velocities wouldn't be set which 
	// could lead to playback artifacts. That's why these cases are treated here separately
    if (time == 0)
    {
        toStart();
        return;
    }
    else if (time == duration)
    {
        toEnd();
        return;
    }

	double timeDiff = time - currentTime;
	double speedFactorSave = speedFactor;
	bool pausedSave = paused;
	paused = false;
	if (timeDiff < 0)
	{
	    // jump to a backward position
		setSpeedFactor(-1);
		update(-timeDiff);
	}
	else
	{
	    // jump to a forward position
		setSpeedFactor(1);
		update(timeDiff);
	}

	setSpeedFactor(speedFactorSave);
	paused = pausedSave;
}

void AbstractProgressive::play()
{
	paused = false;
}

void AbstractProgressive::stop()
{
	paused = true;
}

double AbstractProgressive::tell() const
{
	return currentTime;
}

void AbstractProgressive::setCyclic(bool cyclic)
{
	this->cyclic = cyclic;
}

void AbstractProgressive::setDuration(double duration)
{
	this->duration = duration;
}

void AbstractProgressive::update(double deltaT)
{
	if (paused)
		return;

	currentTime += deltaT * speedFactor;

	if (speedFactor > 0)
	{
		// animation playing goes forward

		// when the end of the animation is reached stop or restart depending on cyclic
		if (currentTime >= duration)
		{
			if (cyclic)
			{
				currentTime -= duration;
			}
			else
			{
				paused = true;
				toEnd();
				return;
			}
		}
	}
	else
	{
		// animation playing goes backward

		// when the end of the animation is reached stop or restart depending on cyclic
		if (currentTime <= 0)
		{
			if (cyclic)
			{
				currentTime += duration;
			}
			else
			{
				toStart();
				paused = true;
				return;
			}
		}
	}
}

void AbstractProgressive::toStart()
{
	currentTime = 0.0;
}

void AbstractProgressive::toEnd()
{
	currentTime = duration;
}

} // interfaces

} // base

} // vs
