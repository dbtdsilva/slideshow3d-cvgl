/*
 * Effect.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"

using namespace std;
using namespace cv;

class Effect {
public:
	Effect(string previewImage);
	~Effect();

	string getPreviewImagePath();
	virtual Mat applyEffect(Mat, vector<void*>);
	virtual string getEffectName();
	virtual vector<void*> readParameters();
	virtual vector<void*> requestDefaultParameters();
private:
	string image;
	string effectName;
};

#endif