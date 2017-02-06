/**
 * @file ParametrizableSurface.hpp
 * @author maccesch
 * @date 18.10.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PARAMETRIZABLESURFACE_HPP_
#define PARAMETRIZABLESURFACE_HPP_

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace math
{

/**
 * Interface for parametrizable surfaces. I.e. it takes two parameters
 * and returns a value (ImageType) accordingly.
 */
template<class ParameterType1 = double, class ParameterType2 = ParameterType1, class ImageType = ParameterType1>
class VS_EXPORT ParametrizableSurface
{
public:
	ParametrizableSurface();
	virtual ~ParametrizableSurface();

	/**
	 * Takes two parameters and returns a value (ImageType) accordingly.
	 * @param x The first parameter
	 * @param y The second parameter
	 * @return Dependent on the parameters the ImageType is returned
	 */
	virtual ImageType operator()(ParameterType1 x, ParameterType2 y) = 0;
};

template<class ParameterType1 = double, class ParameterType2 = ParameterType1, class ImageType = ParameterType1>
ParametrizableSurface<ParameterType1, ParameterType2, ImageType>::ParametrizableSurface()
{
	// do nothing
}

template<class ParameterType1 = double, class ParameterType2 = ParameterType1, class ImageType = ParameterType1>
ParametrizableSurface<ParameterType1, ParameterType2, ImageType>::~ParametrizableSurface()
{
	// do nothing
}

} // math
} // base
} // vs

#endif /*PARAMETRIZABLESURFACE_HPP_*/
