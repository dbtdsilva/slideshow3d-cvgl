/*
 * coverflow.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef COVERFLOW_H
#define COVERFLOW_H

#include <string>
#include "../theme.hpp"

class Coverflow : public Theme {
public:
	static Theme* getInstance(vector<GraphicModel> *);

	void initTheme(string);
	void pressLeft(void);
	void pressRight(void);
	void pressUp(void);
	void pressDown(void);
	void zoomIn(void);
	void zoomOut(void);

protected:
	Coverflow(vector<GraphicModel> *);
	void animation_moveRight(int);
	void animation_moveLeft(int);
	void animation_moveUp(int);
	void animation_moveDown(int);
	void animation_zoomIn(int);
	void animation_zoomOut(int);
};

#endif