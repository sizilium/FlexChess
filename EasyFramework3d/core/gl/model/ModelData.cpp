#include <vs/core/gl/model/ModelData.h>
#include <vs/core/gl/model/ObjectData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

ModelData::ModelData():
	filename(""), path(""), formatVersion(0), lod(0), objNum(0), objects()
{}

ModelData::~ModelData()								// destructor
{}

} // namespace model
} // namespace gl
} // namespace core
} // namespace vs
