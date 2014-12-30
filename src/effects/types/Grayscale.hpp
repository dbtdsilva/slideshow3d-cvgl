/*
 * Grayscale.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../Effect.hpp"

using namespace cv;
using namespace std;

class Grayscale : public Effect {

public:
	Grayscale(string imagepath) : Effect(imagepath, false) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
		
		Mat image_out;
	    cvtColor(in, image_out, CV_BGR2GRAY);
	    args.clear();
		return image_out;
	}
	
	string getEffectName() {
		return "Grayscale";
	}
};

#endif