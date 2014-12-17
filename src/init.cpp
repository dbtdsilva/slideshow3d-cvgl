/*
 * init.cpp
 *
 * Ficheiro de implementacao do modulo INIT.
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "utils/mathUtils.hpp"
#include "models/models.hpp"
#include <iostream>

void inicializarEstado(void)
{
    /* DOUBLE-BUFFERING + DEPTH-TESTING */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    /* Definir a cor do fundo */
    glClearColor(1, 1, 1, 1.0);
    /* Atributos das primitivas */
    glPointSize(4.0);
    glLineWidth(3.0);
    /* Modo de desenho dos poligonos */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    /* Back-Face Culling */
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Matriz de projeccao é inicialmente a IDENTIDADE => Proj. Paralela Ortogonal */
    matrizProj = IDENTITY_MATRIX;
    matrizModelView = IDENTITY_MATRIX;
    animationActive = false;
}


void inicializarJanela(void)
{
    /* Caracteristicas da janela de saida */
    glutInitWindowSize(700, 700);   /* Usar variaveis GLOBAIS para estes parametros */
    glutInitWindowPosition(300, 20);
    /* Para terminar de modo apropriado */
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    /* Criar a janela de saida */
    windowHandle = glutCreateWindow("Slideshow 3D 2014");
    if (windowHandle < 1) {
        fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
        exit(EXIT_FAILURE);
    }
}

void inicializarPlanoProjeccao(void)
{
    proj.fovy = 70;
    proj.aspect_ratio = 1;
    proj.near_plane = 1;
    proj.far_plane = 150;
}

void inicializarModelos(void)
{
    GraphicModel * obj = new GraphicModel();
    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                    &obj->numVertices, &obj->arrayVertices, &obj->arrayTextures);
    obj->textureID = loadImage(projectPath + "models/skybox.bmp", &obj->image);
    obj->desl.x = 0;
    obj->desl.y = 0;
    obj->desl.z = 0;
    obj->anguloRot.x = 0;
    obj->anguloRot.y = 0;
    obj->anguloRot.z = 0;
    obj->factorEsc.x = 1;
    unsigned int max = obj->image.cols > obj->image.rows ? obj->image.cols : obj->image.rows;
    obj->factorEsc.y = (double) obj->image.cols / max;
    obj->factorEsc.z = (double) obj->image.rows / max;
    ss_images.push_back(obj);

    matrizProj = CreateProjectionMatrix(proj.fovy, proj.aspect_ratio, proj.near_plane, proj.far_plane);
    Translate(&matrizProj, 0, 2, -6);
    RotateAboutX(&matrizProj, DegreesToRadians(90));
    RotateAboutZ(&matrizProj, DegreesToRadians(-90));
}

void libertarArraysGlobais(void) {
}
