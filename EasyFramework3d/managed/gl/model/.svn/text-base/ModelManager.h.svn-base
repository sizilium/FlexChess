/**
 * @file ModelManager.h
 * @author maccesch
 * @date 28.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELMANAGER_H_
#define MODELMANAGER_H_

#define DEFAULT_CLICK_REGION 3
#define DEFAULT_FOV_Y 45
#define DEFAULT_Z_NEAR 0.1
#define DEFAULT_Z_FAR 1000
#define DEFAULT_BUFFER_SIZE 512

// includes
#include <vs/Build.hpp>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <GL/gl.h>

#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/managed/gl/model/ModelManager.h>
#include <vs/base/util/IDGenerator.hpp>
#include <vs/core/gl/Color.h>
// #include <vs/core/gl/Camera.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/base/cont/List.hpp>
#include <vs/base/interfaces/MsgObservable.hpp>

namespace vs {
// predeclarations
namespace core {
namespace gl {
class Camera;
}
}

namespace managed {
namespace gl {
namespace model {
// predeclarations
class ManagedModel;
class ManagedModelBinder;

using namespace std;

// TODO document default parameter for ModelManager
class VS_EXPORT ModelManager : public base::interfaces::AbstractManager<ModelManager>,
	public base::interfaces::MsgObservable<unsigned int> {
private:
	friend class ManagedModel;
	friend class ManagedModelBinder;
	friend class ModelFactory;

	typedef list<GLuint> uilist;

	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as rotation.
	 * For details see the code of printRenderQueue().
	 */
	static const int ROTATION;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as translation.
	 * For details see the code of printRenderQueue().
	 */
	static const int TRANSLATION;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as scalation.
	 * For details see the code of printRenderQueue().
	 */
	static const int SCALATION;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that glPushMatrix() has to be called.
	 * For details see the code of printRenderQueue().
	 */
	static const int PUSH;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that glPopMatrix() has to be called.
	 * For details see the code of printRenderQueue().
	 */
	static const int POP;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as model data
	 * until DRAW_END is found. For details see the code of printRenderQueue().
	 */
	static const int DRAW;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the model data ends. To every DRAW belongs one DRAW_END.
	 * For details see the code of printRenderQueue().
	 */
	static const int DRAW_END;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as color.
	 * For details see the code of printRenderQueue().
	 */
	static const int COLOR;
	/**
	 * Operation constant in the renderQueue.
	 * It tells the renderQueue traverser that the successing data should be interpreted as euler.
	 * For details see the code of printRenderQueue().
	 */
	static const int EULER;

	// only opaque model are handled so far

	// all the unsigned ints here refer to ids (= indices)
	map<unsigned int, uilist> models2textures; // model -> textures
	// TODO : is there only one display list per (model, texture)-pair ?
	map<pair<unsigned int, GLuint>, uilist> modelsTex2displayLists; // model, textures -> display lists
	map<unsigned int, uilist> models2untexturedDLists; // model -> untextured display lists

	// textures -> last occurence in the renderQueue
	map< unsigned int, list<double>::iterator> textures2lastOccur;

	// variables for loading purposes only
	//	unsigned int displayListNumber; // number of display lists
	map<string, list<unsigned int> > textureNames2models; // texture names -> model
	map<string, unsigned int> texNames2texIds;
	map<string, vector<unsigned int> > filenames2models;
	map<pair<string, string>, unsigned int> objNamesFilenames2models;
	map<unsigned int, base::math::DoubleVector> models2centers;
	map<unsigned int, base::math::DoubleVector> models2rotations;
	map<unsigned int, base::math::DoubleVector> models2sizes;
	map<unsigned int, core::gl::Color> models2colors;

	/// In this field translations, rotations, pushs, pops, draws, etc are queued
	/// for drawing. It is traversed and drawn by drawQueue().
	/// For the structure of the renderQueue see the source code of printRenderQueue()
	list<double> renderQueue;

	/// When a texture in the renderQueue has been drawn its directly successing value
	/// is set to the same value as this field. It is flipping 0 and 1
	/// every time drawQueue() is called.  
	char renderedFlag;

	base::util::IDGenerator<unsigned int> modelIdGen;

	base::cont::List<base::interfaces::AbstractManaged *> managedModels;

	bool texturedEnabled; ///< true, when textured geometry is to be drawn 
	bool untexturedEnabled; ///< true, when untextured geometry is to be drawn

	/// Its value is flipped every time update() is called to minimize OpenGL
	/// state changes. See the source code of update() for details.
	bool texturedFlip;

	/**
	 * Draws all geometry in the render queue.
	 * @param[in] textured If true only textured geometry is drawn, only untextured otherwise.
	 * @param[in] drawingModes Only models that are activated for the drawing modes specified by this
	 * parameter are drawn. The modes are specified as bit flags. Possible values are:
	 * DRAWING_MODE_DEFAULT, DRAWING_MODE_PICKING
	 * @param[in] texImportant If false the parameter textured isn't considered.
	 * So textured and untextured geometry is drawn, but both without texture.
	 * This is useful for example when drawing for Picking.
	 */
	void drawQueue(bool textured,
			unsigned int drawingModes = DRAWING_MODE_DEFAULT,
			bool texImportant = true);
	/**
	 * Enqueues a value to the end of renderQueue
	 * @param[in] value The value to enqueue.
	 */
	void enqueue(double value);
	/**
	 * See AbstracManager::addManaged()
	 */
	void addManaged(base::interfaces::AbstractManaged *managed) {
		managedModels.add(managed);
	}

	/** 
	 * Take care of internal texturedFlip initialization.
	 * When textured and untextured geometry gets enabled update() begins to take
	 * care of the textured state of OpenGL. This method ensures that this state
	 * is correctly initialised.
	 */
	inline void bothEnabled();

	/**
	 * Does the actual work for removeManaged(const string &name).
	 * @param[in] name See removeManaged(const string &name)
	 * @param[in] deleteTextured If true is passed the ManagedModel object 
	 * will be deleted from the heap. Otherwise it won't.
	 * @see base::interfaces::ManagerInterface::removeManaged()
	 */
	void removeManaged(const string &name, bool deleteTextured);

	/**
	 * Removes all textures for an model object.
	 * @param[in] objId The id of the object to be removed.
	 */
	void removeTextures(unsigned int objId);

	/**
	 * Draws all untextured display lists for the model object.
	 * @param[in] model Id of the model object to be drawn.
	 */
	inline void drawUntexturedDLists(unsigned int model);
	/**
	 * Draws all textured display lists for the model object with the given texture.
	 * @param[in] model Id of the model object to be drawn.
	 * @param[in] texture Id of the texture.
	 */
	inline void drawTexturedDLists(unsigned int model, int texture);

	/**
	 * Processes the picking hit records. The model object id with has the hit record
	 * with the nearest z value is considered to be clicked. Observers are notified with
	 * this model object id.
	 * @param[in] hits Number of hit records.
	 * @param[in] selectionBuffer Buffer where the hit records are stored in.
	 */
	void processPickingHits(GLint hits, GLuint selectionBuffer[]);

public:
	// TODO! : documents these right:
	/// This flag is passed to drawQueue() as the default drawing mode (to screen).
	static const unsigned int DRAWING_MODE_DEFAULT;
	/// this flag is passed to drawQueue() when models activated for picking are to be drawn
	static const unsigned int DRAWING_MODE_PICKING;

	ModelManager();
	virtual ~ModelManager();

	// TODO implements ManagerInterface interfacess ...

	/**
	 * Draws all models that are managed by this manager and are activated.
	 * @warning If textured and untextured models are both disabled, nothing will
	 * be displayed.
	 * @see disableTextured(), disableUntextured()
	 */
	void update(double time = 0);

	/**
	 * Draws all for picking activated geometry and notifies picking observers
	 * (by calling processPickingHits()).
	 * @param[in] mouseX X-coordinate of the mouse cursor (in window coordinates).
	 * @param[in] mouseY Y-coordinate of the mouse cursor (in window coordinates).
	 * @param[in] pov Point of view. Passed as the first three arguments to gluLookAt().
	 * @param[in] lookAt Point to look at. Passed as the fourth to sixth argument to gluLookAt().
	 * @param[in] up Vector that points up. Passed as the seventh to nineth argument to gluLookAt().
	 * @param[in] clickRegion Number of pixels of the side length of the picking area
	 * around the mouse cursor. The larger it is the less accurate one must aim to
	 * hit an object and the more objects will be hit (slowing down hit processing).
	 * @param[in] fovy Angle of the field of view in y direction.
	 * @param[in] zNear Minimum distance from the point of view to start drawing
	 * (i.e. considering objects for picking). It has to be larger than zero.
	 * @param[in] zFar Maximum distance from the point of view to start drawing
	 * (i.e. considering objects for picking).
	 * @param[in] bufferSize Size of the buffer (in GLuints) where the hit records are to be stored in.
	 * @note Before you call this method you have to activate picking (ManagedModel::activatePicking())
	 * for the model objects you want to be pickable.
	 */
	void performPicking(int mouseX, int mouseY,
			const base::math::DoubleVector &pov,
			const base::math::DoubleVector &lookAt,
			const base::math::DoubleVector &up,
			short clickRegion = DEFAULT_CLICK_REGION,
			GLdouble fovy = DEFAULT_FOV_Y, GLdouble zNear = DEFAULT_Z_NEAR,
			GLdouble zFar = DEFAULT_Z_FAR,
			unsigned int bufferSize = DEFAULT_BUFFER_SIZE);

	/**
	 * Draws all for picking activated geometry and notifies picking observers
	 * (by calling processPickingHits()). This is a convenience method.
	 * @param[in] mouseX X-coordinate of the mouse cursor (in window coordinates).
	 * @param[in] mouseY Y-coordinate of the mouse cursor (in window coordinates).
	 * @param[in] clickRegion Number of pixels of the side length of the picking area
	 * around the mouse cursor. The larger it is the less accurate one must aim to
	 * hit an object and the more objects will be hit (slowing down hit processing).
	 * @param[in] bufferSize Size of the buffer (in GLuints) where the hit records are to be stored in.
	 * @note Before you call this method you have to activate picking (ManagedModel::activatePicking())
	 * for the model objects you want to be pickable.
	 * @see performPicking(int mouseX, int mouseY, const base::math::DoubleVector &pov,
	 * const base::math::DoubleVector &lookAt,
	 * const base::math::DoubleVector &up,
	 * short clickRegion = DEFAULT_CLICK_REGION,
	 * GLdouble fovy = DEFAULT_FOV_Y, GLdouble zNear = DEFAULT_Z_NEAR,
	 * GLdouble zFar = DEFAULT_Z_FAR,
	 * unsigned int bufferSize = DEFAULT_BUFFER_SIZE)
	 */
	void performPicking(int mouseX, int mouseY, core::gl::Camera *camera,
			short clickRegion = DEFAULT_CLICK_REGION,
			unsigned int bufferSize = DEFAULT_BUFFER_SIZE);

	/**
	 * Enables drawing of textured geometry.
	 */
	void enableTextured() {
		texturedEnabled = true;
		bothEnabled();
	}
	/**
	 * Disables drawing of textured geometry.
	 */
	void disableTextured() {
		texturedEnabled = false;
	}
	/**
	 * Enables drawing of untextured geometry.
	 */
	void enableUntextured() {
		untexturedEnabled = true;
		bothEnabled();
	}
	/**
	 * Disables drawing of untextured geometry.
	 */
	void disableUntextured() {
		untexturedEnabled = false;
	}

	/**
	 * See base::interfaces::ManagerInterface::getManagedNames()
	 */
	void getManagedNames(base::cont::JavaStyleContainer<string> * names) const;

	/**
	 * See base::interfaces::ManagerInterface::getManaged()
	 */
	base::interfaces::AbstractManaged* getManaged(const string &name) const;

	/**
	 * Only calls removeManaged(name, true)
	 * @see base::interfaces::ManagerInterface::removeManaged()
	 * @see removeManaged(const string &name, bool deleteManaged)
	 */
	void removeManaged(const string &name);

	/**
	 * Returns the name of the manager.
	 * @return The managers name.
	 */
	std::string getName() const {
		return "ModelManager";
	}

	/**
	 * This method clears all managed from the manager.
	 */
	void clear();

	/**
	 * Prints some information about the manager to std console.
	 */
	void outDebug() const;

	// TODO! : add optional parameter: iterator to renderQueue where the values are to be enqueued.
	void enqueueTranslation(double x, double y, double z);
	void enqueueRotation(double angle, double x, double y, double z);
	void enqueueEuler(double angle_x, double angle_y, double angle_z);
	// TODO : either only size or only scale
	void enqueueScalation(double x, double y, double z);
	void enqueueColor(double r, double g, double b, double a);
	inline void enqueuePush();
	inline void enqueuePop();
	inline void enqueueDraw(unsigned int modelId);
	inline void emptyQueue();

	// comfort methods
	inline void enqueueTranslation(const base::math::DoubleVector &v);
	inline void
			enqueueRotation(double angle, const base::math::DoubleVector &v);
	inline void enqueueEuler(const base::math::DoubleVector &euler);
	inline void enqueueScalation(const base::math::DoubleVector &s);
	inline void enqueueColor(const core::gl::Color &c);

	// TODO! : use either only model id or only object id!
	base::math::DoubleVector &getModelCenter(unsigned int model) {
		return models2centers[model];
	}
	base::math::DoubleVector &getModelEuler(unsigned int model) {
		return models2rotations[model];
	}
	base::math::DoubleVector &getModelSize(unsigned int model) {
		return models2sizes[model];
	}
	core::gl::Color &getModelColor(unsigned int model) {
		return models2colors[model];
	}

#ifndef NDEBUG
	void printRenderQueue() const;
#endif
};

inline void ModelManager::enqueueColor(double r, double g, double b, double a) {
	enqueue(COLOR);
	enqueue(r);
	enqueue(g);
	enqueue(b);
	enqueue(a);
}

inline void ModelManager::enqueueTranslation(double x, double y, double z) {
	enqueue(TRANSLATION);
	enqueue(x);
	enqueue(y);
	enqueue(z);
}

inline void ModelManager::enqueueRotation(double angle, double x, double y,
		double z) {
	enqueue(ROTATION);
	enqueue(angle);
	enqueue(x);
	enqueue(y);
	enqueue(z);
}

inline void ModelManager::enqueueScalation(double x, double y, double z) {
	enqueue(SCALATION);
	enqueue(x);
	enqueue(y);
	enqueue(z);
}

inline void ModelManager::enqueueEuler(double angle_x, double angle_y,
		double angle_z) {
	enqueue(EULER);
	enqueue(angle_x);
	enqueue(angle_y);
	enqueue(angle_z);
}

inline void ModelManager::enqueuePush() {
	enqueue(PUSH);
}

inline void ModelManager::enqueuePop() {
	enqueue(POP);
}

inline void ModelManager::enqueueDraw(unsigned int model) {
	enqueue(DRAW);
	// add drawing flags (default is default)
	enqueue(DRAWING_MODE_DEFAULT);
	enqueue(model);
	// TODO : das hier nach drawQueue verschieben?
	uilist &modelTextures = models2textures[model];
	for (uilist::iterator texIt = modelTextures.begin(); texIt
			!= modelTextures.end(); ++texIt) {
		enqueue(*texIt);
		enqueue(1 - renderedFlag); // add the drawn flag (initially false of course)
		textures2lastOccur[*texIt] = --renderQueue.end();
	}
	enqueue(DRAW_END);
}

inline void ModelManager::emptyQueue() {
	// TODO optimize
	renderQueue.clear();
}

inline void ModelManager::enqueue(double value) {
	// TODO optimize
	renderQueue.push_back(value);
}

inline void ModelManager::bothEnabled() {
	if (texturedEnabled && untexturedEnabled) {
		texturedFlip = true;
		glEnable(GL_TEXTURE_2D);
	}
}

inline void ModelManager::enqueueTranslation(const base::math::DoubleVector &v) {
	enqueueTranslation(const_cast<base::math::DoubleVector &>(v)[0], const_cast<base::math::DoubleVector &>(v)[1], const_cast<base::math::DoubleVector &>(v)[2]);
}

inline void ModelManager::enqueueRotation(double angle,
		const base::math::DoubleVector &v) {
	enqueueRotation(angle, const_cast<base::math::DoubleVector &>(v)[0], const_cast<base::math::DoubleVector &>(v)[1], const_cast<base::math::DoubleVector &>(v)[2]);
}

inline void ModelManager::enqueueScalation(const base::math::DoubleVector &s) {
	enqueueScalation(const_cast<base::math::DoubleVector &>(s)[0], const_cast<base::math::DoubleVector &>(s)[1], const_cast<base::math::DoubleVector &>(s)[2]);
}

inline void ModelManager::enqueueColor(const core::gl::Color &c) {
	enqueueColor(const_cast<core::gl::Color &>(c)[0], const_cast<core::gl::Color &>(c)[1], const_cast<core::gl::Color &>(c)[2], const_cast<core::gl::Color &>(c)[3]);
}

// rotate first around z, then y, then x
inline void ModelManager::enqueueEuler(const base::math::DoubleVector &euler) {
	enqueueEuler(const_cast<base::math::DoubleVector &>(euler)[0], const_cast<base::math::DoubleVector &>(euler)[1], const_cast<base::math::DoubleVector &>(euler)[2]);
}

inline void ModelManager::drawUntexturedDLists(unsigned int model) {
	uilist & dLists = models2untexturedDLists[model];
	for (uilist::iterator dlIt = dLists.begin(); dlIt != dLists.end(); ++dlIt) {
		glCallList(*dlIt);
	}
}

inline void ModelManager::drawTexturedDLists(unsigned int model, int texture) {
	uilist & dLists = modelsTex2displayLists[make_pair(model, texture)];
	for (uilist::iterator dlIt = dLists.begin(); dlIt != dLists.end(); ++dlIt) {
		glCallList(*dlIt);
	}
}

} // model
} // gl
} // managed
} // vs

#endif /*MODELMANAGER_H_*/
