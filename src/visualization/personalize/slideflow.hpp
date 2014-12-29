/*
 * coverflow.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef SLIDEFLOW_H
#define SLIDEFLOW_H

#include <string>
#include "../theme.hpp"

class Slideflow : public Theme {
public:
	static Theme* getInstance(vector<GraphicModel> *);

	void initTheme(void);
	void pressLeft(void);
	void pressRight(void);
	void pressUp(void);
	void pressDown(void);
	void zoomIn(void);
	void zoomOut(void);

protected:
	Slideflow(vector<GraphicModel> *);
	void animation_moveRight(int);
	void animation_moveLeft(int);
	void animation_moveUp(int);
	void animation_moveDown(int);
	void animation_zoomIn(int);
	void animation_zoomOut(int);
};

#endif