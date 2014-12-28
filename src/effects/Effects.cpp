/*
 * effects.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Effects.hpp"
#include "../globals.hpp"
#include "types/Sepia.hpp"
#include "types/CannyE.hpp"
#include "types/Cartoon.hpp"
#include "types/Illumination.hpp"
#include "types/Saturation.hpp"
#include "types/ChannelSwitch.hpp"
#include "types/Lomo.hpp"
#include "types/Grayscale.hpp"
#include "types/FloodFilling.hpp"
#include "types/Vignette.hpp"
#include "types/Pencil.hpp"

using namespace std;

Effects::Effects() {
	list.push_back(new Sepia("effects/types/sepia.jpg"));
	list.push_back(new Lomo("effects/types/lomo.jpg"));				
	list.push_back(new Cartoon("effects/types/cartoon.jpg"));				
	list.push_back(new CannyE("effects/types/canny.jpg"));	
	list.push_back(new Grayscale("effects/types/grayscale.jpg"));	
	list.push_back(new Saturation("effects/types/saturation.jpg"));
	list.push_back(new Vignette("effects/types/vignette.jpg"));
	list.push_back(new Pencil("effects/types/pencil.jpg"));
	list.push_back(new ChannelSwitch("effects/types/channelswitch.jpg"));
	list.push_back(new Illumination("effects/types/illumination.jpg"));
}
Effects::~Effects() {
	for (int i = 0; i < list.size(); i++)
		delete list[i];
	list.clear();
}
Mat Effects::applyEffect(unsigned int effectNumber, Mat* in, vector<void*> arg) {
	return *in = list[effectNumber]->applyEffect(*in, arg);
}
unsigned int Effects::getNumberEffects() {
	return list.size();
}
string Effects::getEffectName(unsigned int effectNumber) {
	return list[effectNumber]->getEffectName();
}
string Effects::getPreviewImagePath(unsigned int effectNumber) {
	return list[effectNumber]->getPreviewImagePath();
}
vector<void*> Effects::requestDefaultParameters(unsigned int effectNumber) {
	return list[effectNumber]->requestDefaultParameters();
}
vector<void*> Effects::readParameters(unsigned int effectNumber) {
	return list[effectNumber]->readParameters();
}