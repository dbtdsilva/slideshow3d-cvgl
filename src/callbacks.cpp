/*
 * callbacks.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "globals.hpp"
#include "callbacks.hpp"

using namespace std;

bool checkButtonClick(double, double, GraphicModel*);
void animation_buttonPressed(int);
void refreshCameraPanel(int);

void produceModelsShading(GraphicModel *obj)
{
    glEnableVertexAttribArray(attribute_coord3d);
    glEnableVertexAttribArray(attribute_texcoord);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj->textureID);
    float *coordenadas = new GLfloat[obj->arrayVertices.size() * sizeof(GLfloat)];

    glVertexAttribPointer(attribute_coord3d,        // attribute
                          3,                        // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,                 // the type of each element
                          GL_FALSE,                 // take our values as-is
                          0,                        // no extra data between each position
                          obj->arrayVertices.data());      // pointer to the C array
    
    glVertexAttribPointer(attribute_texcoord, // attribute
                          2,                  // number of elements per vertex, here (x,y)
                          GL_FLOAT,           // the type of each element
                          GL_FALSE,           // take our values as-is
                          0,                  // no extra data between each position
                          obj->arrayTextures.data());

    matrizModelView = IDENTITY_MATRIX;
    Translate(&matrizModelView, obj->desl.x, obj->desl.y, obj->desl.z);
    RotateAboutX(&matrizModelView, DegreesToRadians(obj->anguloRot.x));
    RotateAboutY(&matrizModelView, DegreesToRadians(obj->anguloRot.y));
    RotateAboutZ(&matrizModelView, DegreesToRadians(obj->anguloRot.z));
    /* Diminuir o tamanho do modelo para nao sair fora do view volume */
    Scale(&matrizModelView, obj->factorEsc.x, obj->factorEsc.y, obj->factorEsc.z);
    /* Matriz de projeccao e Matriz de transformacao */
    glUniformMatrix4fv(glGetUniformLocation(programaGLSL, "matrizProj"), 1, GL_FALSE, matrizProj.m);
    glUniformMatrix4fv(glGetUniformLocation(programaGLSL, "matrizModelView"), 1, GL_FALSE, matrizModelView.m);

    glUniform1i(glGetUniformLocation(programaGLSL, "mytexture"), /*GL_TEXTURE*/0);

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(attribute_coord3d);
    glDisableVertexAttribArray(attribute_texcoord);

    delete[] coordenadas;
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programaGLSL);
    for (int i = 0; i < ss_images.size(); i++) 
        produceModelsShading(&ss_images[i]);
    for (int i = 0; i < btn_effects.size(); i++) 
        produceModelsShading(&btn_effects[i]);
    produceModelsShading(&cameraTexture);
    produceModelsShading(&btnSave);
    produceModelsShading(&btnOptions);
    produceModelsShading(&btnDiscard);
    produceModelsShading(&btnCamera);
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'Q' :
    case 'q' :
    case 27  :  exit(EXIT_SUCCESS);
        break;        
    }
}

void mySpecialKeys(int key, int x, int y)
{
    unsigned int max;

    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (!cameraActive)
            theme->pressLeft();
        break;

    case GLUT_KEY_RIGHT:
        if (!cameraActive)
            theme->pressRight();
        break;
    }
}

void onMouse(int button, int state, int x, int y)
{
    switch (button) {
        case 3:
            if (!cameraActive)
                theme->zoomIn();
            break;
        case 4:
            if (!cameraActive)
                theme->zoomOut();
            break;
        case 0:
            if (state != GLUT_DOWN)
                return;

            GLint viewport[4];
            GLdouble modelview[16], projection[16];
            GLfloat winX, winY, winZ;
            GLdouble posX, posY, posZ;
         
            glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
            glGetDoublev(GL_PROJECTION_MATRIX, projection);
            glGetIntegerv(GL_VIEWPORT, viewport);
         
            winX = (float)x;
            winY = (float)viewport[3] - (float)y;
            for (int i = 0; i < 16; i++) 
                projection[i] = matrizProj.m[i];

            glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
            gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

            for (int i = 0; i < btn_effects.size(); i++) {
                if (checkButtonClick(posY, posZ, &btn_effects[i])) {
                    if (i < matEffects.getNumberEffects()) {
                        if (cameraActive) {
                            cameraLastEffect = i;
                        } else {
                            matEffects.applyEffect(i, &ss_images[theme->currentPos].image, matEffects.requestDefaultParameters(i));
                            ss_images[theme->currentPos].textureID = loadImage(&ss_images[theme->currentPos].image);
                        }
                    }
                }
            }
            
            if (checkButtonClick(posY, posZ, &btnSave)) {
                if (cameraActive) {
                    saveImage("../savedImages/cameraShot.jpg", cameraTexture.image);
                    cout << "Saved file as: ../savedImages/cameraShot.jpg" << endl;
                } else {
                    string s = ss_images[theme->currentPos].filepath;
                    string::size_type i = s.rfind('.', s.length());
                    if (i != string::npos)
                        s.replace(i, 0, "_output");
                    s = "../savedImages/" + string(basename(s.c_str()));
                    saveImage(s, ss_images[theme->currentPos].image);
                    cout << "Saved file as: " << s << endl;
                }
                
            } else if (!cameraActive && checkButtonClick(posY, posZ, &btnOptions)) {
                printf("Pressed options button\n");
            } else if (checkButtonClick(posY, posZ, &btnCamera)) {
                if (cameraActive) {
                    cameraActive = false;
                    cameraLastEffect = -1;
                    cameraTexture.factorEsc.z = 0;
                    stream.release();
                } else {
                    theme->zoomOut();
                    glutTimerFunc(20, refreshCameraPanel, 1);
                    cameraActive = true;                   
                }
            } else if (!cameraActive && checkButtonClick(posY, posZ, &btnDiscard)) {
                ss_images[theme->currentPos].image = ss_images[theme->currentPos].original;
                ss_images[theme->currentPos].textureID = loadImage(&ss_images[theme->currentPos].image);
            }
            break;
    }
    glutPostRedisplay();
}
bool checkButtonClick(double posY, double posZ, GraphicModel *obj) {
    if (posZ < obj->desl.z + obj->factorEsc.z && posZ > obj->desl.z - obj->factorEsc.z
        && posY < obj->desl.y + obj->factorEsc.y && posY > obj->desl.y - obj->factorEsc.y)
    {
        btnPressed = obj;
        glutTimerFunc(20, animation_buttonPressed, 1);
        return true;
    }
    return false;
}

void refreshCameraPanel(int value) {
    if (value && theme->animationActive) {
        glutTimerFunc(20, refreshCameraPanel, 1);
        return;
    }
    if (value) {
        Mat cameraFrame;
        stream = VideoCapture(0);
        stream.read(cameraFrame);
        double max = cameraFrame.cols > cameraFrame.rows ? cameraFrame.cols : cameraFrame.rows;
        cameraTexture.factorEsc.y = (double) cameraFrame.cols / max;
        cameraTexture.factorEsc.z = (double) cameraFrame.rows / max;
        glutTimerFunc(20, refreshCameraPanel, 0);
    }
    if (cameraActive) {
        Mat cameraFrame;
        stream.read(cameraFrame);
        cameraTexture.image = cameraFrame;
        if (cameraLastEffect > -1 && matEffects.getEffectName(cameraLastEffect) != "Cartoon") {
            matEffects.applyEffect(cameraLastEffect, &cameraTexture.image, matEffects.requestDefaultParameters(cameraLastEffect));
        }       
        cameraTexture.textureID = loadImage(&cameraTexture.image);
        glutTimerFunc(30, refreshCameraPanel, 0);
    } 
    glutPostRedisplay();
}
void animation_buttonPressed(int status) {
    if ((status == 1 && btnPressed->desl.x < -4.57) ||
        (status == 0 && btnPressed->desl.x > -4.6)) {
        btnPressed->desl.x += 0.01 * (status * 2 - 1);
        glutPostRedisplay();
        if (btnPressed->desl.x >= -4.57 && status == 1)
            glutTimerFunc(10, animation_buttonPressed, 0);
        else if (!(btnPressed->desl.x <= -4.6 && status == 0))
            glutTimerFunc(10, animation_buttonPressed, status);
    }
}

void registarCallbackFunctions(void)
{
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeys);
    glutMouseFunc(onMouse);
}
