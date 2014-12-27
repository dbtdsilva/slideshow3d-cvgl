/*
 * ChannelSwitch.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef CHANNELSWITCH_H
#define CHANNELSWITCH_H

#include "../Effect.hpp"

using namespace cv;
using namespace std;

class ChannelSwitch : public Effect {

public:
	ChannelSwitch(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		Mat image_out;
	    Canny(in, image_out, *((double *) args[0]), *((double *) args[1]), *((double *) args[2]));
	    cvtColor(image_out, image_out, COLOR_GRAY2RGB);
	    args.clear();
		return image_out;
	}
	
	string getEffectName() {
		return "ChannelSwitch";
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