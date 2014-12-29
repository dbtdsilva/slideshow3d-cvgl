/*
 * Pencil.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

 /* 
  * Fonts:
  *		https://books.google.pt/books?id=GY-AAwAAQBAJ
  */

#ifndef PENCIL_H
#define PENCIL_H

#define ChannelBlend_ColorDodge(A,B) ((uint8_t)((B == 255) ? B:min(255, ((A << 8 ) / (255 - B)))))
  
#include "../Effect.hpp"
  
using namespace cv;
using namespace std;

class Pencil : public Effect {

public:
	Pencil(string imagepath) : Effect(imagepath) {}

	Mat applyEffect(Mat in, vector<void*> args) {
		if (in.channels() < 3)
	    	cvtColor(in, in, CV_GRAY2BGR);
	    else if (in.channels() > 3)
	    	cvtColor(in, in, CV_BGRA2BGR);
		Mat image_out;

	    Mat imagem8Bits;
	    Mat imagemSobel5x5_X;
	    Sobel(in, imagemSobel5x5_X, CV_16SC1, 1, 0, *((int*) args[0]));
	    Mat imagemSobel5x5_Y;
	    Sobel(in, imagemSobel5x5_Y, CV_16SC1, 0, 1, *((int*) args[0]));

	    image_out = imagemSobel5x5_X^2 + imagemSobel5x5_Y^2;
	    convertScaleAbs(image_out, image_out);
	    bitwise_not(image_out, image_out);
	    cvtColor(image_out, image_out, CV_BGR2GRAY);
		return image_out;
	}
	
	string getEffectName() {
		return "Pencil";
	}
	vector<void*> readParameters() {
		vector<void *> v;
		int v1;
		cout << "Sobel kernel size (default is 3, possible values: 1, 3, 5 or 7): ";
		cin >> v1;
		v.push_back(new int(v1));
		return v;
	}
	vector<void*> requestDefaultParameters() {
		vector<void *> v;
		int v1 = 3;
		v.push_back(new int(v1));
		return v;
	}
};

#endif