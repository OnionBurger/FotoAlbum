#include "NewsSpin.h"

NewsSpin::NewsSpin(long duration) : TextureTransition(duration) {
	spins = 3;
}

void NewsSpin::actualDraw(int windowWidth, int windowHeight) const {
	float ratio = getTimeRatio(true);
	float scale = ratio;
	float angleZ = ratio * spins * 360;

	glPushMatrix();
		glScalef(scale, scale, 1);
		glRotatef(angleZ, 0, 0, 1);
		getTexture()->draw(windowWidth, windowHeight);
	glPopMatrix();
}