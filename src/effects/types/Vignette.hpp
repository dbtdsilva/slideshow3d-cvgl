/*
 * Vignette.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef VIGNETTE_H
#define VIGNETTE_H

#include "../Effect.hpp"
#include <cmath>

using namespace cv;
using namespace std;

class Vignette : public Effect {

public:
	Vignette(string imagepath) : Effect(imagepath, true) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
	    else if (in.channels() > 3)
	    	cvtColor(in, in, CV_BGRA2BGR);
		Mat image_out = in.clone();
		int xref = in.rows / 2;
		int yref = in.cols / 2;

		double extFactor = *((double *) args[0]);
		for (int i = 0; i < in.rows; i++) {
			for (int j = 0; j < in.cols; j++) {
	            Vec3b &bgr_out = image_out.at<Vec3b>(i, j);
	    		Vec3b bgr_in = in.at<Vec3b>(i, j);

	    		double distance = sqrt(pow(i - xref,2) + pow(j - yref,2));
				double distance_to_edge = sqrt(pow(xref, 2) + pow(yref, 2));
	    		
	    		double factor = 1 - (distance / distance_to_edge) * extFactor;
	    		for(int k = 0; k < 3; k++)
	    			bgr_out.val[k] = bgr_in.val[k] * factor;
	    	}
	    }
	    args.clear();
		return image_out;
	}
	string getEffectName() {
		return "Vignette";
	}
	vector<void*> readParameters() {
		vector<void *> v;
		double v1;
		cout << "Factor (0 to 1 - default: 0.75): ";
		cin >> v1;
		v.push_back(new double(v1));
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		double v1 = 0.75;
		v.push_back(new double(v1));
		return v;
	}
};

#endif