/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "coverflow.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "coverflow.hpp"
#include <iostream>
#include "../../globals.hpp"


Coverflow::Coverflow(vector<GraphicModel> * images) : Theme(images) {}

Theme* Coverflow::getInstance(vector<GraphicModel> * images) {
    if (instance == NULL)
        instance = new Coverflow(images);
    return instance;
}

void Coverflow::initTheme(string path) {
    animationActive = false;
    animationMove = false;
    animationZoom = false;
    currentPos = 0;

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
}

void Coverflow::pressLeft(void) {
    if (animationMove)
        return;
    if (currentPos == 0)
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos--;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveLeft, currentPos);
}

void Coverflow::pressRight(void) {
	if (animationMove)
        return;
    if (currentPos == c_images->size() - 1)
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
    currentPos++;
    animationMove = true;
    glutTimerFunc(20, staticAnimation_moveRight, currentPos);
}
void Coverflow::pressUp(void) {}
void Coverflow::pressDown(void) {}
void Coverflow::zoomIn(void) {
    if (animationActive)
        return;
    glutTimerFunc(20, staticAnimation_zoomIn, currentPos);
}
void Coverflow::zoomOut(void) {
    if (animationActive)
        return;
    glutTimerFunc(20, staticAnimation_zoomOut, currentPos);
}

void Coverflow::animation_moveRight(int pos) {
    bool changed = false;
    for (int i = 0; i < c_images->size(); i++) {
        if (i == currentPos) {
            if ((*c_images)[i].desl.y > 0) {
                (*c_images)[i].desl.y -= 0.05;
                changed = true;
            }
            if ((*c_images)[i].anguloRot.z != 0) {
                (*c_images)[i].anguloRot.z -= 3; 
                changed = true;
            }
            if ((*c_images)[i].desl.x > -2) {
                (*c_images)[i].desl.x -= 0.1;
                changed = true;
            }
        } else if (i > currentPos) {
            if ((*c_images)[i].anguloRot.z < 45) {
                (*c_images)[i].anguloRot.z += 3;
                changed = true;
            }
            if ((*c_images)[i].desl.y > (0.5 + i - currentPos)) {
                (*c_images)[i].desl.y -= 0.05;
                changed = true;
            }
        } else {
            if ((*c_images)[i].anguloRot.z > -45) {
                (*c_images)[i].anguloRot.z -= 3;
                changed = true;
            }
            if ((*c_images)[i].desl.y > (-0.5 + i - currentPos)) {
                (*c_images)[i].desl.y -= 0.05;
                changed = true;
            }
        }
    }
    glutPostRedisplay();
    if (changed)
        glutTimerFunc(5, staticAnimation_moveRight, pos);
    else {
        for (int i = 0; i < c_images->size(); i++) {
            (*c_images)[i].desl.y = i < currentPos ? -0.5 + i - currentPos : 0.5 + i - currentPos;
            (*c_images)[i].anguloRot.z = i < currentPos ? -45 : 45;
            if (i == currentPos) {
                (*c_images)[i].desl.x = -2;
                (*c_images)[i].desl.y = 0;
                (*c_images)[i].anguloRot.z = 0;
            }
        }
        animationMove = false;
    }
}

void Coverflow::animation_moveLeft(int pos) {
    bool changed = false;
    for (int i = 0; i < c_images->size(); i++) {
        if (i == currentPos) {
            if ((*c_images)[i].desl.y < 0) {
                (*c_images)[i].desl.y += 0.05;
                changed = true;
            }
            if ((*c_images)[i].anguloRot.z != 0) {
                (*c_images)[i].anguloRot.z += 3; 
                changed = true;
            }
            if ((*c_images)[i].desl.x > -2) {
                (*c_images)[i].desl.x -= 0.1;
                changed = true;
            }
        } else if (i > currentPos) {
            if ((*c_images)[i].anguloRot.z < 45) {
                (*c_images)[i].anguloRot.z += 3;
                changed = true;
            }
            if ((*c_images)[i].desl.y < (0.5 + i - currentPos)) {
                (*c_images)[i].desl.y += 0.05;
                changed = true;
            }
        } else {
            if ((*c_images)[i].anguloRot.z > -45) {
                (*c_images)[i].anguloRot.z -= 3;
                changed = true;
            }
            if ((*c_images)[i].desl.y < (-0.5 + i - currentPos)) {
                (*c_images)[i].desl.y += 0.05;
                changed = true;
            }
            
        }
    }
    glutPostRedisplay();
    if (changed) 
        glutTimerFunc(5, staticAnimation_moveLeft, pos);
    else {
        for (int i = 0; i < c_images->size(); i++) {
            (*c_images)[i].desl.y = i < currentPos ? -0.5 + i - currentPos : 0.5 + i - currentPos;
            (*c_images)[i].anguloRot.z = i < currentPos ? -45 : 45;
            if (i == currentPos) {
                (*c_images)[i].desl.x = -2;
                (*c_images)[i].desl.y = 0;
                (*c_images)[i].anguloRot.z = 0;
            }
        }
        animationMove = false;
    }
}
void Coverflow::animation_moveDown(int pos) {}
void Coverflow::animation_moveUp(int pos) {}
void Coverflow::animation_zoomIn(int pos) {
    if (ss_images[pos].desl.x > -4.5) { 
        animationActive = true;
        ss_images[pos].desl.x -= 0.1;
        glutPostRedisplay();
        glutTimerFunc(20, staticAnimation_zoomIn, pos);
    } else {
        ss_images[pos].desl.x = -4.5;
        animationActive = false;
    }
}
void Coverflow::animation_zoomOut(int pos) {
    int max = pos == currentPos ? -2 : 0;
    if (ss_images[pos].desl.x < max) { 
        animationActive = true;
        ss_images[pos].desl.x += 0.1;
        glutPostRedisplay();
        glutTimerFunc(20, staticAnimation_zoomOut, pos);
    } else {
        ss_images[pos].desl.x = max;
        animationActive = false;
    }
}