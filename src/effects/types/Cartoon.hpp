/*
 * Cartoon.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef CARTOON_H
#define CARTOON_H

#include "../Effect.hpp"

using namespace cv;
using namespace std;

class Cartoon : public Effect {

public:
	Cartoon(string imagepath) : Effect(imagepath, false) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
	    else if (in.channels() > 3)
	    	cvtColor(in, in, CV_BGRA2BGR);
		Mat bgr, edges, edgesBgr;
	    pyrMeanShiftFiltering(in, bgr, 15, 40);
	    
	    Canny(in, edges, 150, 150);
	    cvtColor(edges, edgesBgr, COLOR_GRAY2BGR);
	    
	    bgr = bgr - edgesBgr;
    	return bgr;
	}
	
	string getEffectName() {
		return "Cartoon";
	}
	vector<void*> readParameters() {
		vector<void *> v;
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		return v;
	}
};

#endif