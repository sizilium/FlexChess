/**
 * @file ModelLoader.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VSGL_MODEL_HEADER
#define VSGL_MODEL_HEADER

// includes
#include <vs/Build.hpp>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <GL/gl.h>
#include <vs/core/gl/model/ModelVisitorInterface.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

using namespace std;

/**
 * A ModelVisitor to load a model file and create the data containers accordingly.
 * OpenGL has to be initialized before you can use this class.
 * It is implemented as a ModelVisitor (@see ModelVisitorInterface)
 */
class VS_EXPORT ModelLoader : public ModelVisitorInterface
{
protected:
	string filename;
	ifstream modelFile;
	bool textured;

	static const char END_CHAR;

	void visit(ModelData &model);
	void visit(ObjectData &object);
	void visit(FaceGroupData &faces);
	void visit(VertexData &vertex);

public:

	/**
	 * Loads the model data into the data container.
	 *
	 * @param filename
	 * Model file to load.
	 * @param model
	 * Container where all data should be stored in.
	 *
	 * @throw ex::FileException
	 */
	void load(const string &filename, ModelData &model);
};

void fileGood(string &filename, ifstream &file);

} // model
} // gl
} // core
} // vs


#endif
