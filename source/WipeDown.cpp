#include "WipeDown.h"

WipeDown::WipeDown(long duration) : TextureTransition(duration) {
}

void WipeDown::actualDraw(int windowWidth, int windowHeight) const {
	float ratio = getTimeRatio(true);

	int lenY = ratio * getTexture()->getHeight();

	int left = -0.5f * getTexture()->getWidth();
	int right = left + getTexture()->getWidth();
	int top = +0.5f * getTexture()->getHeight();
	int bottom = top - lenY;
	
	float cropX = getTexture()->getCropX();
	float cropY = getTexture()->getCropY();
	float cropYRatio = ((float)lenY) / getTexture()->getHeight();

	glBegin(GL_QUADS);
		glTexCoord2f(0, (1 - cropYRatio) * cropY); glVertex2i(left, bottom);
		glTexCoord2f(cropX, (1 - cropYRatio) * cropY); glVertex2i(right, bottom);
		glTexCoord2f(cropX, cropY); glVertex2i(right, top);
		glTexCoord2f(0, cropY); glVertex2i(left, top);
	glEnd();
}