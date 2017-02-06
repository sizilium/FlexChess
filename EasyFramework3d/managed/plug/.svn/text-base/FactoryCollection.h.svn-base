/**
 * @file FactoryCollection.h
 * @author sizilium
 * @date 02.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FACTORY_COLLECTION_H
#define FACTORY_COLLECTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/Uncopyable.hpp>
#include <vs/base/interfaces/FactoryInterface.h>
#include <vs/base/cont/List.hpp>
#include <string>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace std;

/** @class FactoryCollection
 * 
 */
class VS_EXPORT FactoryCollection : public base::interfaces::Uncopyable
{
public:
	FactoryCollection();
	~FactoryCollection();
	
	/**
	 * Creates a factory by name and returns it. Important for xml stuff. You can
	 * instantiate a factory also manually by calling the constructor.\n
	 * Note: When you use this method you need to cast!
	 * @param name The factories name as a const string.
	 * @param theNamespace Optional parameter if the factories name is overloaded by
	 * several namespaces (the first match will return).
	 * @return The factory, if not existing returns NULL. 
	 */
	base::interfaces::FactoryInterface* getFactory(const string &name, const string &theNamespace = "");
	
	/**
	 * If you want to tell the framework your own factory, manifest it at the context!
	 * Important for xml stuff (xml loader needs to know about the factories).\n
	 * Another (better) way to tell the framework onw factories is the plugin mechanism!
	 * @param factory Manifest an own factory to the EasyFramework.
	 */
	void manifestFactory(base::interfaces::FactoryInterface *factory);
	
private:
	
	static int refCount;

	base::cont::List<base::interfaces::FactoryInterface *> knownFactories;
	
	/*
	AbstractPhysicFactory *knownPhysicFactories;
	AbstractOpenGlFactory *knownOpenGlFactories;
	AbstractModelFactory *knownModelFactories;
	PluginFactoryInterface *knownUpdateableFactories;
	AbstractSoundFactory *knownSoundFactories;
	AbstractConstraintFactory *knownConstrainsFactories;
	*/
};

/**
 * global instance (singleton)
 */
extern FactoryCollection factoryCollection;

} // plug
} // managed
} // vs

#endif  // FACTORY_COLLECTION_H
