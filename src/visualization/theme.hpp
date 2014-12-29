/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef THEME_H
#define THEME_H

#include <string>
#include "../models/graphicmodel.hpp"

using namespace std;
using namespace cv;

class Theme {
public:
	static Theme* getInstance(vector<GraphicModel> * images);

	virtual ~Theme();

	virtual void initTheme(void);
	virtual void pressLeft(void);
	virtual void pressRight(void);
	virtual void pressUp(void);
	virtual void pressDown(void);
	virtual void zoomIn(void);
	virtual void zoomOut(void);
	virtual void animation_moveLeft(int);
	virtual void animation_moveRight(int);
	virtual void animation_moveUp(int);
	virtual void animation_moveDown(int);
	virtual void animation_zoomIn(int);
	virtual void animation_zoomOut(int);
	int currentPos;
	bool animationActive;
protected:
	Theme(vector<GraphicModel> * images);

	static void staticAnimation_moveLeft(int);
	static void staticAnimation_moveRight(int);
	static void staticAnimation_moveUp(int);
	static void staticAnimation_moveDown(int);
	static void staticAnimation_zoomIn(int);
	static void staticAnimation_zoomOut(int);
	static Theme * instance;

	bool animationMove;
	bool animationZoom;
	vector<GraphicModel> * c_images;
};

#endif