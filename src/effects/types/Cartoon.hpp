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
	Cartoon(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
	    else if (in.channels() > 3)
	    	cvtColor(in, in, CV_BGRA2BGR);
		Mat bgr, edges, edgesBgr;

		cvtColor(in, bgr, COLOR_BGRA2BGR);
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
		double v1, v2;
		int v3;
		cout << "Lower threshold: ";
		cin >> v1;
		cout << "Upper threshold: ";
		cin >> v2;
		cout << "Aperture size (default - 3): ";
		cin >> v3;

		v.push_back(new double(v1));
		v.push_back(new double(v2));
		v.push_back(new double(v3));
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		double v1 = 100;
		double v2 = 150;
		int v3 = 3;
		v.push_back(new double(v1));
		v.push_back(new double(v2));
		v.push_back(new double(v3));
		return v;
	}
};

#endif