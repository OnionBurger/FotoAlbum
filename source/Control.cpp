#include "Control.h"
#include"utility.h"
#include "TextureShow.h"
#include <iostream>

Control::Control() {
	textures = new TextureShow();

	ortho = true;
	perspectiveDistance = 1000.f;

	fullscreen = false;
}

void Control::init() {
	std::cout << "Initiating..." << std::endl;
	utilityInit();
	std::cout << std::endl;
	textures->init();
}

void Control::makeProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortho) {
		glOrtho(0, windowWidth, 0, windowHeight, -1000, +1000);
	} else {
		glFrustum(-windowWidth / (2 * perspectiveDistance), 
			+windowWidth / (2 * perspectiveDistance), 
			-windowHeight / (2 * perspectiveDistance), 
			+windowHeight / (2 * perspectiveDistance), 
			1, 2000);
	}
}

void Control::reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, (GLint)width, (GLint)height);
	makeProjection();
}

void Control::toggleFullscreen() {
	fullscreen = !fullscreen;

	if (fullscreen) {
		windowPrevWidth = windowWidth;
		windowPrevHeight = windowHeight;
		glutFullScreen();
	} else {
		glutReshapeWindow(windowPrevWidth, windowPrevHeight);
	}
}

void Control::time(long elapsedMs) {
	textures->time(elapsedMs);
}

void Control::keyDown(unsigned char key) {
	if (key == ' ' || key == 'c') { // SPACE
		textures->pauseToggle();
	} else if (key == 'z') {
		textures->forcePrev();
	} else if (key == 13 || key == 'x') { // ENTER or X
		textures->forceNext();
	} else if (key == 'f') {
		toggleFullscreen();
	} else if (key == 'w') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == +1) rotations.pop_back();
		else rotations.push_back(-1);
	} else if (key == 's') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == -1) rotations.pop_back();
		else rotations.push_back(+1);
	} else if (key == 'a') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == +2) rotations.pop_back();
		else rotations.push_back(-2);
	} else if (key == 'd') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == -2) rotations.pop_back();
		else rotations.push_back(+2);
	} else if (key == 'q') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == -3) rotations.pop_back();
		else rotations.push_back(+3);
	} else if (key == 'e') {
		if (!rotations.empty() && rotations[rotations.size() - 1] == +3) rotations.pop_back();
		else rotations.push_back(-3);
	} else if (key == 'r') {
		rotations.clear();
	} else if (key == 'v') {
		ortho = !ortho;
		makeProjection();
	}
}

void Control::specialKeyDown(int key) {
}

void Control::draw() const {
	glPushMatrix();
		if (ortho) glTranslatef(windowWidth / 2, windowHeight / 2, 0);
		else glTranslatef(0, 0, -perspectiveDistance);
		
		for (unsigned i = rotations.size() - 1; i < rotations.size(); --i)
			glRotatef(toAngle(rotations[i]), isX(rotations[i]), isY(rotations[i]), isZ(rotations[i]));

		textures->draw(windowWidth, windowHeight);
	glPopMatrix();
}

Control::~Control() {
	delete textures;
	utilityClear();
}