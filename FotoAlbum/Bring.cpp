#include "Bring.h"

Bring::Bring(long duration) : TextureTransition(duration) {
	distance = 1000.f;
}

void Bring::actualDraw(int windowWidth, int windowHeight) const {
	float ratio = getTimeRatio(true);
	float translationZ = -(1.f - ratio) * distance;
	float angleX = -90.f * (1.f - ratio);

	glPushMatrix();
		glTranslatef(0, 0, translationZ);
		glRotatef(angleX, 1, 0, 0);
		getTexture()->draw(windowWidth, windowHeight);
	glPopMatrix();
}