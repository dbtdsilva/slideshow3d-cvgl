/*
 * effects.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Effects.hpp"
#include "../globals.hpp"
#include "types/Sepia.hpp"

using namespace std;

Effects::Effects() {
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
	list.push_back(new Sepia("effects/types/sepia.png"));
}
Effects::~Effects() {
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
