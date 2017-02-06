#include <vs/Context.h>
#include <vs/base/util/IOStream.h>

#include <GL/glu.h>

#ifndef NO_VSPH
#include <vs/managed/ph/PhysicManager.h>
// xml
#include <vs/managed/ph/PhysicXmlEntries.h>
namespace vs {using namespace managed::ph;}
#endif

#ifndef NO_VSGL
#include <vs/core/gl/Camera.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/managed/gl/model/ModelManager.h>
#include <vs/managed/gl/AnimationManager.h>
// xml
#include <vs/managed/gl/model/ManagedModelXmlEntry.h>
#include <vs/managed/gl/OpenGlXmlEntries.h>
namespace vs 
{
using namespace core::gl;
using namespace managed::gl;
using namespace managed::gl::model;
}
#endif

#ifndef NO_VSPG
#include <vs/managed/plug/PluginManager.h>
namespace vs {using namespace managed::plug;}
#endif

#include <vs/managed/UpdateableManager.h>

#ifndef NO_VSAL
#include <vs/managed/al/SoundManager.h>
namespace vs {using namespace managed::al;}
#endif

#ifndef NO_VSCT
#include <vs/constr/ConstraintManager.h>
namespace vs {using namespace constr;}
#endif

#ifndef NO_VSGUI
#include <vs/managed/gui/GuiXmlEntries.h>
#include <vs/managed/gui/GuiManager.h>
namespace vs {using namespace managed::gui;}
#endif

#ifndef NO_VSXL
#include <vs/base/xml/XmlManager.h>
//#include <vs/xml/AbstractXmlTag.h>
namespace vs {using namespace base::xml;}
#endif


#include <vs/base/interfaces/ManagerInterface.hpp>


namespace vs
{
using namespace std;
using namespace managed;
using namespace base::util;
using namespace base::cont;
using namespace base::interfaces;

/**
 * This is a special namespace for a special global variable.\n
 * The currentContextPointer variable is the only global variable in the EasyFramework.\n 
 * It will be set automatically when you create a new Context, never touch this!
 */
namespace global
{
	/**
	 * The pointer to the current context.
	 */
	Context *currentContextPointer = NULL;

}	// global

	
Context::Context()
{
	if (global::currentContextPointer == NULL)
		this->setCurrent();
}


Context::~Context()
{
	// Because using RcPtr (smart resource counting pointers) the managers will be
	// deleted automatically if the refount is 0.
	
	// the context no longer exists
	if (global::currentContextPointer == this)
	{
		global::currentContextPointer = NULL;
	
		#ifndef NO_VSPH
			setCurrentContext<PhysicManager>(NULL);
			setCurrentManager<PhysicManager>(NULL);
		#endif
		
		#ifndef NO_VSGL
			setCurrentContext<ModelManager>(NULL);
			setCurrentManager<ModelManager>(NULL);
			
			setCurrentContext<OpenGlManager>(NULL);
			setCurrentManager<OpenGlManager>(NULL);
			
			setCurrentContext<AnimationManager>(NULL);
			setCurrentManager<AnimationManager>(NULL);
		#endif
		
		#ifndef NO_VSPG
			setCurrentContext<PluginManager>(NULL);
			setCurrentManager<PluginManager>(NULL);
		#endif
		
		#ifndef NO_VSAL
			setCurrentContext<SoundManager>(NULL);
			setCurrentManager<SoundManager>(NULL);
		#endif
		
			setCurrentContext<UpdateableManager>(NULL);
			setCurrentManager<UpdateableManager>(NULL);
		
		#ifndef NO_VSCT
			setCurrentContext<ConstraintManager>(NULL);
			setCurrentManager<ConstraintManager>(NULL);
		#endif
			
		#ifndef NO_VSCT
			setCurrentContext<GuiManager>(NULL);
			setCurrentManager<GuiManager>(NULL);
		#endif
			
		#ifndef NO_VSXL
			setCurrentContext<XmlManager>(NULL);
			XmlManager::setCurrentManager(NULL);
		#endif
	}
}
// RcPtr destructors will be called here


void Context::setCurrent()
{
	global::currentContextPointer = this;
	
	#ifndef NO_VSPH
		setCurrentContext<PhysicManager>(this);
		setCurrentManager<PhysicManager>(physicManager.operator->());
	#endif
	
	#ifndef NO_VSGL
		setCurrentContext<ModelManager>(this);
		setCurrentManager<ModelManager>(modelManager.operator->());
		
		setCurrentContext<OpenGlManager>(this);
		setCurrentManager<OpenGlManager>(openGlManager.operator->());
		
		setCurrentContext<AnimationManager>(this);
		setCurrentManager<AnimationManager>(animationManager.operator->());
	#endif
	
	#ifndef NO_VSPG
		setCurrentContext<PluginManager>(this);
		setCurrentManager<PluginManager>(pluginManager.operator->());
	#endif
	
	#ifndef NO_VSAL
		setCurrentContext<SoundManager>(this);
		setCurrentManager<SoundManager>(soundManager.operator->());
	#endif
	
		setCurrentContext<UpdateableManager>(this);
		setCurrentManager<UpdateableManager>(updateableManager.operator->());
	
	#ifndef NO_VSCT
		setCurrentContext<ConstraintManager>(this);
		setCurrentManager<ConstraintManager>(constraintManager.operator->());
	#endif
		
	#ifndef NO_VSGUI
		setCurrentContext<GuiManager>(this);
		setCurrentManager<GuiManager>(guiManager.operator->());
	#endif
		
	#ifndef NO_VSXL
		setCurrentContext<XmlManager>(this);
		XmlManager::setCurrentManager(xmlManager.operator->());
	#endif
}

void Context::performAction(string action)
{
	if (action == "refreshManagers")
	{
	#ifndef NO_VSPH
		if (physicManager.isNull() && PhysicManager::isCurrentManager())
		{
			physicManager = RcPtr<PhysicManager> (PhysicManager::getCurrentManager());
			activeList.push_back(physicManager.operator->());
		}
	#endif
		
	#ifndef NO_VSGL
		if (modelManager.isNull() && ModelManager::isCurrentManager())
		{
			modelManager = RcPtr<ModelManager> (ModelManager::getCurrentManager());
			activeList.push_back(modelManager.operator->());
		}
		if (openGlManager.isNull() && OpenGlManager::isCurrentManager())
		{
			openGlManager = RcPtr<OpenGlManager> (OpenGlManager::getCurrentManager());
			activeList.push_front(openGlManager.operator->());
		}
		if (animationManager.isNull() && AnimationManager::isCurrentManager())
		{
			animationManager = RcPtr<AnimationManager> (AnimationManager::getCurrentManager());
			activeList.push_back(animationManager.operator->());
		}
	#endif
		
	#ifndef NO_VSPG
		if (pluginManager.isNull() && PluginManager::isCurrentManager())
		{
			pluginManager = RcPtr<PluginManager> (PluginManager::getCurrentManager());
			activeList.push_back(pluginManager.operator->());
		}
	#endif
		
	#ifndef NO_VSAL
		if (soundManager.isNull() && SoundManager::isCurrentManager())
		{
			soundManager = RcPtr<SoundManager> (SoundManager::getCurrentManager());
			activeList.push_back(soundManager.operator->());
		}
	#endif

		if (updateableManager.isNull() && UpdateableManager::isCurrentManager())
		{
			updateableManager = RcPtr<UpdateableManager> (UpdateableManager::getCurrentManager());
			activeList.push_back(updateableManager.operator->());
		}

	#ifndef NO_VSCT
		if (constraintManager.isNull() && ConstraintManager::isCurrentManager())
		{
			constraintManager = RcPtr<ConstraintManager> (ConstraintManager::getCurrentManager());
			activeList.push_back(constraintManager.operator->());
		}
	#endif
		
	#ifndef NO_VSGUI
		if (guiManager.isNull() && GuiManager::isCurrentManager())
		{
			guiManager = RcPtr<GuiManager> (GuiManager::getCurrentManager());
			activeList.push_back(guiManager.operator->());
		}
	#endif
			
	#ifndef NO_VSXL
		if (xmlManager.isNull() && XmlManager::isCurrentManager())
		{
			xmlManager = RcPtr<XmlManager> (XmlManager::getCurrentManager());
			makeStdXmlTagsKnown(xmlManager.operator->());
		}
	#endif
	}
}


#ifndef NO_VSPH // ------------------------------------------------------------------

managed::ph::PhysicManager* Context::getPhysicManager(Context *share)
{
	if (share)
	{
		// using the old physicManager (RcPtr)
		physicManager = share->physicManager;
		activeList.push_back(physicManager.operator->());
		reorderManager();
	}
	else if (physicManager.isNull())
	{
		// get new physicManager
		physicManager = RcPtr<PhysicManager> (PhysicManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}

	return physicManager.operator->();
}

void Context::enablePhysicManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(physicManager.operator ->()))
	{
		inactiveList.remove(physicManager.operator ->());
		activeList.add(physicManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(physicManager.operator->()))
	{
		activeList.remove(physicManager.operator ->());
		inactiveList.add(physicManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isPhysicManager() const
{
	if (physicManager.isNull())
		return false;
	else
		return true;
}

#endif // NO_VSPH


#ifndef NO_VSGL // --------------------------------------------------------------------

managed::gl::OpenGlManager* Context::getOpenGlManager(Context *share)
{
	if (share)
	{
		// using the old openGlManager (RcPtr)
		openGlManager = share->openGlManager;
		activeList.push_front(openGlManager.operator->());
		reorderManager();
	}
	else if (openGlManager.isNull())
	{
		// get new openGlManager
		openGlManager = RcPtr<OpenGlManager> (OpenGlManager::getCurrentManager());
		// activeList.push_front already called!
		reorderManager();
	}
	
	return openGlManager.operator->();
}

void Context::enableOpenGlManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(openGlManager.operator ->()))
	{
		inactiveList.remove(openGlManager.operator ->());
		activeList.add(openGlManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(openGlManager.operator->()))
	{
		activeList.remove(openGlManager.operator ->());
		inactiveList.add(openGlManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isOpenGlManager() const
{
	if (openGlManager.isNull())
		return false;
	else
		return true;
}


ModelManager* Context::getModelManager(Context *share)
{
	if (share)
	{
		// using the old modelManager (RcPtr)
		modelManager = share->modelManager;
		activeList.push_back(modelManager.operator->());
		reorderManager();
	}
	else if (modelManager.isNull())
	{
		// get new modelManager
		modelManager = RcPtr<ModelManager> (ModelManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return modelManager.operator->();
}

void Context::enableModelManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(modelManager.operator ->()))
	{
		inactiveList.remove(modelManager.operator ->());
		activeList.add(modelManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(modelManager.operator->()))
	{
		activeList.remove(modelManager.operator ->());
		inactiveList.add(modelManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isModelManager() const
{
	if (modelManager.isNull())
		return false;
	else
		return true;
}


AnimationManager* Context::getAnimationManager(Context *share)
{
	if (share)
	{
		// using the old animationManager (RcPtr)
		animationManager = share->animationManager;
		activeList.push_back(animationManager.operator->());
		reorderManager();
	}
	else if (animationManager.isNull())
	{
		// get new animationManager
		animationManager = RcPtr<AnimationManager> (AnimationManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return animationManager.operator->();
}

void Context::enableAnimationManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(animationManager.operator ->()))
	{
		inactiveList.remove(animationManager.operator ->());
		activeList.add(animationManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(animationManager.operator->()))
	{
		activeList.remove(animationManager.operator ->());
		inactiveList.add(animationManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isAnimationManager() const
{
	if (animationManager.isNull())
		return false;
	else
		return true;
}


#endif // NO_VSGL


#ifndef NO_VSPG // -------------------------------------------------------------------


managed::plug::PluginManager* Context::getPluginManager(Context *share)
{
	if (share)
	{
		// using the old pluginManager (RcPtr)
		pluginManager = share->pluginManager;
		activeList.push_back(pluginManager.operator->());
		reorderManager();
	}
	else if (pluginManager.isNull())
	{
		// get new pluginManager
		pluginManager = RcPtr<PluginManager> (PluginManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return pluginManager.operator->();
}

void Context::enablePluginManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(pluginManager.operator ->()))
	{
		inactiveList.remove(pluginManager.operator ->());
		activeList.add(pluginManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(pluginManager.operator->()))
	{
		activeList.remove(pluginManager.operator ->());
		inactiveList.add(pluginManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isPluginManager() const
{
	if (pluginManager.isNull())
		return false;
	else
		return true;
}


#endif // NO_VSPG



managed::UpdateableManager* Context::getUpdateableManager(Context *share)
{
	if (share)
	{
		// using the old updateableManager (RcPtr)
		updateableManager = share->updateableManager;
		activeList.push_back(updateableManager.operator->());
		reorderManager();
	}
	else if (updateableManager.isNull())
	{
		// get new updateableManager
		updateableManager = RcPtr<UpdateableManager> (UpdateableManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return updateableManager.operator->();
}

void Context::enableUpdateableManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(updateableManager.operator ->()))
	{
		inactiveList.remove(updateableManager.operator ->());
		activeList.add(updateableManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(updateableManager.operator->()))
	{
		activeList.remove(updateableManager.operator ->());
		inactiveList.add(updateableManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isUpdateableManager() const
{
	if (updateableManager.isNull())
		return false;
	else
		return true;
}


#ifndef NO_VSAL // -------------------------------------------------------------------

managed::al::SoundManager* Context::getSoundManager(Context *share)
{
	if (share)
	{
		// using the old soundManager (RcPtr)
		soundManager = share->soundManager;
		activeList.push_back(soundManager.operator->());
		reorderManager();
	}
	else if (soundManager.isNull())
	{
		// get new soundManager
		soundManager = RcPtr<SoundManager> (SoundManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return soundManager.operator->();
}

void Context::enableSoundManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(soundManager.operator ->()))
	{
		inactiveList.remove(soundManager.operator ->());
		activeList.add(soundManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(soundManager.operator->()))
	{
		activeList.remove(soundManager.operator ->());
		inactiveList.add(soundManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isSoundManager() const
{
	if (soundManager.isNull())
		return false;
	else
		return true;
}


#endif // NO_VSAL


#ifndef NO_VSCT // --------------------------------------------------------------------


constr::ConstraintManager* Context::getConstraintManager(Context *share)
{
	if (share)
	{
		// using the old constraintManager (RcPtr)
		constraintManager = share->constraintManager;
		activeList.push_back(constraintManager.operator->());
		reorderManager();
	}
	else if (constraintManager.isNull())
	{
		// get new constraintManager
		constraintManager = RcPtr<ConstraintManager> (ConstraintManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return constraintManager.operator->();
}

void Context::enableConstraintManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(constraintManager.operator ->()))
	{
		inactiveList.remove(constraintManager.operator ->());
		activeList.add(constraintManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(constraintManager.operator->()))
	{
		activeList.remove(constraintManager.operator ->());
		inactiveList.add(constraintManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isConstraintManager() const
{
	if (constraintManager.isNull())
		return false;
	else
		return true;
}


#endif // NO_VSCT


#ifndef NO_VSGUI // --------------------------------------------------------------------


managed::gui::GuiManager* Context::getGuiManager(Context *share)
{
	if (share)
	{
		// using the old guiManager (RcPtr)
		guiManager = share->guiManager;
		activeList.push_back(guiManager.operator->());
		reorderManager();
	}
	else if (guiManager.isNull())
	{
		// get new guiManager
		guiManager = RcPtr<GuiManager> (GuiManager::getCurrentManager());
		// activeList.push_back already called!
		reorderManager();
	}
	
	return guiManager.operator->();
}

void Context::enableGuiManager(bool enable)
{
	// activate manager
	if (enable && inactiveList.contains(guiManager.operator ->()))
	{
		inactiveList.remove(guiManager.operator ->());
		activeList.add(guiManager.operator ->());
	}
	// deactivate manager
	else if (!enable && activeList.contains(guiManager.operator->()))
	{
		activeList.remove(guiManager.operator ->());
		inactiveList.add(guiManager.operator ->());
	}
	
	reorderManager();	// right order
}

bool Context::isGuiManager() const
{
	if (guiManager.isNull())
		return false;
	else
		return true;
}


#endif // NO_VSGUI


#ifndef NO_VSXL // -------------------------------------------------------------------


XmlManager* Context::getXmlManager(Context *share)
{
	if (share)
	{
		// using the old xmlManager (RcPtr)
		xmlManager = share->xmlManager;
		// no activeList.push_back
	}
	else if (xmlManager.isNull())
	{
		// get new xmlManager
		xmlManager = RcPtr<XmlManager> (XmlManager::getCurrentManager());
		
		// add known std xml tags, so the xml manager will be able to read them
		makeStdXmlTagsKnown(xmlManager.operator->());
	}

	return xmlManager.operator->();
}

bool Context::isXmlManager() const
{
	if (xmlManager.isNull())
		return false;
	else
		return true;
}


void Context::makeStdXmlTagsKnown(XmlManager *manager)
{
#ifndef NO_VSPH
	manager->addKnownXmlEntry(new PointXmlEntry);
	manager->addKnownXmlEntry(new EulerXmlEntry);
	manager->addKnownXmlEntry(new OrientatedPointXmlEntry);
	manager->addKnownXmlEntry(new MovingPointXmlEntry);
	manager->addKnownXmlEntry(new MovingEulerXmlEntry);
	manager->addKnownXmlEntry(new MovingOrientatedPointXmlEntry);
	manager->addKnownXmlEntry(new AcceleratingPointXmlEntry);
	manager->addKnownXmlEntry(new AcceleratingEulerXmlEntry);
	manager->addKnownXmlEntry(new PointBodyXmlEntry);
	manager->addKnownXmlEntry(new RigidBodyXmlEntry);
#endif

#ifndef NO_VSGL
	manager->addKnownXmlEntry(new ManagedModelXmlEntry);
	manager->addKnownXmlEntry(new LightXmlEntry);
	manager->addKnownXmlEntry(new GridXmlEntry);
	manager->addKnownXmlEntry(new OpenGlSettingsXmlEntry);
#endif

#ifndef NO_VSPG

#endif

#ifndef NO_VSAL

#endif

#ifndef NO_VSCT

#endif

#ifndef NO_VSGUI
	
#endif
	
}

#endif // NO_VSXL


void Context::outDebug() const
{
	out << "Context debugging informations:"; // << endl;
	//out << " Active Managers: " << activeList.size(); // endl;
	//out << " Inactive Managers: " << inactiveList.size(); // endl;
	out << "-------------------------------"; // << endl;
#ifndef NO_VSPH
	if (!physicManager.isNull())
	{
		out << "PhysicManager:"; // << endl;
		physicManager.operator->()->outDebug();
	}
#endif
	
#ifndef NO_VSGL
		if (!openGlManager.isNull())
		{
			out << "OpenGlManager:"; // << endl;
			openGlManager.operator->()->outDebug();
		}
		if (!modelManager.isNull())
		{
			out << "ModelManager:"; // << endl;
			modelManager.operator->()->outDebug();
		}
		if (!animationManager.isNull())
		{
			out << "AnimationManager:"; // endl;
			animationManager.operator->()->outDebug();
		}
#endif
	
#ifndef NO_VSPG
	if (!pluginManager.isNull())
	{
		out << "PluginManager:"; // endl;
		pluginManager.operator->()->outDebug();
	}
#endif
	
	if (!updateableManager.isNull())
	{
		out << "UpdateableManager:"; // endl;
		updateableManager.operator->()->outDebug();
	}
	
#ifndef NO_VSAL
	if (!soundManager.isNull())
	{
		out << "SoundManager"; // << endl;
		soundManager.operator->()->outDebug();
	}
#endif
	
#ifndef NO_VSCT
	if (!constraintManager.isNull())
	{
		out << "ConstraintManager:"; // << endl;
		constraintManager.operator->()->outDebug();
	}
#endif
	
#ifndef NO_VSGUI
	if (!guiManager.isNull())
	{
		out << "GuiManager:"; // << endl;
		guiManager.operator->()->outDebug();
	}
#endif
	
#ifndef NO_VSXL
	if (!xmlManager.isNull())
	{
		out << "XmlManager:"; // << endl;
		xmlManager.operator->()->outDebug();
	}
#endif
}

void Context::reset()
{
	List<ManagerInterface *>::Iterator it(activeList);
	while (it != activeList.end())
	{
		(*it)->clear();
		++it;
	}
	
	it = inactiveList.begin();
	while (it != inactiveList.end())
	{
		(*it)->clear();
		++it;
	}
	
#ifndef NO_VSXL
	xmlManager.operator->()->clear();
#endif
}

// ------------------------------- UPDATE -------------------------------------------

void Context::update(double time)
{
	List<ManagerInterface *>::Iterator it(activeList);
	
	while (it != activeList.end())
	{
		(*it)->update(time);
		++it;
	}
}

void Context::reorderManager()
{
	List<ManagerInterface *> tmpList;
	tmpList = activeList;
	activeList.clear();
	
// 1.	(first update)
#ifndef NO_VSGL
	if (tmpList.contains(openGlManager.operator->()))	// fist update cam (projection)
		activeList.push_back(openGlManager.operator ->());
	if (tmpList.contains(modelManager.operator->()))
		activeList.push_back(modelManager.operator ->());
#endif

// 2.
#ifndef NO_VSPH
	if (tmpList.contains(physicManager.operator->()))
		activeList.push_back(physicManager.operator ->());
#endif

// 3.
#ifndef NO_VSPG
	if (tmpList.contains(pluginManager.operator->()))
		activeList.push_back(pluginManager.operator ->());
#endif

// 4.
#ifndef NO_VSAL
	if (tmpList.contains(soundManager.operator->()))
		activeList.push_back(soundManager.operator ->());
#endif

// 5.
	if (tmpList.contains(updateableManager.operator->()))
		activeList.push_back(updateableManager.operator ->());

// 6.
#ifndef NO_VSCT
	if (tmpList.contains(constraintManager.operator->()))
		activeList.push_back(constraintManager.operator ->());
#endif

// 7.	(last update)
#ifndef NO_VSGUI
	if (tmpList.contains(guiManager.operator->()))
		activeList.push_back(guiManager.operator ->());
#endif
}

// ------------------------------ INJECTS -------------------------------------------

void Context::injectViewport(int x, int y, int width, int height)
{
#ifndef NO_VSGL
	if(!openGlManager.isNull())
		openGlManager->injectViewport(x, y, width, height);
#endif
	
#ifndef NO_VSGUI
	if(!guiManager.isNull())
		guiManager->injectViewport(x, y, width, height);
#endif
}

void Context::injectMouseHover(int x, int y)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectMouseHover(x, y);
#endif
}

void Context::injectMouseLeftClick(int x, int y, bool pressed)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectMouseLeftClick(x, y, pressed);
#endif
	
#ifndef NO_VSGL
	if (!modelManager.isNull() && !openGlManager.isNull() && pressed == false)
	{
		Camera *camera = openGlManager->getCurrentCamera();
		if (camera)
		{
		    //void performPicking(int mouseX, int mouseY, short clickRegion = 3, GLdouble fovy = 45,
			//					GLdouble zNear = 0.1, GLdouble zFar = 1000, unsigned int bufferSize = 512);

			//modelManager->performPicking(x, y, camera);
			//modelManager->update();
		}
	}
#endif
}

void Context::injectMouseRightClick(int x, int y, bool pressed)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectMouseRightClick(x, y, pressed);
#endif
}

void Context::injectMouseMiddleClick(int x, int y, bool pressed)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectMouseMiddleClick(x, y, pressed);
#endif
}

void Context::injectMouseWheel(char ticks)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectMouseWheel(ticks);
#endif
}

void Context::injectKeyPress(unsigned char key)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectKeyPress(key);
#endif
}

void Context::injectKeyRelease(unsigned char key)
{
#ifndef NO_VSGUI
	if (!guiManager.isNull())
			guiManager->injectKeyRelease(key);
#endif
}

bool Context::isContext()
{
	if (global::currentContextPointer != NULL)
		return true;
	else
		return false;
}

Context* Context::getCurrentContext()
{
	if (global::currentContextPointer == NULL)
		global::currentContextPointer = new Context;
	return global::currentContextPointer;
}


} // vs
