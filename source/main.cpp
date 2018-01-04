#include <Windows.h>
#include "GL.H"
#include "glu.h"
#include "glut.h"
#include "Control.h"
#include <chrono>

Control *control;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	control->init();
}

void reshape(int width, int height) {
	control->reshape(width, height);
}

void timeProc() {
	static long prevTime = 0;

	long elapsed = 0;
	if (prevTime == 0) {
		prevTime = timeGetTime();
	} else {
		elapsed = timeGetTime() - prevTime; // in ms

		if (elapsed < 40) {
			Sleep(40 - elapsed);
			glFinish();
		} else {
			control->time(elapsed);
			prevTime += elapsed;
		}
	}	
}

void display() {
	timeProc();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	control->draw();

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
	control->keyDown(key);
}

void specialKeyDown(int key, int x, int y) {
	control->specialKeyDown(key);
}

void clear() {
	delete control;
}

int main(int argc, char **argv) {
	int w = 640, h = 480;

	control = new Control();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tabla");

	init();
	control->reshape(w, h);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyDown);
	//glutKeyboardUpFunc();
	glutSpecialFunc(specialKeyDown);
	//glutSpecialUpFunc();
	//glutMouseFunc();
	//glutMotionFunc();
	//glutPassiveMotionFunc();

	glutMainLoop();

	clear();
	return 0;
}