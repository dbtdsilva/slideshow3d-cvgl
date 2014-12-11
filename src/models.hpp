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

using namespace std;

void lerVerticesDeFicheiro(string nome, int *numVertices, vector<float> *arrayVertices, 
										vector<float> *arrayNormais, vector<float> *arrayTextures);
void escreverVerticesEmFicheiro(string nome, int numVertices, GLfloat *arrayVertices);
GLuint loadBMPImage(string imagepath);
GLfloat *calcularNormaisTriangulos(int numVertices, GLfloat *arrayVertices);

#endif
