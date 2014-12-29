/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "slideflow.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "slideflow.hpp"
#include <iostream>
#include "../../globals.hpp"


Slideflow::Slideflow(vector<GraphicModel>* images) : Theme(images) {}

Theme* Slideflow::getInstance(vector<GraphicModel>* images) {
    instance = new Slideflow(images);
    return instance;
}

void Slideflow::initTheme(void) {
    animationActive = false;
    animationMove = false;
    animationZoom = false;
    currentPos = 1;

    unsigned int max;
    for (int i = 0; i < c_images->size(); i++) {
        switch (i % 3) {
            case 0: (*c_images)[i].desl.z = 2; break;
            case 1: (*c_images)[i].desl.z = 0; break;
            case 2: (*c_images)[i].desl.z = -2; break;
        }
        (*c_images)[i].desl.x = 0;
        (*c_images)[i].desl.y = int(i / 3) * 2.1;
        (*c_images)[i].anguloRot.x = 0;
        (*c_images)[i].anguloRot.y = 0;
        (*c_images)[i].anguloRot.z = 0;
        (*c_images)[i].factorEsc.x = 1;
        max = (*c_images)[i].image.cols > (*c_images)[i].image.rows ? (*c_images)[i].image.cols : (*c_images)[i].image.rows;
        (*c_images)[i].factorEsc.y = (double) (*c_images)[i].image.cols / max;
        (*c_images)[i].factorEsc.z = (double) (*c_images)[i].image.rows / max;
    }
    (*c_images)[currentPos].desl.x = -2;
    (*c_images)[currentPos].desl.y = 0;
    (*c_images)[currentPos].desl.z = 0;
}

void Slideflow::pressLeft(void) {
    if (animationMove)
        return;
    if (currentPos - 3 < 0)
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos -= 3;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveLeft, currentPos);
}

void Slideflow::pressRight(void) {
	if (animationMove)
        return;
    if (currentPos + 3 >= c_images->size())
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos += 3;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveRight, currentPos);
}
void Slideflow::pressUp(void) {
    if ((int) ((currentPos + 1) / 3) != (int)(currentPos / 3))
        return;
    if (currentPos + 1 >= c_images->size())
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos += 1;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveRight, currentPos);
}
void Slideflow::pressDown(void) {
    if ((int) ((currentPos - 1) / 3) != (int)(currentPos / 3))
        return;
    if (currentPos - 1 >= c_images->size())
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos -= 1;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveRight, currentPos);
}
void Slideflow::zoomIn(void) {
    if (animationActive)
        return;
    glutTimerFunc(20, staticAnimation_zoomIn, currentPos);
}
void Slideflow::zoomOut(void) {
    if (animationActive)
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
}

void Slideflow::animation_moveRight(int pos) {
    bool changed = false;
    for (int i = 0; i < c_images->size(); i++) {
        if ((*c_images)[i].desl.y > int(i / 3) * 2.1 - int(pos / 3) * 2.1) {
            (*c_images)[i].desl.y -= 0.05;
            changed = true;
        }
    }
    if ((*c_images)[pos].desl.x > -2) {
        (*c_images)[pos].desl.x -= 0.05;
        changed = true;
    }
    if (pos % 3 == 0 && (*c_images)[pos].desl.z > 1) {
        (*c_images)[pos].desl.z -= 0.1;
        changed = true;
    } else if (pos % 3 == 2 && (*c_images)[pos].desl.z < -1) {
        (*c_images)[pos].desl.z += 0.1;
        changed = true;
    }
    glutPostRedisplay();
    if (changed)
        glutTimerFunc(5, staticAnimation_moveRight, pos);
    else {
        for (int i = 0; i < c_images->size(); i++)
            (*c_images)[i].desl.y = int(i / 3) * 2.1 - int(pos / 3) * 2.1;
        if (pos % 3 == 0)
            (*c_images)[pos].desl.z = 1;
        if (pos % 3 == 2)            
            (*c_images)[pos].desl.z = -1;
        (*c_images)[pos].desl.x = -2;
        animationMove = false;
    }
}

void Slideflow::animation_moveLeft(int pos) {
    bool changed = false;
    for (int i = 0; i < c_images->size(); i++) {
        if ((*c_images)[i].desl.y < (int(i / 3) * 2.1 - int(pos / 3) * 2.1)) {
            (*c_images)[i].desl.y += 0.05;
            changed = true;
        }
    }
    if ((*c_images)[pos].desl.x > -2) {
        (*c_images)[pos].desl.x -= 0.05;
        changed = true;
    }
    if (pos % 3 == 0 && (*c_images)[pos].desl.z > 1) {
        (*c_images)[pos].desl.z -= 0.1;
        changed = true;
    } else if (pos % 3 == 2 && (*c_images)[pos].desl.z < -1) {
        (*c_images)[pos].desl.z += 0.1;
        changed = true;
    }

    glutPostRedisplay();
    if (changed)
        glutTimerFunc(5, staticAnimation_moveLeft, pos);
    else {
        for (int i = 0; i < c_images->size(); i++)
            (*c_images)[i].desl.y = int(i / 3) * 2.1 - int(pos / 3) * 2.1;
        if (pos % 3 == 0)
            (*c_images)[pos].desl.z = 1;
        if (pos % 3 == 2)            
            (*c_images)[pos].desl.z = -1;
        (*c_images)[pos].desl.x = -2;
        animationMove = false;
    }
}
void Slideflow::animation_moveDown(int pos) {}
void Slideflow::animation_moveUp(int pos) {}
void Slideflow::animation_zoomIn(int pos) {
    bool changed = false;

    if ((*c_images)[pos].desl.x > -4.5) { 
        changed = true;
        (*c_images)[pos].desl.x -= 0.1;   
    }
    if (pos % 3 == 2 && (*c_images)[pos].desl.z < 0) { 
        changed = true;
        (*c_images)[pos].desl.z += 0.1;
    }
    if (pos % 3 == 0 && (*c_images)[pos].desl.z > 0) { 
        changed = true;
        (*c_images)[pos].desl.z -= 0.1;
    }

    glutPostRedisplay();
    if (changed) {
        animationActive = true;
        glutTimerFunc(20, staticAnimation_zoomIn, pos);
    } else {
        (*c_images)[pos].desl.x = -4.5;
        (*c_images)[pos].desl.z = 0;
        animationActive = false;
    }
    
}
void Slideflow::animation_zoomOut(int pos) {
    bool changed = false;
    int max = pos == currentPos ? -2 : 0;
    int maxZ;
    
    if ((*c_images)[pos].desl.x < max) {
        (*c_images)[pos].desl.x += 0.1;
        changed = true;
    }

    int maxZ_minus = pos == currentPos ? -1 : -2;
    int maxZ_plus = pos == currentPos ? 1 : 2;
    if (pos % 3 == 0 && (*c_images)[pos].desl.z < maxZ_plus) {
        (*c_images)[pos].desl.z += 0.1;
        changed = true;
    } else if (pos % 3 == 2 && (*c_images)[pos].desl.z > maxZ_minus) {
        (*c_images)[pos].desl.z -= 0.1;
        changed = true;
    }

    glutPostRedisplay();
    if (changed) {
        animationActive = true;
        glutTimerFunc(20, staticAnimation_zoomOut, pos);
    }
    else {
        animationActive = false;
        (*c_images)[pos].desl.x = max;
        switch (pos % 3) {
            case 0: (*c_images)[pos].desl.z = maxZ_plus; break;
            case 1: (*c_images)[pos].desl.z = 0; break;
            case 2: (*c_images)[pos].desl.z = maxZ_minus; break;
        }
    }
}