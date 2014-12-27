/*
 * BlackWhite.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef BLACKWHITE_H
#define BLACKWHITE_H

#include "../Effect.hpp"

using namespace cv;
using namespace std;

class BlackWhite : public Effect {

public:
	BlackWhite(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		Mat image_out;
	    Canny(in, image_out, *((double *) args[0]), *((double *) args[1]), *((double *) args[2]));
	    cvtColor(image_out, image_out, COLOR_GRAY2RGB);
	    args.clear();
		return image_out;
	}
	
	string getEffectName() {
		return "BlackWhite";
	}
};

#endif