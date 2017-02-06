#include <iostream>
#include <cmath>
#include <vs/base/util/Time.h>
#include <vs/base/math/Math.h>

#ifdef linux
#include <sys/time.h>
#endif

namespace vs
{
namespace base
{
namespace util
{
using namespace std;
using namespace base::math;

void StopWatch::start()
{
#ifdef linux
    timeval t;
    gettimeofday(&t, NULL);
    startTime = t.tv_sec * 1000 + t.tv_usec / 1000;
#else
	startTime = clock();
#endif
}


void StopWatch::stop()
{
#ifdef linux
    timeval t;
    gettimeofday(&t, NULL);
    stopTime = t.tv_sec * 1000 + t.tv_usec / 1000;
#else
	stopTime = clock();
#endif
}


double StopWatch::getTime()
{
#ifdef linux
	return stopTime - startTime;
#else
	return difftime(stopTime, startTime);
#endif
}


int StopWatch::getTimeInt()
{
	return (int) (getTime() * 1000);	// *1000 damit keine 0 entsteht
}


double StopWatch::getFrameTime()
{
    double tmp;
#ifdef linux
    timeval t;

    gettimeofday(&t, NULL);
    stopFrameTime = t.tv_sec * 1000 + t.tv_usec / 1000;

    tmp = stopFrameTime - startFrameTime;
    
    gettimeofday(&t, NULL);
    startFrameTime = t.tv_sec * 1000 + t.tv_usec / 1000;
    
#else
    stopFrameTime = clock();
    tmp = difftime(stopFrameTime, startFrameTime);
    startFrameTime = clock();
#endif
    return tmp;
}


void sleep (double milliseconds)
{
    double seconds = milliseconds * 1000;
    StopWatch timer;
    timer.start();
    do
    {
        timer.stop();
    }
    while(timer.getTime() < seconds);
}


double FaderStdFunction1::function(double x)    // linear
{
    return x;   // f(x) = x
}


double FaderStdFunction2::function(double x)    // smooth
{
    return 3*x*x - 2*x*x*x; // f(x) = 3x^2 - 2x^3
}


double FaderStdFunction3::function(double /*x*/)
{
    return 0;
}

FaderStdFunction1 stdFuncLinear;
FaderStdFunction2 stdFuncSmooth;


Fader::Fader()
{
    length = 1000;
    startValue = 0;
    endValue = 1;
    usedTimeFunction = &stdFuncLinear;
    stopWatch.start();
}


Fader::Fader(double len, float s_val, float e_val, FaderFunction &func)
{
    length = len * 1000;
    startValue = s_val;
    endValue = e_val;
    usedTimeFunction = &func;
    stopWatch.start();
}


Fader::~Fader()
{

}


void Fader::init(double len, float s_val, float e_val, FaderFunction &func)
{
    length = len * 1000;
    startValue = s_val;
    endValue = e_val;
    usedTimeFunction = &func;
    stopWatch.start();
}


void Fader::start()
{
    stopWatch.start();
}


void Fader::quickStop()
{
    length = 0;
}


bool Fader::value(double &getValue)
{
    stopWatch.stop();
    double dTime = stopWatch.getTime();

    if ( dTime <= length)
    {
        double dValue;

        // aufruf der zeitfunktion durch polymorphismus
        dValue = usedTimeFunction->function( dTime/length );

        getValue = dValue*(endValue-startValue) + startValue;
        return true;
    }
    if (getValue != endValue)
    {
        getValue = endValue;
        return true;
    }
    else
    {
        getValue = endValue;
        return false;
    }
}


bool Fader::value()
{
    stopWatch.stop();
    double dTime = stopWatch.getTime();

    if ( dTime < length)
        return true;
    else
        return false;
}


} // util
} // base
} // vs
