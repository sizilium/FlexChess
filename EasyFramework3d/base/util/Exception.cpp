#include <vs/base/util/Exception.h>
#include <typeinfo>
#include <sstream>
#include <cctype>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <curses.h>
#endif

namespace vs
{
namespace base
{
namespace util
{
using namespace std;


Exception::Exception(string errFile, string errFunc, string desc)
{
    ErrPlace place;
    place.file = errFile;
    place.function = errFunc;

    errorDescription = desc;
    stackTrace.push (place);
}


Exception::Exception(string errFile, int errPlace, string desc)
{
	stringstream tmp;
	tmp << "Line: " << errPlace;
	
    ErrPlace place;
    place.file = errFile;
    place.function = tmp.str();

    errorDescription = desc;
    stackTrace.push (place);
}


Exception::~Exception() throw()
{

}


void Exception::addPlaceOfError(string errFile, string errFunc)
{
    ErrPlace place;
    place.file = errFile;
    place.function = errFunc;

    stackTrace.push (place);
}


void Exception::addPlaceOfError(string errFile, int errPlace)
{
	stringstream tmp;
	tmp << "Line: " << errPlace;

    ErrPlace place;
    place.file = errFile;
    place.function = tmp.str();

    stackTrace.push (place);
}


void Exception::printStackTrace()
{
    string name;

    // den namen der klasse besorgen
    name =  typeid(*this).name();

    // unwichtige zeichen entfernen
    name = name.substr(2, name.length() - 3);

    for ( size_t i = 0; i < name.length(); i++)
    {
        if (isdigit(name[i]))
        {
            if (name[i] == '2')
            {
                name[i] = ':';
                name.insert(i, ":");
            }
            else
                name[i] = ':';
        }

    }

    cout << name << endl;

    cout << "Exception Trace:\n";

    ErrPlace place;

    while ( !stackTrace.empty() )
    {
        place = stackTrace.top();
        stackTrace.pop();

        cout << " in " << place.file << "   " << place.function << endl;
    }

    cout << " -> \"" << errorDescription << "\"" << endl;
    cout << "(to continue press a key)" << endl;
    getch();
}


const char* Exception::what() const throw()
{
    return errorDescription.c_str();
}


} // util
} // base
} // vs

