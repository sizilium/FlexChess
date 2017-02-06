#include <vs/cmd/ph/CmdsPhysic.h>
#include <vs/core/ph/Point.h>

namespace vs
{
namespace cmd
{
namespace ph
{
using namespace core::ph;
using namespace base::math;


CmdSetCoords::CmdSetCoords(Point *point, DoubleVector coords)
{
	this->point = point;
	this->coords = coords;
	this->oldCoords = point->getCoords();
}

void CmdSetCoords::execute()
{
	point->setCoords(this->coords);
}

void CmdSetCoords::undo()
{
	point->setCoords(this->oldCoords);
}

} // ph
} // cmd
} // vs
