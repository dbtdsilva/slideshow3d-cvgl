 /*
 * models.cpp
 *
 * Ficheiro de implementacao do modulo MODELS.
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include "models.hpp"
#include "utils/mathUtils.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

GLuint loadBMPImage(string imagepath) {
	// Create one OpenGL texture
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Mat image = cv::imread(imagepath, CV_LOAD_IMAGE_UNCHANGED);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID;
}
void lerVerticesDeFicheiro(string nome, int *numVertices, vector<float> *arrayVertices, 
										vector<float> *arrayNormais, vector<float> *arrayTextures)
{
	std::vector<Point3_<float> > vertices, normalVector, faces, facesNormals;
	std::vector<Point_<float> > textureVector, facesTextures;

	FILE * file = fopen(nome.c_str(), "r");
	if(file == NULL){
	    printf("Failed to open file!\n");
	    return;
	}

	char firstChar[128];
	int res = fscanf(file, "%s", firstChar);

	Point3_<float> tmp, tmpN;
	Point_<float> tmpT;
	while(res != EOF) {
	    if (strcmp(firstChar, "v") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    vertices.push_back(tmp);
		} else if(strcmp(firstChar, "vn") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    normalVector.push_back(tmp);
		} else if(strcmp(firstChar, "vt") == 0) {
			fscanf(file, "%f %f\n", &tmpT.x, &tmpT.y);
			textureVector.push_back(tmpT);
		} else if(strcmp(firstChar, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
																	   &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
																	   &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    faces.push_back(vertices.at(vertexIndex[0]-1));
		    faces.push_back(vertices.at(vertexIndex[1]-1));
		    faces.push_back(vertices.at(vertexIndex[2]-1));

		    facesTextures.push_back(textureVector.at(uvIndex[0]-1));
		    facesTextures.push_back(textureVector.at(uvIndex[1]-1));
		    facesTextures.push_back(textureVector.at(uvIndex[2]-1));

		    facesNormals.push_back(normalVector.at(normalIndex[0]-1));
		    facesNormals.push_back(normalVector.at(normalIndex[1]-1));
		    facesNormals.push_back(normalVector.at(normalIndex[2]-1));
		} else {

		}
		res = fscanf(file, "%s", firstChar);
	}

	*numVertices = faces.size();
	int i;
	int sub = 0;
	for (i = 0; i < faces.size(); i++) {
		tmp = faces.at(i);
		tmpN = facesNormals.at(i);
		tmpT = facesTextures.at(i);

		arrayNormais->push_back(tmpN.x);
		arrayNormais->push_back(tmpN.y);
		arrayNormais->push_back(tmpN.z);

		arrayTextures->push_back(tmpT.x);
		arrayTextures->push_back(tmpT.y);

		arrayVertices->push_back(tmp.x);
		arrayVertices->push_back(tmp.y);
		arrayVertices->push_back(tmp.z);
	}
}


void escreverVerticesEmFicheiro(char *nome, int numVertices, GLfloat *arrayVertices)
{
	int i, j, indexArrayCoords;
	FILE *fp = fopen(nome, "w");
	if (fp == NULL) {
		fprintf(stderr, "ERRO na escrita do ficheiro %s\n", nome);
		exit(EXIT_FAILURE);
	}
	/* Escrever o numero de vertices */
	fprintf(fp, "%d\n", numVertices);
	indexArrayCoords = 0;
	for (i = 0; i < numVertices; i++) {
		for (j = 0; j < 3; j++)
			fprintf(fp, "%f ", arrayVertices[ indexArrayCoords++ ]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}


GLfloat *calcularNormaisTriangulos(int numVertices, GLfloat *arrayVertices)
{
	GLfloat *arrayNormais = (GLfloat *) malloc(3 * numVertices * sizeof(GLfloat));
	int index = 0; /* Indice para o proximo elemento */
	int j = 0;
	/* Para cada face triangular do modelo */
	for (index = 0; index < (3 * numVertices); index += 9)
	{
		GLfloat *normalVector;
		normalVector = computeUnitNormalToTriangle(&arrayVertices[index]);
		/* Store the unit normal vector for each vertex */
		for (j = 0; j < 3; j++)
		{
			arrayNormais[index + j] = normalVector[j];
			arrayNormais[index + j + 3] = normalVector[j];
			arrayNormais[index + j + 6] = normalVector[j];
		}
		free(normalVector);
	}
	return arrayNormais;
}

