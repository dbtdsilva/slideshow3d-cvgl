/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef THEMECONTROLLER_H
#define THEMECONTROLLER_H

#include <string>
#include "theme.hpp"

class ThemeController {
public:
	ThemeController(string path);
	~ThemeController();
	vector<GraphicModel>* getImageVector();
	Theme* getCurrent();
	Theme* next();

private:
	Theme* getThemePos(int);
	int themePos;
	vector<Theme*> list;
	vector<GraphicModel> images;
};

#endif