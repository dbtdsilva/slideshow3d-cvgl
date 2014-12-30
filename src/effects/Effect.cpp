/*
 * Effect.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Effect.hpp"
#include <iostream>
using namespace cv;

Effect::Effect(string previewImage, bool custom) {
	this->image = previewImage;
	this->custom = custom;
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
vector<void*> Effect::readParameters() {
	vector<void *> v;
	return v;
}
vector<void*> Effect::requestDefaultParameters() {
	vector<void *> v;
	return v;
}