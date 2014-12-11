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
    vector<float> arrayTextures;
    GLuint textureID;
    /* Parametros das transformacoes */
    Point3_<float> desl;
    Point3_<float> anguloRot;
    Point3_<float> factorEsc;
};

#endif