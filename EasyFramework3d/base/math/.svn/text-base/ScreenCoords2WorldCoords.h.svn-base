/**
 * @file ScreenCoords2WorldCoords.h
 * @author maccesch
 * @date 29.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef SCREENCOORDSWORLD_H
#define SCREENCOORDSWORLD_H

// includes
#include <vs/Build.hpp>
#include <vs/base/math/DoubleVector.h>
#include <iostream>

namespace vs
{
namespace base
{
namespace math
{

/**
 * @class SreenCoords2WorldCoords
 */
class VS_EXPORT ScreenCoords2WorldCoords
{
public:
    ScreenCoords2WorldCoords();

	/** setter for xScreenHalf
	 * @param setXScreenHalf
	 */
	void setXScreen(unsigned int setXScreen)
	{
		xScreenHalf = static_cast<double>(setXScreen) / 2;
	}
	/** getter for xScreenHalf
	 * @return
	 */
	unsigned int getXScreen() const
	{
		return static_cast<unsigned int>(xScreenHalf * 2);
	}

	/** setter for yScreenHalf
	 * @param setYScreenHalf
	 */
	void setYScreen(unsigned int setYScreen)
	{
		yScreenHalf = static_cast<double>(setYScreen) / 2;
		calcRatio();
	}
	/** getter for yScreenHalf
	 * @return
	 */
	unsigned int getYScreen() const
	{
		return static_cast<unsigned int>(yScreenHalf * 2);
	}

	/** setter for viewingAngle
	 * @param setViewingAngle
	 */
	void setViewingAngle(double setViewingAngle)
	{
		viewingAngle = setViewingAngle / 2;
		calcRatio();
	}
	/** getter for viewingAngle
	 * @return
	 */
	double getViewingAngle() const
	{
		return viewingAngle * 2;
	}

	/** setter for position
	 * @param setPosition
	 */
	void setPosition(DoubleVector setPosition)
	{
		position = setPosition;
	}
	/** getter for position
	 * @return
	 */
	DoubleVector getPosition() const
	{
		return position;
	}

	/** setter for up
	 * @param setUp
	 */
	void setUp(DoubleVector setUp)
	{
		up = setUp;
		calcViewingPlaneBase();
	}
	/** getter for up
	 * @return
	 */
	DoubleVector getUp() const
	{
		return up;
	}

	/** set the viewing Direction */
	void setLookAt(DoubleVector lookAt)
	{
		viewingPlaneZ = lookAt - position;
		viewingPlaneZ /= viewingPlaneZ.abs();
		calcViewingPlaneBase();
	}

    /**
     * calculate the vector from position to the mouse point in 3d
     * @param mouseX The x coordinate of the mouse
     * @param mouseY The y coordinate of the mouse
     * @return the resulting vector
     */
	DoubleVector operator()(int mouseX, int mouseY) const;

    friend ostream& operator<<(ostream &os, const ScreenCoords2WorldCoords &converter);
private:
	void calcRatio()
	{
		ratio = tan(viewingAngle) / xScreenHalf;
	}

	void calcViewingPlaneBase()
	{
		viewingPlaneX = up % viewingPlaneZ;
		viewingPlaneX /= viewingPlaneX.abs();
		viewingPlaneY = viewingPlaneX % viewingPlaneZ;
    }

	float xScreenHalf;
	float yScreenHalf;

	double viewingAngle;
	double ratio;

	DoubleVector viewingPlaneX;
	DoubleVector viewingPlaneY;
	DoubleVector viewingPlaneZ;

	DoubleVector position;
	DoubleVector up;
};

VS_EXPORT ostream& operator<<(ostream &os, const ScreenCoords2WorldCoords &converter);

} // math
} // base
} // vs

#endif // SCREENCOORDSWORLD_H
