#include <vs/managed/gl/model/ModelManager.h>
#include <vs/core/gl/model/ModelLoader.h>
#include <vs/core/gl/TextureManager.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/core/gl/model/TexNamesExtractor.h>
#include <sstream>
#include <vs/base/util/Exception.h>
#include <vs/base/util/FileException.h>
#include <vs/core/gl/GLException.h>
#include <vs/managed/gl/model/ManagedModelBinder.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/core/gl/model/ModelData.h>
#include "vs/core/gl/Camera.h"
using namespace vs::core::gl;

using namespace std;

namespace vs {
namespace managed {
namespace gl {
namespace model {

using namespace vs::base::math;
using namespace vs::base::util;
using namespace vs::base::cont;
using namespace vs::base::interfaces;
using namespace vs::core::gl::model;
using namespace vs::core::gl;

const int ModelManager::ROTATION = 1;
const int ModelManager::TRANSLATION = 2;
const int ModelManager::PUSH = 3;
const int ModelManager::POP = 4;
const int ModelManager::DRAW = 6;
const int ModelManager::DRAW_END = -6;
const int ModelManager::COLOR = 7;
const int ModelManager::SCALATION = 8;
const int ModelManager::EULER = 9;

const unsigned int ModelManager::DRAWING_MODE_DEFAULT = 1;
const unsigned int ModelManager::DRAWING_MODE_PICKING = 2;

ModelManager::ModelManager() :
	models2textures(), modelsTex2displayLists(), models2untexturedDLists(),
			textures2lastOccur(), textureNames2models(), texNames2texIds(),
			filenames2models(), objNamesFilenames2models(), models2centers(),
			models2rotations(), models2sizes(), models2colors(), renderQueue(),
			renderedFlag(1), modelIdGen(), managedModels(),
			texturedEnabled(true), untexturedEnabled(true), texturedFlip(false) {
}

ModelManager::~ModelManager() {
}

void ModelManager::update(double time) {

	if (texturedEnabled and untexturedEnabled)
	{
		// minimize OpenGL state changed. If textured and untextured
		// geometry is to be drawn, flip textured state only once per update

		//		drawQueue(texturedFlip);
		//
		//		texturedFlip = !texturedFlip;
		//		
		//		if (texturedFlip)
		//			glEnable(GL_TEXTURE_2D);
		//		else
		//			glDisable(GL_TEXTURE_2D);
		//
		//		drawQueue(texturedFlip);

		glEnable(GL_TEXTURE_2D);
		drawQueue(true);
		//glDisable(GL_TEXTURE_2D);
		//drawQueue(false);		// TODO problems by drawing untextured stuff
		// wenn untexturierte sachen gezeichnet werden, werden die 
		// texturierten sachen nicht mehr gezeichnet.
		// au�erdem fehlt die farbe bei untextrurierten sachen...
	}
	else
	{
		if (texturedEnabled)
		{
			glEnable(GL_TEXTURE_2D);
			drawQueue(true);
		}
		else if (untexturedEnabled)
		{
			drawQueue(false);
		}
	}

}

void ModelManager::drawQueue(bool textured, unsigned int drawingModes,
		bool texImportant) {
	int matrixStackHeight = 0;

	list<double>::iterator lastZeroStack = renderQueue.begin();
	list<double>::iterator lastTextureOccur;
	list<double>::iterator tempIt;

	int nextTexture = -1;
	list<double>::iterator nextStart = renderQueue.end();

	list<double>::iterator renderIt = renderQueue.begin();
	int currentTexture = -1;

	double x, y, z, angle;

	glPushMatrix();

	while (renderIt != renderQueue.end()) {
		switch (static_cast<unsigned int>(*renderIt)) {
		case PUSH:
			glPushMatrix();
			matrixStackHeight++;
			++renderIt;
			break;

		case POP:
			glPopMatrix();
			matrixStackHeight--;
			// TODO:advanced stack logic
			++renderIt;
			if (matrixStackHeight == 0)
				lastZeroStack = renderIt;
			break;

		case TRANSLATION:
			x = *(++renderIt);
			y = *(++renderIt);
			z = *(++renderIt);
			glTranslatef(x, y, z);
			++renderIt;
			break;

		case ROTATION:
			angle = *(++renderIt);
			x = *(++renderIt);
			y = *(++renderIt);
			z = *(++renderIt);
			glRotatef(angle, x, y, z);
			++renderIt;
			break;

		case SCALATION:
			x = *(++renderIt);
			y = *(++renderIt);
			z = *(++renderIt);
			glScalef(x, y, z);
			++renderIt;
			break;

		case COLOR:
			// abuse veriables (x = red, y = green, z = blue, angle = alpha)
			x = *(++renderIt);
			y = *(++renderIt);
			z = *(++renderIt);
			angle = *(++renderIt);
			glColor4f(x, y, z, angle);
			++renderIt;
			break;
		case EULER:
			// x, y, z are alle angles around these axes
			x = *(++renderIt);
			y = *(++renderIt);
			z = *(++renderIt);
			glRotatef(z, 0.0f, 0.0f, 1.0f);
			glRotatef(y, 0.0f, 1.0f, 0.0f);
			glRotatef(x, 1.0f, 0.0f, 0.0f);
			++renderIt;
			break;

		case DRAW:
			// TODO : move this case to its own method
			unsigned int queuedDrawingModes =
					static_cast<unsigned int>(*(++renderIt));
			if (drawingModes & queuedDrawingModes) {
				unsigned int model = static_cast<unsigned int>(*(++renderIt));

				if (drawingModes & DRAWING_MODE_PICKING) {
					glLoadName(model);
				}

				if (!texImportant) {
					drawUntexturedDLists(model);

					// iterate through the textures
					++renderIt;
					while (*renderIt != DRAW_END) {
						currentTexture = static_cast<GLuint>(*renderIt);
						drawTexturedDLists(model, currentTexture);
						++renderIt; // skip renderedFlag
						++renderIt;
					}
					++renderIt;
					break;
				}

				if (!textured) {
					drawUntexturedDLists(model);
					while (*renderIt != DRAW_END) {
						++renderIt;
					}
					++renderIt;
					break;
				}

				// if textured:
				++renderIt;
				while (*renderIt != DRAW_END) {
					if (currentTexture < 0) {
						currentTexture = static_cast<GLuint>(*renderIt);
						// texture already drawn?
						tempIt = renderIt;
						++tempIt;
						if (*tempIt == renderedFlag) {
							++renderIt;
							++renderIt;
							currentTexture = -1;
							continue;
						}
						lastTextureOccur = textures2lastOccur[currentTexture];
						glBindTexture(GL_TEXTURE_2D, currentTexture);
					}
					if (*renderIt == currentTexture) {
						drawTexturedDLists(model, currentTexture);
						// mark as drawn
						++renderIt;
						*renderIt = renderedFlag;

						if (renderIt == lastTextureOccur) {
							if (nextTexture >= 0) {
								// TODO : matrix stack emptying with advanced logic (see above)
								while (matrixStackHeight > 0) {
									glPopMatrix();
									matrixStackHeight--;
								}
								glPopMatrix();
								glPushMatrix();

								renderIt = nextStart;
								currentTexture = nextTexture;
								nextTexture = -1;
								nextStart = renderQueue.end();
								lastTextureOccur
										= textures2lastOccur[currentTexture];
								glBindTexture(GL_TEXTURE_2D, currentTexture);
								break;
							} else {
								currentTexture = -1;
							}
						}
					} else {
						// remember where to start next and what is the next texture
						if (nextTexture < 0) {
							// has this texture already been drawn?
							tempIt = renderIt;
							++tempIt;
							if (*tempIt != renderedFlag) {
								nextTexture = static_cast<GLuint>(*renderIt);
								nextStart = lastZeroStack;
							}
						}

						// omit drawn flag
						++renderIt;
					}

					++renderIt;
				}
				if (*renderIt == DRAW_END)
					++renderIt;
				break;
			}
		}
	}

	glPopMatrix();

	renderedFlag = 1 - renderedFlag;

}

void ModelManager::outDebug() const {
#ifndef NDEBUG
	printRenderQueue();
#endif // NDEBUG
}

#ifndef NDEBUG
void ModelManager::printRenderQueue() const {
	for (list<double>::const_iterator renderIt = renderQueue.begin(); renderIt
			!= renderQueue.end(); ++renderIt) {
		unsigned int model;
		unsigned int queuedDrawingModes;
		switch (static_cast<unsigned int>(*renderIt)) {
		case PUSH:
			cout << PUSH << " (PUSH)" << endl;
			break;

		case POP:
			cout << POP << " (POP)" << endl;
			break;

		case TRANSLATION:
			cout << TRANSLATION << " (TRANSLATION):" << endl;

			cout << "\tx = " << *(++renderIt) << endl;
			cout << "\ty = " << *(++renderIt) << endl;
			cout << "\tz = " << *(++renderIt) << endl;
			break;

		case ROTATION:
			cout << ROTATION << " (ROTATION):" << endl;

			cout << "\tangle = " << *(++renderIt) << endl;
			cout << "\tx = " << *(++renderIt) << endl;
			cout << "\ty = " << *(++renderIt) << endl;
			cout << "\tz = " << *(++renderIt) << endl;
			break;

		case SCALATION:
			cout << SCALATION << " (SCALATION):" << endl;

			cout << "\tx = " << *(++renderIt) << endl;
			cout << "\ty = " << *(++renderIt) << endl;
			cout << "\tz = " << *(++renderIt) << endl;
			break;

		case EULER:
			cout << EULER << " (EULER - rotates first z, then y, then x):"
					<< endl;

			cout << "\tangle_x = " << *(++renderIt) << endl;
			cout << "\tangle_y = " << *(++renderIt) << endl;
			cout << "\tangle_z = " << *(++renderIt) << endl;
			break;

		case COLOR:
			cout << COLOR << " (COLOR):" << endl;

			cout << "\tr = " << *(++renderIt) << endl;
			cout << "\tg = " << *(++renderIt) << endl;
			cout << "\tb = " << *(++renderIt) << endl;
			cout << "\ta = " << *(++renderIt) << endl;
			break;

		case DRAW:
			cout << DRAW << " (DRAW):" << endl;

			queuedDrawingModes = static_cast<unsigned int>(*(++renderIt));
			cout << "\tdrawingModes = " << queuedDrawingModes << " [" << endl;
			if (queuedDrawingModes & DRAWING_MODE_DEFAULT)
				cout << "\t\tDRAWING_MODE_DEFAULT = " << DRAWING_MODE_DEFAULT
						<< endl;
			if (queuedDrawingModes & DRAWING_MODE_PICKING)
				cout << "\t\tDRAWING_MODE_PICKING = " << DRAWING_MODE_PICKING
						<< endl;
			cout << "\t]" << endl;

			model = static_cast<unsigned int>(*(++renderIt));
			cout << "\tmodel = " << model << endl;
			cout << endl;

			++renderIt;
			while (*renderIt != DRAW_END) {
				cout << "\t\ttexture = " << static_cast<GLuint>(*renderIt)
						<< endl;
				++renderIt;
				cout << "\t\trendered = " << *renderIt << " (=";
				if ((*renderIt) == renderedFlag)
					cout << "true";
				else
					cout << "false";
				cout << ")" << endl;
				++renderIt;
				cout << endl;
			}
			cout << DRAW_END << " (DRAW_END)" << endl;
			break;

		default:
			cout << (*renderIt) << "(renderQueue disrupted!)" << endl;
			break;
		}
	}
}
#endif // NDEBUG
void ModelManager::clear() {
	models2textures.clear();
	modelsTex2displayLists.clear();
	models2untexturedDLists.clear();
	textures2lastOccur.clear();
	//	displayListNumber = 0;
	textureNames2models.clear();
	texNames2texIds.clear();
	filenames2models.clear();
	objNamesFilenames2models.clear();
	models2centers.clear();
	models2rotations.clear();
	models2sizes.clear();
	models2colors.clear();
	renderQueue.clear();
	renderedFlag = 1;

	// TODO! delete in ModelManager::clear() occurs a pointer error!
	//	List<AbstractManaged *>::Iterator it;
	//	for (it = managedModels.begin(); it != managedModels.end(); ++it)
	//	{
	//		delete *it;
	//		managedModels.erase(it);
	//	}
}

void ModelManager::removeManaged(const string &name) {
	removeManaged(name, true);
}

void ModelManager::removeTextures(unsigned int objId) {
	// remove all texture stuff
	uilist textures = models2textures[objId];
	uilist::iterator texIt;
	for (texIt = textures.begin(); texIt != textures.end(); ++texIt) {
		modelsTex2displayLists.erase(make_pair(objId, *texIt));

		// get texture name of *texIt
		map<string,list<unsigned int> >::iterator texNamesIt;
		for (texNamesIt = textureNames2models.begin(); texNamesIt
				!= textureNames2models.end(); ++texNamesIt) {
			list<unsigned int> & objIds = texNamesIt->second;

			list<unsigned int>::iterator objIt;
			for (objIt = objIds.begin(); objIt != objIds.end(); ++objIt) {
				if (*objIt == objId)
					break;
			}
			if (objIt != objIds.end())
				objIds.erase(objIt);

			// if no objects are using the texture anymore, remove it completely
			if (objIds.empty()) {
				textures2lastOccur.erase(*texIt);
				textureNames2models.erase(texNamesIt->first);
				texNames2texIds.erase(texNamesIt->first);
			}

		}
	}

	models2textures.erase(objId);
}

void ModelManager::removeManaged(const string &name, bool deleteManaged) {
	List<AbstractManaged *>::Iterator it = managedModels.begin();
	ManagedModel *managedModel;
	while (it != managedModels.end()) {
		if (name == (*it)->getName())
			break;
	}
	managedModel = dynamic_cast<ManagedModel *>(*it);
	if (managedModel->isActive())
		managedModel->deactivate();

	string modelpath = managedModel->getPath();

	// get object names and ids of the model
	list<pair<string, unsigned int> > objNamesIds;
	map<pair<string, string>, unsigned int>::iterator objNameMapIt;
	for (objNameMapIt = objNamesFilenames2models.begin(); objNameMapIt
			!= objNamesFilenames2models.end(); ++objNameMapIt) {
		if (objNameMapIt->first.second == modelpath)
			objNamesIds.push_back(make_pair(objNameMapIt->first.first,
					objNameMapIt->second));

	}

	// remove all objects of the model from the manager
	list<pair<string, unsigned int> >::iterator objNameListIt;
	for (objNameListIt = objNamesIds.begin(); objNameListIt
			!= objNamesIds.end(); ++objNameListIt) {
		string &objName = objNameListIt->first;
		unsigned int objId = objNameListIt->second;
		objNamesFilenames2models.erase(make_pair(objName, modelpath));

		models2rotations.erase(objId);
		models2sizes.erase(objId);
		models2centers.erase(objId);
		models2colors.erase(objId);

		models2untexturedDLists.erase(objId);

		removeTextures(objId);
	}

	filenames2models.erase(modelpath);

	if (deleteManaged)
		delete (*it);
	managedModels.erase(it);
}

void ModelManager::getManagedNames(JavaStyleContainer<string> *names) const {
	List<AbstractManaged *>::Const_Iterator it = managedModels.begin();
	while (it != managedModels.end()) {
		names->add((*it)->getName());
	}
}

AbstractManaged* ModelManager::getManaged(const string &name) const {
	List<AbstractManaged *>::Const_Iterator it = managedModels.begin();
	while (it != managedModels.end()) {
		if (name == (*it)->getName())
			return (*it);
	}
	return NULL;
}

void ModelManager::processPickingHits(GLint hits, GLuint selectionBuffer[]) {
	GLuint currentNamesNo;
	GLuint *ptr;
	GLuint *resultHitRecord= NULL;
	GLuint resultNamesNo;
	GLuint minZ = 0xffffffff;

	// search for the hit record with minimal z value
	ptr = static_cast<GLuint *>(selectionBuffer);
	for (int i = 0; i < hits; i++) {
		currentNamesNo = *ptr;
		++ptr;
		if (*ptr < minZ) {
			resultNamesNo = currentNamesNo;
			minZ = *ptr;
			resultHitRecord = ptr + 2;
		}

		// proceed to the next hit record assuming that there is only one name in the stack
		// (see drawQueue())
		ptr += currentNamesNo + 2;
		// TODO : this may not be thread safe: if the call to performPicking is finished before the Observer (in another thread) isn't executed, this memory is freed (loose reference!)
		notify(static_cast<unsigned int &>(*resultHitRecord));
	}

}

void ModelManager::performPicking(int mouseX, int mouseY, Camera *camera,
		short clickRegion, unsigned int bufferSize) {
	
	performPicking(mouseX, mouseY, camera->getPositionRef().getCoords(), camera->getLookAtRef().getCoords(),
			camera->getUpVecRef(), clickRegion, camera->fovy(), camera->zNear(), camera->zFar(), bufferSize);
}

void ModelManager::performPicking(int mouseX, int mouseY,
		const DoubleVector &pov, const DoubleVector &lookAt,
		const DoubleVector &up, short clickRegion, GLdouble fovy,
		GLdouble zNear, GLdouble zFar, unsigned int bufferSize) {

	GLuint selectionBuffer[bufferSize];
	GLint viewport[4];

	// init picking mode
	glSelectBuffer(bufferSize, selectionBuffer);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// set up the projection matrix for picking
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(mouseX, viewport[3]-mouseY, clickRegion, clickRegion,
			viewport);

	gluPerspective(fovy, static_cast<double>(viewport[2]-viewport[0])
			/ (viewport[3]-viewport[1]), zNear, zFar);

	camera->update();

	glMatrixMode(GL_MODELVIEW);
	glInitNames();

	// push dummy name in order to use glLoadName instead of glPopName and glPushName
	glPushName(0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	drawQueue(true, DRAWING_MODE_PICKING, false);

	int hits;

	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);

	// if there are hits process them
	if (hits != 0) {
		cout << "hit! goto processPickingHits() ... " << hits << endl;
		processPickingHits(hits, selectionBuffer);
	}
}

} // model
} // gl
} // managed
} // vs
