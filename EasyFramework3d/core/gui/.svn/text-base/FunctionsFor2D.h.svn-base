/**
 * @file FunctionsFor2D.h
 * @author sizilium
 * @date 22.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FUNCTIONS_FOR_2D_H
#define FUNCTIONS_FOR_2D_H

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace core
{
namespace gui
{
// predeclarations
class VS_EXPORT Widget;

/**
 * Sets opengl to a 2d orthogonal projection. Then you can draw directly in the viewport (not in
 * space). Call resetPerspectiveProjection if the 2d drawing are finished.
 */
VS_EXPORT void setOrthographicProjection(int x = 0, int y = 0, int width = 1024, int height = 768);

/**
 * Resets orthogonal projection to previous perspective projection.
 * Notice that the opgengl modelview matrix can be changed! You must save it manually if needed.
 */
VS_EXPORT void resetPerspectiveProjection();

/**
 * Checks if a coordinate hits a widget. 
 * The function also calcs the local coordinates hit coordinates within the widget, if a hit
 * occured.
 * @param widget The widget who will be checked.
 * @param x The hit x test coordinate.
 * @param y The hit y test coordinate.
 * @param localX The calculated x coordinate within the given widget, where the hit occured (if true).
 * @param localY The calculated y coordinate within the given widget, where the hit occured (if true).
 * @return True if the tested coordinates are up to the widget dimensions.
 */
VS_EXPORT bool hitWidget(const Widget *widget, int x, int y, int &localX, int &localY);


} // gui
} // core
} // vs

#endif  // FUNCTIONS_FOR_2D_H
