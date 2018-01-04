#include "TextureTransition.h"

TextureTransition::TextureTransition(long duration) {
	reverse = false;
	texture = 0;
	timeSum = 0;
	this->duration = duration;
}

float TextureTransition::getTimeRatio(bool mindReverse) const {
	if (mindReverse && reverse) return 1.f - ((float)timeSum) / duration;
	else return ((float)timeSum) / duration;
}

long TextureTransition::time(long elapsedMs) {
	timeSum += elapsedMs;
	if (timeSum >= duration) {
		return timeSum - duration;
	} else {
		return 0;
	}
}

void TextureTransition::draw(int windowWidth, int windowHeight) const {
	if (texture == 0) return;

	texture->bind();
	actualDraw(windowWidth, windowHeight);
}

TextureTransition::~TextureTransition() {
}