/*
 * Sepia.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef SEPIA_H
#define SEPIA_H

#include "../Effect.hpp"

using namespace cv;

class Sepia : public Effect {

public:
	Sepia(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		std::cout << "what2" << std::endl;
		Mat image_out = in.clone();

	    Mat kern = (cv::Mat_<float>(4,4) <<  0.272, 0.534, 0.131, 0,
	                                         0.349, 0.686, 0.168, 0,
	                                         0.393, 0.769, 0.189, 0,
	                                         0, 0, 0, 1);
	    transform(in, image_out, kern);
		return image_out;
	}
	
	string getEffectName() {
		return "Sepia";
	}
};

#endif