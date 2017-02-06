#include <vs/base/util/IOStream.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace std;

// Standard global OStream instances (observers will attache automatically)
OStream out;
OStream err;
OStream log;


// A standard observer for c++ cout commands.
class CoutObserver : interfaces::MsgObserver<OStreamEvent>
{
public:
	CoutObserver()
	{
		out.attach(this);
	}
private:
	void notify(OStreamEvent &event)
	{
		assert ("The CoutObserver can only handle OStremEvent's !!"
		        && event.type() == interfaces::Event::OStreamEvent);
		cout << event.text() << endl; 	// using "cout"
	}
};

// A standard observer for c++ cerr commands.
class CerrObserver : interfaces::MsgObserver<OStreamEvent>
{
public:
	CerrObserver()
	{
		err.attach(this);
	}
private:
	void notify(OStreamEvent &event)
	{
		assert ("The CerrObserver can only handle OStremEvent's !!"
		        && event.type() == interfaces::Event::OStreamEvent);
		cerr << event.text() << endl; 	// using "cerr"
	}
};

// A standard observer for c++ clog commands.
class ClogObserver : interfaces::MsgObserver<OStreamEvent>
{
public:
	ClogObserver()
	{
		log.attach(this);
	}
private:
	void notify(OStreamEvent &event)
	{
		assert ("The ClogObserver can only handle OStremEvent's !!"
		        && event.type() == interfaces::Event::OStreamEvent);
		clog << event.text() << endl; 	// using "clog"
	}
};

namespace
{
// Standard Observer instances, automatically attached to the global OStream instances.
CoutObserver outObserver;
CerrObserver cerrObserver;
ClogObserver clogObserver;
}


// #################################################################################


OStreamEvent::OStreamEvent(string text)
:Event(Event::OStreamEvent)
{
	mvarText = text;
}

string OStreamEvent::text() const
{
	return mvarText;
}

// notify logic
OStream& operator<<(OStream &os, const string &text)
{
	// notify to all observers with special OStreamEvent wich includes the text
	OStreamEvent event(text);
	os.notify(event);
	return os;
}

// notify logic
OStream& operator<<(OStream &os, const stringstream &text)
{
	// notify to all observers with special OStreamEvent wich includes the text
	OStreamEvent event(text.str());
	os.notify(event);
	return os;
}


} // util
} // base
} // vs
