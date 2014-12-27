/*
 * Sepia.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef SEPIA_H
#define SEPIA_H

#include "../Effect.hpp"

using namespace cv;

class Sepia : public Effect {

public:
	Sepia(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		Mat image_out = in.clone();
		/* 			O mesmo que fazer 
			r = r ∗ 0.189 + g ∗ 0.769 + b ∗ 0.393
			g = r ∗ 0.168 + g ∗ 0.686 + b ∗ 0.349
			b = r ∗ 0.131 + g ∗ 0.534 + b ∗ 0.272
		*/
	    Mat kernel = (Mat_<float>(4,4) <<  0.272, 0.534, 0.131, 0,
	                                       0.349, 0.686, 0.168, 0,
	                                       0.393, 0.769, 0.189, 0,
	                                       0,     0,     0,     1);
	    								 /*   B     G     R     A */  
	    transform(in, image_out, kernel);
		return image_out;
	}
	
	string getEffectName() {
		return "Sepia";
	}
};

#endif