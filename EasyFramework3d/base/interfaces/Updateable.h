/**
 * @file Updateable.hp
 * @author sizilium
 * @date 12.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef UPDATEABLE_H
#define UPDATEABLE_H

// includes
#include <vs/Build.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/**
 * General interfaces for all classes who must implement a update method, say
 * a class who should be update regularly.\n
 * All managers or the context for example are updateable!
 * @see al::MovingPoint, al::SoundSource, al::OggVorbisPlayer
 */
class VS_EXPORT Updateable
{
public:
	virtual ~Updateable();
	/**
	 * Updates the state of the object.
	 * @param deltaT The past time since the last call in milliseconds.
	 */
	virtual void update(double deltaT) = 0;
};

} // interfaces
} // base
} // vs

#endif // UPDATEABLE_H
