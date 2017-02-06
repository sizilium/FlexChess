/**
 * @file Context.h
 * @author sizilium
 * @date 01.06.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef CONTEXT_H
#define CONTEXT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractContext.h>
#include <vs/base/cont/List.hpp>
#include <vs/base/util/ReferenceCounting.h>
#include <vs/Version.hpp>
#include <string>

namespace vs
{

// predeclarations (for faster compilation)
#ifndef NO_VSPH
namespace managed {namespace ph {class PhysicManager; }}
#endif

#ifndef NO_VSGL
namespace managed {namespace gl {namespace model {class ModelManager; }}}
namespace managed {namespace gl {class OpenGlManager; }}
namespace managed {namespace gl {class AnimationManager; }}
#endif

#ifndef NO_VSPG
namespace managed {namespace plug {class PluginManager;}}
#endif

#ifndef NO_VSAL
namespace managed {namespace al {class SoundManager;}}
#endif

#ifndef NO_VSXL
namespace base {namespace xml {class XmlManager;}}
#endif

namespace managed {class UpdateableManager;}

#ifndef NO_VSCT
namespace constr {class ConstraintManager;}
#endif

#ifndef NO_VSGUI
namespace managed{namespace gui {class GuiManager;}}
#endif

namespace base
{
namespace interfaces
{
class ManagerInterface;
class FactoryInterface;
}
}


/** @class Context
 * This is the "root" class of the EasyFramework. Here you can get/create all Managers:
 * - PhysicManager
 * - OpenGlManager
 * - ModelManager
 * - ConstraintManager
 * - PluginManager
 * - UpdateableManager
 * - SoundManager
 * 
 * If a manager in the context does not exist, it will be created automatically by the
 * get...Manager() methods. Each context contains his separate managers.\n
 * Normally you need only one context, but if you want to use several OpenGL context
 * (several VsmWidgets with Qt for example) you need several vs context objects too.\n
 * The context is updateable like the managers. Mean: When you call update(deltaT) to
 * the context all existing managers will be updated automatically for you.
 */
class VS_EXPORT Context : public base::interfaces::AbstractContext
{
public:
	/**
	 * There are no managers created by default. The constructor will set all pointers
	 * to the manager to null. Even when a get...Manager() method is called the manager
	 * will be created.
	 */
	Context();

	/**
	 * The destructor is very important. It deletes all allocated managers (the managers
	 * will delete again his own members etc.). Don't forget to call the destructor of
	 * the context when there is no longer need of it (when the program is exiting). Else
	 * you loose eventually some memory storage.
	 */
	virtual ~Context();

	/**
	 * Set the context to "this" object. All XmlFactory's now will add their specifis items
	 * to the properly manager. All XmlFactory's works on the actual context/managers.
	 */
	void setCurrent();
	
	/**
	 * This method is used for internally manager -> context signalling. Don't care about it.
	 * The context layer is above the managers layer. Sometimes a manager want to call a context 
	 * method (update, refresh etc.). But the layer architecture says, that only top down communication
	 * is allowed! So the managers called a virtual method on AbstractContext, wich is located on
	 * a lower layer (indirect communication trick).
	 * @see AbstractContext
	 */
	void performAction (std::string action);
	
#ifndef NO_VSPH
	/**
	 * This is a "getInstance" method, means that an existing PhysicManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one PhysicManager for each context.\n
	 * You can use this method to get access to the PhysicManager's items.
	 * @param sharePhysicManager If you not want to use an already existing PhysicManager
	 * in another context, pass the old PhysicManager to this parameter (optional).
	 * @return PhysicManager object who handels all updateable physic classes like MovingPoint,
	 * RigidBody etc.
	 * @see vs::managed::ph::PhysicManager
	 */
	managed::ph::PhysicManager* getPhysicManager(Context *sharePhysicManager = NULL);

	/**
	 * Activates or deactivates the PhysicManager in the context.
	 * @param enable If you pass false, the context won't update the PhysicManager.
	 * Note: This doesn't regards the manually PhysicManager update method!
	 */
	void enablePhysicManager(bool enable);
	
	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isPhysicManager() const;
#endif

#ifndef NO_VSGL
	/**
	 * This is a "getInstance" method, means that an existing OpenGlManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one OpenGlManager for each context.\n
	 * You can use this method to get access to the OpenGlManager's items, like graphic
	 * settings, lights, cams etc.
	 * @param shareOpenGlManager If you not want to use an already existing OpenGlManager
	 * in another context, pass the old OpenGlManager to this parameter (optional).
	 * @return OpenGlManager object who handels all OpenGL stuff.
	 * @see vs::managed::gl::OpenGlManager
	 */
	managed::gl::OpenGlManager* getOpenGlManager(Context *shareOpenGlManager = NULL);

	/**
	 * Activates or deactivates the OpenGlManager in the context.
	 * @param enable If you pass false, the context won't update the OpenGlManager.
	 * Note: This doesn't regards the manually OpenGlManager update method!
	 */
	void enableOpenGlManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isOpenGlManager() const;

	/**
	 * This is a "getInstance" method, means that an existing ModelManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one ModeManager for each context.\n
	 * You can use this method to get access to the ModelManager's items.
	 * @param shareModelManager If you not want to use an already existing ModelManager
	 * in another context, pass the old ModelManager to this parameter (optional).
	 * @return ModelManager object who handels ManagedObjects
	 * @see vs::managed::gl::model::ModelManager
	 */
	managed::gl::model::ModelManager* getModelManager(Context *shareModelManager = NULL);

	/**
	 * Activates or deactivates the ModelManager in the context.
	 * @param enable If you pass false, the context won't update the ModelManager.
	 * Note: This doesn't regards the manually ModelManager update method!
	 */
	void enableModelManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isModelManager() const;
	
	/**
	 * This is a "getInstance" method, means that an existing AnimationManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one ModeManager for each context.\n
	 * You can use this method to get access to the AnimationManager's items.
	 * @param shareAnimationManager If you not want to use an already existing AnimationManager
	 * in another context, pass the old AnimationManager to this parameter (optional).
	 * @return AnimationManager object who handels ManagedObjects
	 * @see vs::managed::gl::AnimationManager
	 */
	managed::gl::AnimationManager* getAnimationManager(Context *shareAnimationManager = NULL);

	/**
	 * Activates or deactivates the AnimationManager in the context.
	 * @param enable If you pass false, the context won't update the AnimationManager.
	 * Note: This doesn't regards the manually AnimationManager update method!
	 */
	void enableAnimationManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isAnimationManager() const;
#endif

#ifndef NO_VSPG
	/**
	 * This is a "getInstance" method, means that an existing PluginManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one PluginManager for each context.\n
	 * You can use this method to get access to the PluginManager's items.
	 * @param sharePluginManager If you not want to use an already existing PluginManager
	 * in another context, pass the old PluginManager to this parameter (optional).
	 * @return PluginManager object who handels all updateable (userdefined) classes like.
	 * @see vs::managed::plug::PluginManager
	 */
	managed::plug::PluginManager* getPluginManager(Context *sharePluginManager = NULL);

	/**
	 * Activates or deactivates the PluginManager in the context.
	 * @param enable If you pass false, the context won't update the PluginManager.
	 * Note: This doesn't regards the manually PluginManager update method!
	 */
	void enablePluginManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isPluginManager() const;
#endif

	/**
	 * This is a "getInstance" method, means that an existing UpdateableManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one UpdateableManager for each context.\n
	 * You can use this method to get access to the UpdateableManager's items.
	 * @param shareUpdateableManager If you not want to use an already existing UpdateableManager
	 * in another context, pass the old UpdateableManager to this parameter (optional).
	 * @return UpdateableManager object who handels all updateable (userdefined) classes like.
	 * @see vs::managed::UpdateableManager
	 */
	managed::UpdateableManager* getUpdateableManager(Context *shareUpdateableManager = NULL);

	/**
	 * Activates or deactivates the UpdateableManager in the context.
	 * @param enable If you pass false, the context won't update the UpdateableManager.
	 * Note: This doesn't regards the manually UpdateableManager update method!
	 */
	void enableUpdateableManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isUpdateableManager() const;

#ifndef NO_VSAL
	/**
	 * 
	 * 
	 */
	managed::al::SoundManager* getSoundManager(Context *shareSoundManager = NULL);

	/**
	 * Activates or deactivates the SoundManager in the context.
	 * @param enable If you pass false, the context won't update the SoundManager.
	 * Note: This doesn't regards the manually SoundManager update method!
	 */
	void enableSoundManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isSoundManager() const;
#endif

#ifndef NO_VSCT
	/**
	 * This is a "getInstance" method, means that an existing ConstraintManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one ConstraintManager for each context.\n
	 * You can use this method to get access to the ConstraintManager's items.
	 * @param shareConstraintManager If you not want to use an already existing ConstraintManager
	 * in another context, pass the old ConstraintManager to this parameter (optional).
	 * @return ConstraintManager object who handels AbstractConstraints
	 * @see vs::constr::ConstraintManager
	 */
	constr::ConstraintManager* getConstraintManager(Context *shareConstraintManager = NULL);

	/**
	 * Activates or deactivates the ConstraintManager in the context.
	 * @param enable If you pass false, the context won't update the ConstraintManager.
	 * Note: This doesn't regards the manually ConstraintManager update method!
	 */
	void enableConstraintManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isConstraintManager() const;
#endif	
	
#ifndef NO_VSGUI
	/**
	 * This is a "getInstance" method, means that an existing GuiManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one GuiManager for each context.\n
	 * You can use this method to get access to the GuiManager's items.
	 * @param shareGuiManager If you not want to use an already existing GuiManager
	 * in another context, pass the old GuiManager to this parameter (optional).
	 * @return GuiManager object who handels Widgets
	 * @see vs::constr::GuiManager
	 */
	managed::gui::GuiManager* getGuiManager(Context *shareGuiManager = NULL);

	/**
	 * Activates or deactivates the GuiManager in the context.
	 * @param enable If you pass false, the context won't update the GuiManager.
	 * Note: This doesn't regards the manually GuiManager update method!
	 */
	void enableGuiManager(bool enable);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isGuiManager() const;
#endif	

#ifndef NO_VSXL
	/**
	 * This is a "getInstance" method, means that an existing XmlManager object will
	 * be returned and a not existing automatically will be created and returned.\n
	 * There is only one XmlManager for each context.\n
	 * You can use this method to get access to the XmlManager's items.
	 * @param shareXmlManager If you not want to use an already existing XmlManager
	 * in another context, pass the old XmlManager to this parameter (optional).
	 * @return XmlManager object who handels abstract xml factories.
	 * @see vs::base::xml::XmlManager
	 */
	base::xml::XmlManager* getXmlManager(Context *shareXmlManager = NULL);

	/**
	 * Checks if the manager exists (without creating a new if not).
	 */
	bool isXmlManager() const;
	
	void makeStdXmlTagsKnown(base::xml::XmlManager *manager);
#endif

	/**
	 * Updates all existing managers with the given time difference. Note that you must
	 * inject a time here (there is no default like some other updateables).
	 * @param deltaT Pass the time in milliseconds. Use a timer! 
	 * @see vs::base::util::Time
	 */
	void update(double deltaT = 0);

	/**
	 * Informs the EasyFramework about the viewport (opengl drawing area) globaly.
	 * This informations will be redirect to the GuiManager and the OpenGlManager (if exist).
	 * @param x This value normally is 0.
	 * @param y This value normally is 0.
	 * @param width This value is 1024 for example.
	 * @param height This value is 768 for example.
	 */
	void injectViewport(int x, int y, int width, int height);
	
	/**
	 * Informs the EasyFramework about mouse hover events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @see GuiManager
	 */
	void injectMouseHover(int x, int y);
	
	/**
	 * Informs the EasyFramework about mouse left click events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 * @see GuiManager
	 */
	void injectMouseLeftClick(int x, int y, bool pressed = true);
	
	/**
	 * Informs the EasyFramework about mouse right click events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 * @see GuiManager
	 */
	void injectMouseRightClick(int x, int y, bool pressed = true);
	
	/**
	 * Informs the EasyFramework about mouse middle click events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param x The actual x coordinate of the mouse in the opengl viewport. 0 is on the left.
	 * @param y The actual y coordinate of the mouse in the opengl viewport. 0 is on bottom.
	 * @param pressed True if the mouse button is pressed, false if released.
	 * @see GuiManager
	 */
	void injectMouseMiddleClick(int x, int y, bool pressed = true);
	
	/**
	 * Informs the EasyFramework about mouse wheel events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param ticks A positive value means wheel up, a negative value means wheel down.
	 */
	void injectMouseWheel(char ticks);
	
	/**
	 * Informs the EasyFramework about key press events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param key @TODO
	 */
	void injectKeyPress(unsigned char key);

	/**
	 * Informs the EasyFramework about key release events globaly.
	 * This informations will be redirect to the GuiManager (if exist).
	 * @param key @TODO
	 */
	void injectKeyRelease(unsigned char key);

	
	/**
	 * Static member method checks if there is currently a context.
	 * @return Returns true if there is currently a context, else false.
	 */
	static bool isContext();
	
	/**
	 * Static member method to get the current Context pointer.
	 * @code // Example
	 * ... // context has been initialized
	 * 
	 * Context *context = new Context;
	 * ...
	 * if (Context::isContext() )
	 *     context = Context::getCurrentContext();
	 * ...
	 * ModelManager *modelManager = context->getModelManager();
	 * PhysicManager *physicManager = context->getPhysicManager();
	 * ...
	 * @endcode
	 * 
	 * @return A pointer to the current context. If there is no context, a new
	 * context will be create.
	 */
	static Context* getCurrentContext();

	/**
	 * Resets the context. All managed in the managers will be deleted. Performs 
	 * the clear method to all existing managers. The managers itself will not delete.
	 * The xml entries in the xml manager will deleted too.
	 */
	void reset();

	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;

	// Sorts the managers in right update order. It concerns only the active manager list.
	// XmlManager will be ignored.
	void reorderManager();

private:

	
	// --- Manager RcPtr holder ---
	
#ifndef NO_VSPH
	base::util::RcPtr<managed::ph::PhysicManager> physicManager;
	
	void checkCurrentPhysicManager();
#endif
	
#ifndef NO_VSGL
	base::util::RcPtr<managed::gl::OpenGlManager> openGlManager;
	
	void checkCurrentOpenGlManager();
	
	base::util::RcPtr<managed::gl::model::ModelManager> modelManager;
	
	void checkCurrentModelManager();
	
	base::util::RcPtr<managed::gl::AnimationManager> animationManager;
	
	void checkCurrentAnimationManager();
#endif

#ifndef NO_VSPG
	base::util::RcPtr<managed::plug::PluginManager> pluginManager;
	
	void checkCurrentPluginManager();
#endif

	base::util::RcPtr<managed::UpdateableManager> updateableManager;
	
	void checkCurrentUpdateableManager();

#ifndef NO_VSAL
	base::util::RcPtr<managed::al::SoundManager> soundManager;
	
	void checkCurrentSoundManager();
#endif

#ifndef NO_VSCT
	base::util::RcPtr<constr::ConstraintManager> constraintManager;
	
	void checkCurrentConstraintManager();
#endif
	
#ifndef NO_VSGUI
	base::util::RcPtr<managed::gui::GuiManager> guiManager;
	
	void checkCurrentGuiManager();
#endif

#ifndef NO_VSXL
	base::util::RcPtr<base::xml::XmlManager> xmlManager;
	
	void checkCurrentXmlManager();
	
	//void makeStdXmlTagsKnown(base::xml::XmlManager *manager);
#endif

	base::cont::List<base::interfaces::ManagerInterface *> activeList;
	base::cont::List<base::interfaces::ManagerInterface *> inactiveList;

};

} // vs

#endif	// CONTEXT_H
