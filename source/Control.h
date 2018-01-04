#pragma once

#include <stdlib.h>
#include "glut.h"
#include "GL.H"
#include <vector>

class TextureShow;

class Control {
	int windowWidth, windowHeight;
	int windowPrevWidth, windowPrevHeight;

	TextureShow *textures;

	float toAngle(int rot) const { return rot > 0 ? +5.f : -5.f; }
	float isX(int rot) const { return abs(rot) == 1; }
	float isY(int rot) const { return abs(rot) == 2; }
	float isZ(int rot) const { return abs(rot) == 3; }
	std::vector<int> rotations;

	bool ortho;
	float perspectiveDistance;
	void makeProjection();

	bool fullscreen;
	void toggleFullscreen();

public:
	Control();

	void init();

	void reshape(int width, int height);
	int getWidth() const { return windowWidth; }
	int getHeight() const { return windowHeight; }

	void keyDown(unsigned char key);
	void specialKeyDown(int key);

	void time(long elapsedMs);
	void draw() const;

	~Control();
};