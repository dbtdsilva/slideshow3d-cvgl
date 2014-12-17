/*
 * globals.hpp
 *
 * Declaracao de tipos e variaveis globais.
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include "utils/mathUtils.hpp"
#include "models/graphicmodel.hpp"

using namespace std;

struct projCoord {
	float fovy;
	float aspect_ratio;
	float near_plane;
	float far_plane;
};

static string projectPath = "../src/";
extern projCoord proj;
extern int windowHandle;
extern GLuint programaGLSL;
extern GLuint vs, fs;
extern GLint attribute_coord3d, attribute_texcoord;
extern mat4x4 matrizProj, matrizModelView;

extern vector<GraphicModel*> ss_images;
extern bool animationActive;
#endif
