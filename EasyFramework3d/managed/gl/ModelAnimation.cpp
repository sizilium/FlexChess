#include <vs/managed/gl/ModelAnimation.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <fstream>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace vs::base::util;
using namespace std;

const char ModelAnimation::END_CHAR = '@';

ModelAnimation::ModelAnimation() :
	objectAnimations(NULL)
{
}

ModelAnimation::~ModelAnimation()
{
	delete [] objectAnimations;
	objectAnimations = NULL;
}

void ModelAnimation::load(string filename, model::ManagedModel &model,
						  const map<string, string> *objNameAdapter)
{
	ifstream file;
	file.open(filename.c_str(), ios_base::binary);

	if (!file) // error
		throw FileException("ModelAnimation.cpp", "ModelAnimation::load",
				"The file couldn't be opened (maybe the file wasn't found)", filename);

	char buffer[9];

	file.read(buffer, sizeof(char[8]));
	buffer[8] = '\0';
	if (strncmp(buffer, "VSA", 3) != 0)
		throw FileException("ModelAnimation.cpp", "ModelAnimation::load", "The file is not a Vision Synthesis Animation File", filename);

	// currently unused:
	// float version = atof(&buffer[4]);

	unsigned int fps;
	file.read(reinterpret_cast<char *>(&fps), sizeof(unsigned int));

	file.read(reinterpret_cast<char *>(&objectNum), sizeof(unsigned int));

	assert(objectNum > 0);
	objectAnimations = new ModelObjectAnimation[objectNum];

	for (unsigned int i = 0; i < objectNum; ++i)
	{
		char temp = ' ';
		string objectName = "";
		// load object name
		while (temp != END_CHAR)
		{
			file.read(&temp, sizeof(temp));
			if (temp != END_CHAR)
				objectName += temp;
		}

		if (objNameAdapter != NULL)
		{
			if ((*(const_cast< map<string, string> *>(objNameAdapter))).count(objectName) > 0)
			{
				objectName = (*(const_cast< map<string, string> *>(objNameAdapter)))[objectName];
			}
		}

		unsigned int objectId;
		try
		{
			objectId= model.getObjectId(objectName);
		}
		catch (Exception &e)
		{
			e.addPlaceOfError(__FILE__, __LINE__);
			throw e;
		}
		objectAnimations[i].setObjectCenterIt(model.getObjCenterIt(objectId));
		objectAnimations[i].setObjectEulerIt(model.getObjEulerIt(objectId));
		objectAnimations[i].setObjectSizeIt(model.getObjSizeIt(objectId));
		objectAnimations[i].load(file, filename, fps);
	}
	file.close();
}

void ModelAnimation::update(double deltaT)
{
	AbstractProgressive::update(deltaT);
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].update(deltaT);
	}
}

void ModelAnimation::setCyclic(bool cyclic)
{
	AbstractProgressive::setCyclic(cyclic);
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].setCyclic(cyclic);
	}
}

void ModelAnimation::setSpeedFactor(float speedFactor)
{
	AbstractProgressive::setSpeedFactor(speedFactor);
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].setSpeedFactor(speedFactor);
	}
}

void ModelAnimation::play()
{
	AbstractProgressive::play();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].play();
	}
}

void ModelAnimation::stop()
{
	AbstractProgressive::stop();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].stop();
	}
}

void ModelAnimation::toStart()
{
	AbstractProgressive::toStart();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].toStart();
	}
}

void ModelAnimation::toEnd()
{
	AbstractProgressive::toEnd();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		objectAnimations[i].toEnd();
	}
}

void ModelAnimation::setDuration(double duration)
{
	// do nothing
}

} // gl
} // managed
} // vs
