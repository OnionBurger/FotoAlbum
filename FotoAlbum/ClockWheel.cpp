#include "ClockWheel.h"

ClockWheel::ClockWheel(long duration) : TextureTransition(duration) {
	for (unsigned i = 0; i < circleCoords.size(); ++i) {
		coordsVertex.push_back(new float[2]);
		coordsVertex[i][0] = clamp(circleCoords[i][0] * sqrtOf2, -0.5, +0.5);
		coordsVertex[i][1] = clamp(circleCoords[i][1] * sqrtOf2, -0.5, +0.5);
		
		coordsTex.push_back(new float[2]);
		coordsTex[i][0] = coordsVertex[i][0] + 0.5f;
		coordsTex[i][1] = coordsVertex[i][1] + 0.5f;
	}
}

void ClockWheel::actualDraw(int windowWidth, int windowHeight) const {
	unsigned points = getTimeRatio() * coordsVertex.size();
	if (points > coordsVertex.size()) points = coordsVertex.size();

	if (points == 0) return;

	glPushMatrix();
		glScalef(getTexture()->getWidth(), getTexture()->getHeight(), 1);

		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(getTexture()->getCropX() / 2, getTexture()->getCropY() / 2);
			glVertex2f(0, 0);

			glTexCoord2f(coordsTex[0][0] * getTexture()->getCropX(), coordsTex[0][1] * getTexture()->getCropY());
			glVertex2f(coordsVertex[0][0], coordsVertex[0][1]);

			for (unsigned i = 0; i < points && i + 1 < coordsVertex.size(); ++i) {
				glTexCoord2f(coordsTex[i + 1][0] * getTexture()->getCropX(), coordsTex[i + 1][1] * getTexture()->getCropY());
				glVertex2f(coordsVertex[i + 1][0], coordsVertex[i + 1][1]);
			}

			if (points == coordsVertex.size()) {
				glTexCoord2f(coordsTex[0][0] * getTexture()->getCropX(), coordsTex[0][1] * getTexture()->getCropY());
				glVertex2f(coordsVertex[0][0], coordsVertex[0][1]);
			}
		glEnd();
	glPopMatrix();
}

ClockWheel::~ClockWheel() {
	for (unsigned i = 0; i < coordsVertex.size(); ++i)
		delete [] coordsVertex[i];
	
	for (unsigned i = 0; i < coordsTex.size(); ++i)
		delete [] coordsTex[i];
}