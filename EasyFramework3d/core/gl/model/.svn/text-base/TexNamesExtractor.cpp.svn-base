#include <vs/core/gl/model/TexNamesExtractor.h>
#include <vs/core/gl/model/ObjectData.h>
#include <vs/core/gl/model/ModelData.h>
#include <list>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

void TexNamesExtractor::visit(ModelData &model)
{
	// walk through every object ...
	list<ObjectData>::iterator it;
	for (it = model.objects.begin(); it != model.objects.end(); ++it)
	{
		visit(*it);
	}
}

void TexNamesExtractor::visit(ObjectData &object)
{
	// ... and add their texture names to the set
	list<string>::iterator it;
	if (object.textured == '1')
	{
		for (it = object.texNames.begin(); it != object.texNames.end(); ++it)
			textureNames.insert(*it);
	}
}

void TexNamesExtractor::visit(FaceGroupData &faceGroup)
{
	// do nothing
}

void TexNamesExtractor::visit(VertexData &vertex)
{
	// do nothing
}

set<string> TexNamesExtractor::extractTexNames(ModelData &model)
{
	visit(model);
	return textureNames;
}

} // model
} // gl
} // core
} // vs
