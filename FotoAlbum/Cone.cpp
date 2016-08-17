#include "Cone.h"

Cone::Cone(long duration) : TextureTransition(duration) {
}

void Cone::actualDraw(int windowWidth, int windowHeight) const {
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	float cropX = getTexture()->getCropX();
	float cropY = getTexture()->getCropY();

	float ratio = getTimeRatio();

	float left = (-width / 2.f) * ratio;
	float right = (+width / 2.f) * ratio;
	float bottom = (-height / 2.f) * ratio;
	float top = (+height / 2.f) * ratio;

	float far = -((width + height) / 2.f) * (1 - ratio);

	float centerX = 0;
	float centerY = 0;
	float centerZ = 0;

	glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0); glVertex3f(left, bottom, far);
		glTexCoord2f(cropX, 0); glVertex3f(right, bottom, far);
		glTexCoord2f(cropX / 2, cropY / 2); glVertex3f(centerX, centerY, centerZ);
		
		glTexCoord2f(cropX, 0); glVertex3f(right, bottom, far);
		glTexCoord2f(cropX, cropY); glVertex3f(right, top, far);
		glTexCoord2f(cropX / 2, cropY / 2); glVertex3f(centerX, centerY, centerZ);
		
		glTexCoord2f(cropX, cropY); glVertex3f(right, top, far);
		glTexCoord2f(0, cropY); glVertex3f(left, top, far);
		glTexCoord2f(cropX / 2, cropY / 2); glVertex3f(centerX, centerY, centerZ);
		
		glTexCoord2f(0, cropY); glVertex3f(left, top, far);
		glTexCoord2f(0, 0); glVertex3f(left, bottom, far);
		glTexCoord2f(cropX / 2, cropY / 2); glVertex3f(centerX, centerY, centerZ);
	glEnd();
}