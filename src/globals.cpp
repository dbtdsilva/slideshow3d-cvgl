/*
 * globals.cpp
 *
 * Implementação de tipos e variaveis globais.
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "globals.hpp"

using namespace std;

projCoord proj;
int windowHandle;
GLuint programaGLSL;
GLuint vs, fs;
GLint attribute_coord3d, attribute_texcoord;
mat4x4 matrizProj, matrizModelView;

GraphicModel * skybox;
bool animationActive;
