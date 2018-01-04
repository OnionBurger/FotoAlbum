#include "Standing.h"

void Standing::actualDraw(int windowWidth, int windowHeight) const {
	getTexture()->draw(windowWidth, windowHeight);
}