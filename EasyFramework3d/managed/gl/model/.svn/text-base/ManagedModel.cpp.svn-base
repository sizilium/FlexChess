#include <vs/managed/gl/model/ModelManager.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/base/util/Exception.h>
using namespace vs::base::util;

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{

using namespace core::gl;

ManagedModel::ManagedModel() :
	renderQueuePart(), renderQueueStart(), renderQueueEnd(), filename(""), objectIds2iterators()
{
#ifndef NDEBUG
	customCenters = false;
	customRotations = false;
	customSizes = false;
	customColors = false;
#endif
}

ManagedModel::~ManagedModel()
{
	// remove this object from the manager but don't delete
	// because it is currently being deleted
	manager->removeManaged(name, false);
}

unsigned int ManagedModel::getObjectId(string objectName)
{
	pair<string, string> key = make_pair(objectName, filename);
	if (manager->objNamesFilenames2models.count(key) == 0)
		throw Exception(__FILE__, __LINE__,
				"This ManagedModel doesn't have an model object with the name '"
				+ objectName + "'");

	return manager->objNamesFilenames2models[key];
}

void ManagedModel::activate()
{
	assert(!isActive());
	++renderQueueEnd;
	manager->renderQueue.splice(renderQueueEnd, renderQueuePart);
	--renderQueueEnd;
}

void ManagedModel::deactivate()
{
	assert(isActive());
	++renderQueueEnd;
	renderQueuePart.splice(renderQueuePart.end(), manager->renderQueue, renderQueueStart,
						   renderQueueEnd);
	--renderQueueEnd;
}

list<double>::iterator ManagedModel::getObjColorIt(unsigned int objectId)
{
	assert(customColors);
	list<double>::iterator it = objectIds2iterators[objectId];
	for (int i = 0; i < 14; ++i, ++it)
		;
	return it;
}

list<double>::iterator ManagedModel::getObjCenterIt(unsigned int objectId)
{
	assert(customCenters);
	list<double>::iterator it = objectIds2iterators[objectId];
	++it;
	++it;
	return it;
}

list<double>::iterator ManagedModel::getObjEulerIt(unsigned int objectId)
{
	assert(customRotations);
	list<double>::iterator it = objectIds2iterators[objectId];
	for (int i = 0; i < 6; ++i, ++it)
		;
	return it;
}

list<double>::iterator ManagedModel::getObjSizeIt(unsigned int objectId)
{
	assert(customSizes);
	list<double>::iterator it = objectIds2iterators[objectId];
	for (int i = 0; i < 10; ++i, ++it)
		;
	return it;
}

} // model
} // gl
} // managed
} // vs
