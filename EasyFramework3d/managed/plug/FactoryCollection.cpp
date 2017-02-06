#include <vs/managed/plug/FactoryCollection.h>
#include <vs/base/cont/SmartIterator.hpp>
#include <algorithm>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace base::interfaces;
using namespace base::cont;

FactoryCollection factoryCollection;

int FactoryCollection::refCount = 0;

FactoryCollection::FactoryCollection()
{
	refCount++;
	assert ("Only one Factory collection instance allowed (because singleton!) Use the global instance instead." && refCount < 2);

	// search factories in plugins
	// TODO factory plugin search
}

FactoryCollection::~FactoryCollection()
{
	// delete factories
	SmartIterator<FactoryInterface *> it (knownFactories.iterator() );
	while (it.hasNext())
		delete it.next();
	
	knownFactories.clear();
}

FactoryInterface* FactoryCollection::getFactory(const string &name, const string &ns)
{
	List<FactoryInterface *>::Iterator it;

	// ptr_fun
	class Compare
	{
	public:
		static bool compare_1(string cmp_1, string cmp_2)
		{
			if (cmp_1 == cmp_2)
				return true; else return false;
		}
		static bool compare_2(pair<string, string> cmp_1, pair<string, string> cmp_2)
		{
			if (cmp_1.first == cmp_2.first && cmp_1.second == cmp_2.second)
				return true; else return false;
		}
	};
	/*
	if (ns == "")
	{
		// search for name
		it = find_if(knownFactories.begin(), knownFactories.end(), 
		             bind2nd(ptr_fun(Compare::compare_1), name));
		if (it != knownFactories.end())
			return *it;
		else
			return NULL;
	}
	else
	{
		// search for name and namespace
		it = find_if(knownFactories.begin(), knownFactories.end(), 
		             bind2nd(ptr_fun(Compare::compare_2), pair<string, string>(name, ns)));
		if (it != knownFactories.end())
			return *it;
		else
			return NULL;
	}
	*/
	return NULL;
}


void FactoryCollection::manifestFactory(FactoryInterface *factory)
{
	knownFactories.push_back(factory);
}

} // plug
} // managed
} // vs
