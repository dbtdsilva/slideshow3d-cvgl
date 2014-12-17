/*
 * models.hpp
 *
 * Ficheiro cabecalho do modulo MODELS.
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */


#ifndef _models_h
#define _models_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void lerVerticesDeFicheiro(string nome, int *numVertices, vector<float> *arrayVertices, 
										vector<float> *arrayTextures, vector<float> *arrayNormais = NULL);
void escreverVerticesEmFicheiro(string nome, int numVertices, GLfloat *arrayVertices);
GLuint loadImage(string imagepath, Mat * image);
GLfloat *calcularNormaisTriangulos(int numVertices, GLfloat *arrayVertices);

#endif
