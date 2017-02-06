/**
 * @file AbstractTextBox.hpp
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_TEXT_BOX_HPP
#define ABSTRACT_TEXT_BOX_HPP

// includes
#include <vs/Build.hpp>
#include <vs/core/gui/Widget.hpp>

namespace vs
{
namespace core
{
namespace gui
{

/** @class AbstractTextBox
 * 
 */
class VS_EXPORT AbstractTextBox : public Widget
{
public:
	AbstractTextBox(float x = 0, float y = 0, float sizeX = 10, float sizeY = 10)
	:Widget(x, y, sizeX, sizeY)
	{
	}
	
	virtual ~AbstractTextBox()
	{
	}

};

} // gui
} // core
} // vs

#endif  // ABSTRACT_TEXT_BOX_HPP
