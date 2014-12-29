/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "theme.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "globals.hpp"
#include <iostream>

Theme * Theme::instance;

Theme* Theme::getInstance(vector<GraphicModel> * images) {
	if (instance == NULL)
		instance = new Theme(images);
	return instance;
}
Theme::Theme(vector<GraphicModel> * images) {
	this->c_images = images;
}
Theme::~Theme() {

}

void Theme::staticAnimation_moveLeft(int pos) { instance->animation_moveLeft(pos); }
void Theme::staticAnimation_moveRight(int pos) { instance->animation_moveRight(pos); }
void Theme::staticAnimation_moveUp(int pos) { instance->animation_moveUp(pos); }
void Theme::staticAnimation_moveDown(int pos) { instance->animation_moveDown(pos); }
void Theme::staticAnimation_zoomIn(int pos) { instance->animation_zoomIn(pos); }
void Theme::staticAnimation_zoomOut(int pos) { instance->animation_zoomOut(pos); }

void Theme::initTheme(string path) {}
void Theme::pressLeft(void) {}
void Theme::pressRight(void) {}
void Theme::pressUp(void) {}
void Theme::pressDown(void) {}
void Theme::zoomIn(void) {}
void Theme::zoomOut(void) {}
void Theme::animation_moveLeft(int) {}
void Theme::animation_moveRight(int) {}
void Theme::animation_moveUp(int) {}
void Theme::animation_moveDown(int) {}
void Theme::animation_zoomIn(int) {}
void Theme::animation_zoomOut(int) {}