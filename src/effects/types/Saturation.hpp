/*
 * Threshold.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef SATURATION_H
#define SATURATION_H

#include "../Effect.hpp"
#include <algorithm>

using namespace cv;
using namespace std;

class Saturation : public Effect {

public:
	Saturation(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
	    else if (in.channels() > 3)
	    	cvtColor(in, in, CV_BGRA2BGR);
		Mat image_out, yuv;

	   	cvtColor(in, yuv, CV_BGR2YCrCb, 0);
	   	image_out = yuv.clone();
	    for (int i = 0; i < yuv.rows; i++) {
	        for (int j = 0; j < yuv.cols; j++) {
	            Vec3f list = yuv.at<Vec3b>(i, j);
	            Vec3b &list_out = image_out.at<Vec3b>(i, j);
	            list_out.val[1] = std::min((double)255, ((list.val[1] - 128) * *((double*) args[0])) + 128);
	            list_out.val[2] = std::min((double)255, ((list.val[2] - 128) * *((double*) args[0])) + 128);
	        }       
	    }
	    cvtColor(image_out, image_out, CV_YCrCb2BGR);
	    args.clear();
		return image_out;
	}
	
	string getEffectName() {
		return "Saturation";
	}
	vector<void*> readParameters() {
		vector<void *> v;
		double v1;
		cout << "Factor ( > 1 is brighter, < 1 is darker): ";
		cin >> v1;

		v.push_back(new double(v1));
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		double v1 = 1.3;
		v.push_back(new double(v1));
		return v;
	}
};

#endif