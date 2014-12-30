/*
 * FloodFilling.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef FLOODFILLING_H
#define FLOODFILLING_H

#include "../Effect.hpp"

using namespace cv;
using namespace std;

class FloodFilling : public Effect {

public:
	FloodFilling(string imagepath) : Effect(imagepath, true) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		Mat image_out = in.clone();
		floodFill(image_out, Point(*((int*) args[0]), *((int*) args[1])), *((int*) args[2]), 0, 
									*((int*) args[3]), *((int*) args[4]));
	    args.clear();
		return image_out;
	}
	
	string getEffectName() {
		return "FloodFilling";
	}
	vector<void*> readParameters() {
		vector<void *> v;
		int v1, v2, v3;
		int x, y;
		cout << "Start point" << endl << "X: ";
		cin >> x;
		cout << "Y: ";
		cin >> y;
		cout << "New value to write on pixel: ";
		cin >> v1;
		cout << "Lower margin to flood (default - 50): ";
		cin >> v2;
		cout << "Upper margin to flood (default - 50): ";
		cin >> v3;
		v.push_back(new int(x));
		v.push_back(new int(y));
		v.push_back(new int(v1));
		v.push_back(new int(v2));
		v.push_back(new int(v3));
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		int v1 = 0;
		int v2 = 50;
		int v3 = 50;
		int x, y;
		cout << "Start point" << endl << "X: ";
		cin >> x;
		cout << "Y: ";
		cin >> y;
		v.push_back(new int(x));
		v.push_back(new int(y));
		v.push_back(new int(v1));
		v.push_back(new int(v2));
		v.push_back(new int(v3));
		return v;
	}
};

#endif