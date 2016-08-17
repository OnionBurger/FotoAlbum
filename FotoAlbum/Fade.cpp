#include "Fade.h"

Fade::Fade(long duration) : TextureTransition(duration) {
}

void Fade::actualDraw(int windowWidth, int windowHeight) const {
	glColor4f(1, 1, 1, getTimeRatio(true));

	getTexture()->draw(windowWidth, windowHeight);
	
	glColor4f(1, 1, 1, 1);
}