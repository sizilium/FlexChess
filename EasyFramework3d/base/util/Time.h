/**
* @file Time.h
* This file provides timer utilities.
* A StopWatch and Fader for every day use.
*/

#ifndef TIME_H
#define TIME_H

// includes
#include <vs/Build.hpp>
#include <ctime>

namespace vs
{
namespace base
{
/**
 * The util namespace provides usefull utility classes and functions.
 */
namespace util
{
using namespace std;


/**
 * Selfexplanatory StopWatch class
 */
class VS_EXPORT StopWatch
{
public:
	/**
	 * Default constructor.
	 */
	StopWatch()
	{
		startTime = clock();
		stopTime = clock();
		startFrameTime = clock();
		stopFrameTime = clock();
	}
	
	/**
	 * Starts the StopWatch.
	 */
	void start();
	
	/**
	 * Stops the StopWatch.
	 */
	void stop();

	/**
	 * Calculates the difference between the calls to start() and stop().
	 * @return time in milliseconds
	 */
	double getTime();
	
	/**
	 * Calculates the difference between the calls to start() and stop().
	 * @return time in seconds
	 */
	int getTimeInt();

	/**
	 * Calculates the time between each call of this method.
	 * @return time in milliseconds
	 */
	double getFrameTime();

private:
	clock_t startTime;		///< stores the time of the calls to start().
	clock_t stopTime;		///< stores the time of the calls to stop().

	clock_t startFrameTime;		///< at the end of getFrameTime() the current time is stored in here.
	clock_t stopFrameTime;		///< at the beginning of getFrameTime() the currrent time is stored in here.
};

/**
 * Loops until the specified time (in milliseconds) has passed.
 */
void sleep(double milliseconds);

// TODO: Move Faders out of here and replace FaderFunction by Parameterizable 
/**
 * Abstract FaderFunction class for a function interfaces.
 */
class VS_EXPORT FaderFunction
{
public:

	/**
	 * function must be implemented by user.
	 * @param x f(x)
	 * @return y = f(x)
	 */
	virtual double function(double x) = 0;
private:

};

/**
 * Default Fader function. Standard linear function
 */
class VS_EXPORT FaderStdFunction1 : public FaderFunction
{
public:
    /**
     * f(x) = x
     */
	double function(double x);
};

/**
 * Standard smooth function
 */
class VS_EXPORT FaderStdFunction2 : public FaderFunction
{
public:
    /**
     * \f$ (3x^2-2x^3) \f$
     */
	double function(double x);
};

/**
 * Standard ...
 */
class VS_EXPORT FaderStdFunction3 : public FaderFunction
{
public:
	double function(double x);
};

/**
 * global FaderStdFunction1 for linear timer function.
 * Can be used in the Fader class constructor. Of Course you can write own
 * function with the FaderFunction interfaces...
 */
extern FaderStdFunction1 stdFuncLinear;
/**
 * global FaderStdFunction2 for smooth timer function
 * Can be used in the Fader class constructor. Of Course you can write own
 * function with the FaderFunction interfaces...
 */
extern FaderStdFunction2 stdFuncSmooth;

/**
 * Fader class for time functions. Resting on a defined time function
 * the class calculates the result return value for each time
 */
class VS_EXPORT Fader
{
public:
    /**
     * defines a new fader with standard values.
     * startValue = 0, endValue = 1, lenght = 1000 ms
     * linear function
     */
	Fader();
	/**
	 * defines a new fader (default linear function)
	 * @param length time for the fader job in seconds
	 * @param setStartValue start value at start time (0)
	 * @param setEndValue end value at end time (length)
     * @param func optional parameter for a FaderFunction
	 */
	Fader(  double length, float setStartValue, float setEndValue,
            FaderFunction &func = stdFuncLinear);
	~Fader();

	/**
	 * defines/redefines the fader settings
	 * @param length time for the fader job
	 * @param setStartValue start value at start time (0)
	 * @param setEndValue end value at end time (length)
	 * @param func optional parameter for a Faderfunction (linear as default)
	 */
	void init(  double length, float setStartValue, float setEndValue,
                FaderFunction &func = stdFuncLinear);

	/**
	 * starts the fader. The 'startValue' will be returned first.
	 */
	void start();
	/**
	 * the fader stops immidately
	 */
	void quickStop();
	/**
	 * calculates the result return value on a appointed time
	 * @param getValue return the result in getValue as reference
	 * @return returns true if the function still in work, else false
	 */
	bool value(double &getValue);
	/**
	 * returns information if the fader still in work
	 * @return returns true if the function still in work, else false
	 */
	bool value();

private:
	double length;
	float startValue;
	float endValue;

	FaderFunction *usedTimeFunction;

	StopWatch stopWatch;
};


} // util
} // base
} // vs

#endif  // TIME_H
