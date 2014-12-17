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
        produceModelsShading(ss_images[i]);
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
    int i;
    GraphicModel *obj;
    switch (key)
    {
    case 'Q' :
    case 'q' :
    case 27  :  exit(EXIT_SUCCESS);
    case '+' :
        glutPostRedisplay();
        break;
    case '-' :
        glutPostRedisplay();
        break;
    case '.':
        glutPostRedisplay();
        break;
    case ',':
        glutPostRedisplay();
        break;
    case 'p':
    case 'P':
        break;
    case 'm':
    case 'M':
        break;        
    }
}

void mySpecialKeys(int key, int x, int y)
{
    if (animationActive)
        return;

    switch (key)
    {
    case GLUT_KEY_LEFT :
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT :
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP :
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN :
        glutPostRedisplay();
        break;
    }
}

void onMouse(int button, int state, int x, int y)
{
    if (button == 3) {
        Scale(&matrizProj, 1.02, 1.02, 1.02);
        glutPostRedisplay();
        return;
    }

    if (button == 4){
        Scale(&matrizProj, 0.98, 0.98, 0.98);
        glutPostRedisplay();
        return;
    }

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
}

void registarCallbackFunctions(void)
{
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeys);
    glutMouseFunc(onMouse);
}
