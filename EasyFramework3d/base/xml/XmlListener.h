/**
 * @file XmlListener.h
 * @author sizilium
 * @date 18.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLLISTENER_H
#define XMLLISTENER_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/Tree.hpp>
#include <vs/base/xml/XmlPrimitives.h>
#include <string>

namespace vs
{
namespace base
{
namespace xml
{

/** @class XmlListener
 * 
 */
class VS_EXPORT XmlListener
{
public:
	virtual ~XmlListener();
	
	virtual void notifyRead(const base::cont::Tree<XmlTag*> *input) = 0;	
	virtual void notifyWrite(base::cont::Tree<XmlTag*> *fillTreeToWrite) = 0;
};

/**
 * 
 */
VS_EXPORT XmlTag* searchTag(const std::string &searchName, const base::cont::Tree<XmlTag*> *input);

} // xml
} // base
} // vs

#endif  // XMLLISTENER_H
