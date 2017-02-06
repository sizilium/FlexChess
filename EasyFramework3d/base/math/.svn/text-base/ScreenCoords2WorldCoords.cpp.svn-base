#include <vs/base/math/ScreenCoords2WorldCoords.h>

namespace vs
{
namespace base
{
namespace math
{


ScreenCoords2WorldCoords::ScreenCoords2WorldCoords()
		: xScreenHalf(1), yScreenHalf(1), viewingAngle(1), ratio(1),
		viewingPlaneX(1, 0, 0), viewingPlaneY(0, 1, 0), viewingPlaneZ(0, 0, 1),
		position(0, 0, 0), up(0, 1, 0)
{}

DoubleVector ScreenCoords2WorldCoords::operator()(int mouseX, int mouseY) const
{
	// calc mouse coordinates relative to screencenter in world length units
	double xGl = -(mouseX - xScreenHalf) * ratio; //* yScreenHalf / xScreenHalf;
	double yGl = (mouseY - yScreenHalf) * ratio;

	// calc vector from position to mouse pointer
	DoubleVector result = viewingPlaneX * xGl + viewingPlaneY * yGl + viewingPlaneZ;

	return result;
}

ostream& operator<<(ostream &os, const ScreenCoords2WorldCoords &converter)
{
    os << "+ ScreenCoords2WorldCoords: " << endl;
    os << "|\txScreenHalf:\t\t" << converter.xScreenHalf << endl;
    os << "|\tyScreenHalf:\t\t" << converter.yScreenHalf << endl;
    os << "|\tviewingAngle:\t\t" << converter.viewingAngle << endl;
    os << "|" << endl;
    os << "|\tposition:\t\t" << converter.position << endl;
    os << "|\tup:\t\t\t" << converter.up << endl;
    os << "|" << endl;
    os << "|\tviewingPlaneX:\t" << converter.viewingPlaneX << endl;
    os << "|\tviewingPlaneY:\t" << converter.viewingPlaneY << endl;
    os << "|\tviewingPlaneZ:\t" << converter.viewingPlaneZ << endl;
    os << "--" << endl;
    return os;
}

} // math
} // base
} // vs
