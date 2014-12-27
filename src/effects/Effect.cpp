/*
 * Effect.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Effect.hpp"
#include <iostream>

using namespace cv;

Effect::Effect(string previewImage) {
	this->image = previewImage;
}
Effect::~Effect() {}

string Effect::getPreviewImagePath() {
	return this->image;
}
string Effect::getEffectName() {
	return "No effect applied selected";
}
Mat Effect::applyEffect(Mat, vector<void*>) {
	return Mat();
}