/*
 * GraphicModelChess.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef GRAPHICMODEL_H
#define GRAPHICMODEL_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "models.hpp"
#include "utils/mathUtils.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class GraphicModel {
public:
    /* Coordenadas dos vertices */
    GraphicModel();
    ~GraphicModel();

    int numVertices;
    vector<float> arrayVertices;
    vector<float> arrayNormais;
    vector<float> arrayTextures;
    string filepath;
    Mat image, original;
    GLuint textureID;
    /* Parametros das transformacoes */
    Point3_<double> desl;
    Point3_<double> anguloRot;
    Point3_<double> factorEsc;
};

#endif

