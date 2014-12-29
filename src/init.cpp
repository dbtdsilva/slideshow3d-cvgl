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
    glClearColor(0, 0, 0, 1.0);
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
    animationMove = false;
    currentPos = 0;
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

void inicializarModelos(string path)
{
    vector<string> files = listImagesDirectory(path, false);
    unsigned int max;
    for (int i = 0; i < files.size(); i++) {
        printf("Loading image (%4.1f): %s\n", ((double) i / files.size()) * 100, files[i].c_str());
        GraphicModel obj;
        lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &obj.numVertices, &obj.arrayVertices, &obj.arrayTextures);
        obj.textureID = loadImage(files[i], &obj.image);
        obj.filepath = files[i];
        obj.original = obj.image;
        obj.desl.x = i == 0 ? -2 : 0;
        obj.desl.y = i == 0 ? 0 : 1.5 + (i-1);
        obj.desl.z = 0;
        obj.anguloRot.x = 0;
        obj.anguloRot.y = 0;
        obj.anguloRot.z = i == 0 ? 0 : 45;
        obj.factorEsc.x = 1;
        max = obj.image.cols > obj.image.rows ? obj.image.cols : obj.image.rows;
        obj.factorEsc.y = (double) obj.image.cols / max;
        obj.factorEsc.z = (double) obj.image.rows / max;
        ss_images.push_back(obj);
    }
    cout << "Images completely loaded (100%)" << endl;

    printf("Loading effects panels\n");
    for (int i = 0; i < matEffects.getNumberEffects(); i++) {
        printf("Loading effect (%4.1f): %s\n", ((double) i / matEffects.getNumberEffects()) * 100, matEffects.getPreviewImagePath(i).c_str());
        GraphicModel obj;
        lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &obj.numVertices, &obj.arrayVertices, &obj.arrayTextures);
        obj.textureID = loadImage(projectPath + matEffects.getPreviewImagePath(i), &obj.image);
        obj.filepath = projectPath + matEffects.getPreviewImagePath(i);
        obj.desl.x = -4.6;
        obj.desl.y = -0.66 + (i/2) * 0.33;
        obj.desl.z = i % 2 == 0 ? 0.7 : 0.87;
        obj.anguloRot.x = 0;
        obj.anguloRot.y = 0;
        obj.anguloRot.z = 0;
        obj.factorEsc.x = 1;
        obj.factorEsc.y = 0.16;
        obj.factorEsc.z = 0.08;
        btn_effects.push_back(obj);
    }
    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &cameraTexture.numVertices, &cameraTexture.arrayVertices, &cameraTexture.arrayTextures);
    cameraTexture.textureID = loadImage(projectPath + "models/white.png", &cameraTexture.image);
    cameraTexture.original = cameraTexture.image;
    cameraTexture.desl.x = -4;
    cameraTexture.desl.y = 0;
    cameraTexture.desl.z = 0;
    cameraTexture.anguloRot.x = 0;
    cameraTexture.anguloRot.y = 0;
    cameraTexture.anguloRot.z = 0;
    cameraTexture.factorEsc.x = 1;
    cameraTexture.factorEsc.y = 0.8;
    cameraTexture.factorEsc.z = 0;
    cout << "Effects completely loaded (100%)" << endl;

    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &btnCamera.numVertices, &btnCamera.arrayVertices, &btnCamera.arrayTextures);
    btnCamera.textureID = loadImage(projectPath + "models/camera.png", &btnCamera.image);
    btnCamera.filepath = projectPath + "models/camera.png";
    btnCamera.desl.x = -4.6;
    btnCamera.desl.y = 0.85;
    btnCamera.desl.z = -0.85;
    btnCamera.anguloRot.x = 0;
    btnCamera.anguloRot.y = 0;
    btnCamera.anguloRot.z = 0;
    btnCamera.factorEsc.x = 1;
    btnCamera.factorEsc.y = 0.1;
    btnCamera.factorEsc.z = 0.08;

    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &btnSave.numVertices, &btnSave.arrayVertices, &btnSave.arrayTextures);
    btnSave.textureID = loadImage(projectPath + "models/save.png", &btnSave.image);
    btnSave.filepath = projectPath + "models/save.png";
    btnSave.desl.x = -4.6;
    btnSave.desl.y = -0.85;
    btnSave.desl.z = -0.85;
    btnSave.anguloRot.x = 0;
    btnSave.anguloRot.y = 0;
    btnSave.anguloRot.z = 0;
    btnSave.factorEsc.x = 1;
    btnSave.factorEsc.y = 0.08;
    btnSave.factorEsc.z = 0.08;

    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &btnDiscard.numVertices, &btnDiscard.arrayVertices, &btnDiscard.arrayTextures);
    btnDiscard.textureID = loadImage(projectPath + "models/reset.png", &btnDiscard.image);
    btnDiscard.filepath = projectPath + "models/reset.png";
    btnDiscard.desl.x = -4.6;
    btnDiscard.desl.y = -0.65;
    btnDiscard.desl.z = -0.85;
    btnDiscard.anguloRot.x = 0;
    btnDiscard.anguloRot.y = 0;
    btnDiscard.anguloRot.z = 0;
    btnDiscard.factorEsc.x = 1;
    btnDiscard.factorEsc.y = 0.08;
    btnDiscard.factorEsc.z = 0.08;

    lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &btnOptions.numVertices, &btnOptions.arrayVertices, &btnOptions.arrayTextures);
    btnOptions.textureID = loadImage(projectPath + "models/options.png", &btnOptions.image);
    btnOptions.filepath = projectPath + "models/options.png";
    btnOptions.desl.x = -4.6;
    btnOptions.desl.y = 0.85;
    btnOptions.desl.z = -0.85;
    btnOptions.anguloRot.x = 0;
    btnOptions.anguloRot.y = 0;
    btnOptions.anguloRot.z = 0;
    btnOptions.factorEsc.x = 1;
    //btnOptions.factorEsc.y = 0.08;
    btnOptions.factorEsc.y = 0.0;   /* Hiding */
    btnOptions.factorEsc.z = 0.08;

    cout << "Creating projection" << endl;
    matrizProj = CreateProjectionMatrix(proj.fovy, proj.aspect_ratio, proj.near_plane, proj.far_plane);
    Translate(&matrizProj, 0, 0, -6);
    RotateAboutX(&matrizProj, DegreesToRadians(90));
    RotateAboutZ(&matrizProj, DegreesToRadians(-90));
    cout << "Projection completely loaded" << endl;
}

void libertarArraysGlobais(void) {
}
