/**
 * @file IDGenerator.hpp this file includes a id generator wich generates unique
 * ids. Note: For efficiently reasons there are no exception handling!
 */

#ifndef IDGENERATOR_H
#define IDGENERATOR_H

// includes
#include <vs/Build.hpp>
#include <list>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace std;

/** @class IDGenerator
 * generates unique ids on an efficiently way
 */
template<class T = int> 
class VS_EXPORT IDGenerator
{
public:
    IDGenerator();
    ~IDGenerator();

    /**
     * @return the next available id
     */
    T getNextID();

    /**
     * inform the IDGenerator that an id is no longer in use. Don't forget
     * to free unused ids!
     */
    void freeID(T id);

    void coutInfos() const;

private:
    T count;
    list<T> freeIDs;

};


template<class T> IDGenerator<T>::IDGenerator()
{
    count = 0;
}


template<class T> IDGenerator<T>::~IDGenerator()
{

}


template<class T> T IDGenerator<T>::getNextID()
{
    T retval;

    // nachschauen ob lücken frei sind
    if (!freeIDs.empty() )
    {
        retval = freeIDs.front();
        freeIDs.pop_front();
        return retval;
    }
    // ansonsten count erhöhen
    else
    {
        // Achtung: überlauf wird nicht abgefragt
        return ++count;
    }
}


template<class T> void IDGenerator<T>::freeID(T id)
{
    freeIDs.push_back(id);
}


template<class T> void IDGenerator<T>::coutInfos() const
{
    cout << "count: " << count << "   freeIDs.size(): " << freeIDs.size() << endl;
}

} // util
} // base
} // vs

#endif
