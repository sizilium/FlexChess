#include <vs/base/xml/XmlListener.h>

namespace vs
{
namespace base
{
namespace xml
{
using namespace cont;
using namespace std;

XmlListener::~XmlListener()
{}

XmlTag* searchTag(const string &searchName, const Tree<XmlTag*> *input)
{
	Tree<XmlTag*>::Const_Iterator it (input);
	while (it.hasNext())
	{
		if ((*it)->getName() == searchName)
			return *it;
		++it;
	}
	return NULL;
}

} // xml
} // base
} // vs
