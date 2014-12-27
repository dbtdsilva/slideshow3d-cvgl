/*
 * effects.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef EFFECTS_H
#define EFFECTS_H

#include <string>
#include <iostream>
#include "Effect.hpp"

using namespace std;
using namespace cv;

class Effects {
public:
	Effects();
	~Effects();
	string getPreviewImagePath(unsigned int effectNumber);
	string getEffectName(unsigned int effectNumber);
	Mat applyEffect(unsigned int effectNumber, Mat*, vector<void*> arg);
	vector<void*> requestDefaultParameters(unsigned int effectNumber);
	vector<void*> readParameters(unsigned int effectNumber);

	unsigned int getNumberEffects();
private:
	vector<Effect*> list;
};

#endif