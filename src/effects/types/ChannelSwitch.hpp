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
	ChannelSwitch(string imagepath) : Effect(imagepath, false) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3) {
			cout << "You can't apply this effect on an image without 3 channels at least (RGB)" << endl;
			return in;
		}
		Mat image_out = in.clone();
		/* O mesmo efeito que o Sepia mas com o R e o B trocados */
	    Mat kernel = (Mat_<float>(4,4) <<  1, 0, 0, 0,
	                                       0, 0, 1, 0,
	                                       0, 1, 0, 0,
	                                       0, 0, 0, 1);
	    							/*	   B  G  R  A */  
	    transform(in, image_out, kernel);
		return image_out;
	}
	
	string getEffectName() {
		return "ChannelSwitch";
	}
};

#endif