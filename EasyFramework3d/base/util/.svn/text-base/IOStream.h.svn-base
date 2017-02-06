/**
 * @file IOStream.h
 * @author sizilium
 * @date 24.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_IO_STREAM_H
#define VS_IO_STREAM_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/MsgObservable.hpp>
//#include <iostream>
#include <sstream>

namespace vs
{
namespace base
{
namespace util
{
// predeclarations
class OStream;

/**
 * This stream operator is friend in the OStream class. The operator creates a new
 * OStreamEvent and send it to the attached observers of an OStream object. 
 * @param os An OStream object, for example the global standard out, log or err instance.
 * @param text The OStreamEvent will include this text so the observers can redirect 
 * the text to console, to strings or to files for example 
 */
VS_EXPORT OStream& operator<<(OStream &os, const std::stringstream &text);

/**
 * This overloaded stream operator is friend in the OStream class.
 * @see operator<<(OStream &os, const std::stringstream &text)
 */
VS_EXPORT OStream& operator<<(OStream &os, const std::string &text);


/** @class OStreamEvent
 * This Event will be sent by the operator<< for OStream objects. It contains a text as
 * std::string. You can't change the text, the event designed only for read.
 * The type of the event is Event::OStreamEvent.
 * @see Event 
 */
class VS_EXPORT OStreamEvent : public interfaces::Event
{
public:
	/**
	 * The text can set by the constructor.
	 * @param text The text which will sent to observers.
	 */
	OStreamEvent(std::string text);
	
	/**
	 * Getter for the text.
	 * @return A standard string.
	 */
	std::string text() const;
private:
	std::string mvarText;
};

/** @class OStream
 * A EasyFramework stream class for output. The class does output nothing itself.
 * The class only redirect the text to it's observers. The advantage is that you can
 * attach and detach any observer who knows about the output handling (Qt console
 * openGl console, dos console, logfiles, ...). Use this class for common output use
 * (without care about the "real" output).
 */
class VS_EXPORT OStream : public interfaces::MsgObservable<OStreamEvent>//, public std::basic_ostream<char>
{
public:
	//void operator() (const std::string &text);
	friend OStream& operator<<(OStream &os, const std::stringstream &text);
	friend OStream& operator<<(OStream &os, const std::string &text);
};

/** @class IStream
 * TODO? IStream for input handling
 */
class VS_EXPORT IStream : public interfaces::MsgObservable<interfaces::Event>
{
public:
	// friend ...
};

/**
 * Standard global OStream instances. The standard stream outputs cout, cerr, clog will
 * be used. But here you can attach any own observers.
 * @code // Example
 * #include <vs/base/util/IOStream.h>
 * using namespace vs::base::util;
 * 
 * ...
 * out << "hello world";			// using cout
 * log << "hello world printed";	// using clog
 * err << "no errors ;-)";			// using cerr
 * ...
 * out.attach(myLoggingObserver);
 * out << "test";		// using cout AND myLoggingObserver.notify(Event)
 * @endcode
 * 
 * You can write your own stream handler to do something with stream events.
 * @code // Example
 * class MyLoggingObserver : private MsgObserver<OStreamEvent>
 * {
 *     notify(OStreamEvent &event)
 *     {
 *         ofstream logfile;
 *         logfile.fopen("logfile.txt", ios_base::out);
 *         if (!logfile)
 *             ... error handling
 *         logfile << event.text();
 *     }
 * }; 
 * @endcode
 */
extern OStream out;
extern OStream err;
extern OStream log;


} // util
} // base
} // vs

#endif  // VS_IO_STREAM_H
