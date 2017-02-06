/**
 * @file AbstractGuiFactory.h
 * @author sizilium
 * @date 04.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_GUI_FACTORY_H
#define ABSTRACT_GUI_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/managed/gui/GuiManager.h>

namespace vs
{
// predeclarations
namespace base {namespace interfaces {class AbstractManaged;}}

namespace managed
{
namespace gui
{

/** @class AbstractGuiFactory
 * 
 */
class VS_EXPORT AbstractGuiFactory : public base::interfaces::AbstractFactory<GuiManager>
{
public:
	virtual ~AbstractGuiFactory();
	
	virtual const std::string getName() const = 0;	// from FactoryInterface
	const std::string getNamespace() const;
	
protected:
	void addManaged(base::interfaces::AbstractManaged *managed);

};

} // gui
} // managed
} // vs

#endif  // ABSTRACT_GUI_FACTORY_H
