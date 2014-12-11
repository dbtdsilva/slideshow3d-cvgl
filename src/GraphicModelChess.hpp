/*
 * GraphicModelChess.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef GRAPHICMODELCHESS_H
#define GRAPHICMODELCHESS_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "models.hpp"
#include "utils/mathUtils.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class GraphicModelChess
{
public:
    /* Coordenadas dos vertices */
    GraphicModelChess();
    ~GraphicModelChess();

    int numVertices;
    vector<float> arrayVertices;
    vector<float> arrayTextures;
    vector<float> arrayNormais;
    GLuint textureID;
    /* Propriedades do material */
    float kAmb[4];
    float kDif[4];
    float kEsp[4];
    float coefPhong;
    /* Parametros das transformacoes */
    Point3_<float> desl;
    Point3_<float> anguloRot;
    Point3_<float> factorEsc;
};

#endif