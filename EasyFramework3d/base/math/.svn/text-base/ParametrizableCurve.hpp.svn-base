/**
 * @file ParametrizableCurve.hpp
 * @author maccesch
 * @date 18.10.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PARAMETRIZABLECURVE_HPP_
#define PARAMETRIZABLECURVE_HPP_

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace math
{

/**
 * Interface for parametrizable curves. I.e. it takes one parameter
 * and returns a value (image) accordingly.
 */
template<class ParameterType = double, class ImageType = ParameterType>
class VS_EXPORT ParametrizableCurve
{
public:
	ParametrizableCurve();
	virtual ~ParametrizableCurve();
	
	/**
	 * Takes one parameter and returns a value (image) accordingly.
	 * @param x The parameter
	 * @return Dependent on the parameter the image is returned
	 */
	virtual ImageType operator()(ParameterType x) = 0;
};

template<class ParameterType = double, class ImageType = ParameterType>
ParameterTypeizableCurve<ParameterType, ImageType>::ParameterTypeizableCurve()
{
	// do nothing
}

template<class ParameterType = double, class ImageType = ParameterType>
ParameterTypeizableCurve<ParameterType, ImageType>::~ParameterTypeizableCurve()
{
	// do nothing
}

} // math
} // base
} // vs

#endif /*PARAMETRIZABLECURVE_HPP_*/
