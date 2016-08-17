#include "EllipsoidWrap.h"
#include "utility.h"

EllipsoidWrap::EllipsoidWrap(long duration) : TextureTransition(duration) {
	t = 0.2f;
}

void EllipsoidWrap::actualDraw(int windowWidth, int windowHeight) const {
	glPushMatrix();
	glScalef(getTexture()->getWidth(), getTexture()->getHeight(), getTexture()->getWidth());

	float p = getTimeRatio();
	if (p <= t) p = 0;
	else p = (t - p) / (t - 1);

	for (unsigned x = 0; x < stepsSpace; ++x) {
		for (unsigned y = 0; y < stepsSpace; ++y) {
			float vx0, vy0, vz0;
			float vx1, vy1, vz1;
			float vx2, vy2, vz2;
			float vx3, vy3, vz3;

			float tx0, ty0;
			float tx1, ty1;
			float tx2, ty2;
			float tx3, ty3;

			getSphereCoords(x, y, p, vx0, vy0, vz0);
			getSphereCoords(x + 1, y, p, vx1, vy1, vz1);
			getSphereCoords(x + 1, y + 1, p, vx2, vy2, vz2);
			getSphereCoords(x, y + 1, p, vx3, vy3, vz3);

			tx0 = ((float)x) / stepsSpace; ty0 = ((float)y) / stepsSpace;
			tx1 = ((float)x + 1) / stepsSpace; ty1 = ((float)y) / stepsSpace;
			tx2 = ((float)x + 1) / stepsSpace; ty2 = ((float)y + 1) / stepsSpace;
			tx3 = ((float)x) / stepsSpace; ty3 = ((float)y + 1) / stepsSpace;

			tx0 *= getTexture()->getCropX(); ty0 *= getTexture()->getCropY();
			tx1 *= getTexture()->getCropX(); ty1 *= getTexture()->getCropY();
			tx2 *= getTexture()->getCropX(); ty2 *= getTexture()->getCropY();
			tx3 *= getTexture()->getCropX(); ty3 *= getTexture()->getCropY();

			glBegin(GL_TRIANGLES);
				glTexCoord2f(tx0, ty0);
				glVertex3f(vx0, vy0, vz0);
				glTexCoord2f(tx1, ty1);
				glVertex3f(vx1, vy1, vz1);
				glTexCoord2f(tx3, ty3);
				glVertex3f(vx3, vy3, vz3);
				
				glTexCoord2f(tx1, ty1);
				glVertex3f(vx1, vy1, vz1);
				glTexCoord2f(tx2, ty2);
				glVertex3f(vx2, vy2, vz2);
				glTexCoord2f(tx3, ty3);
				glVertex3f(vx3, vy3, vz3);
			glEnd();
		}
	}

	glPopMatrix();
}