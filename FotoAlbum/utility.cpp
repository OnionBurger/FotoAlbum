#include "utility.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

float sqrtOf2(sqrt(2.f));

std::vector<float*> circleCoords;

unsigned stepsSpace;
float ***sphereCoords;

void utilityInitCircleCoords() {
	unsigned circleN = 1024;
	for (unsigned i = 0; i < circleN; ++i) {
		circleCoords.push_back(new float[2]);

		float angleDeg = +90.f - i * 360.f / circleN;
		float angleRad = angleDeg * 3.14f / 180;
		
		circleCoords[i][0] = cos(angleRad) * 0.5f;
		circleCoords[i][1] = sin(angleRad) * 0.5f;
	}
}

const float piConstant = 3.1416f;

void utilityInitSphereCoords() {
	stepsSpace = 64;

	sphereCoords = new float**[stepsSpace + 1];

	for (unsigned i = 0; i <= stepsSpace; ++i) {
		sphereCoords[i] = new float*[stepsSpace + 1];

		for (unsigned j = 0; j <= stepsSpace; ++j) {
			sphereCoords[i][j] = new float[3];
			
			float W = (float)stepsSpace, H = (float)stepsSpace;

			float y = (j / H - 0.5f) / 2.f;
			float r = sqrt(1.f / 16.f - y * y);
			float phi = (i / W - 0.5f) * 2.f * piConstant;
			float x = r * sin(phi);
			float z = r * cos(abs(phi));

			sphereCoords[i][j][0] = x;
			sphereCoords[i][j][1] = y;
			sphereCoords[i][j][2] = z;
		}
	}
}

void utilityInit() {
	srand(time(0));
		
	utilityInitCircleCoords();
	utilityInitSphereCoords();
}

float getRandFloat(float upperExclusive) {
	return (((float)rand())/RAND_MAX) * upperExclusive;
}

unsigned getRandUnsigned(unsigned upperExclusive) {
	return (unsigned)(getRandFloat((float)upperExclusive));
}

float clamp(float x, float lower, float higher) {
	if (x < lower) return lower;
	else if (x > higher) return higher;
	else return x;
}

void getSphereCoords(unsigned i, unsigned j, float p, float &x, float &y, float &z) {
	p = clamp(p, 0, 1);

	float x0 = ((float)i) / stepsSpace - 0.5f;
	float y0 = ((float)j) / stepsSpace - 0.5f;
	float z0 = 0;

	x = sphereCoords[i][j][0];
	y = sphereCoords[i][j][1];
	z = sphereCoords[i][j][2];

	x = (1 - p) * x + p * x0;
	y = (1 - p) * y + p * y0;
	z = (1 - p) * z + p * z0;
}

void utilityClearCircleCoords() {
	for (unsigned i = 0; i < circleCoords.size(); ++i)
		delete [] circleCoords[i];
}

void utilityClearSphereCoords() {
	for (unsigned i = 0; i < stepsSpace; ++i) {
		for (unsigned j = 0; j < stepsSpace; ++j) {
			delete [] sphereCoords[i][j];
		}
		delete [] sphereCoords[i];
	}
	delete [] sphereCoords;
}

void utilityClear() {
	utilityClearCircleCoords();
	utilityClearSphereCoords();
}

/*
unsigned stepsSpace, stepsTime;
float ****sphereWrapCoords;

const float piConstant = 3.1416f;

void utilityInitSphereWrapCoords() {
	stepsSpace = 64;
	stepsTime = 2048;

	sphereWrapCoords = new float***[stepsSpace];

	for (unsigned i = 0; i < stepsSpace; ++i) {
		sphereWrapCoords[i] = new float**[stepsSpace];

		for (unsigned j = 0; j < stepsSpace; ++j) {
			sphereWrapCoords[i][j] = new float*[stepsTime];
			
			for (unsigned k = 0; k < stepsTime; ++k) {
				sphereWrapCoords[i][j][k] = new float[2];

				float x1 = ((float)i) / (stepsSpace - 1) - 0.5f;
				float y1 = ((float)j) / (stepsSpace - 1) - 0.5f;
				float p1 = ((float)k) / (stepsTime - 1);

				float absx1 = abs(x1);
				float sgnx1 = x1 < 0 ? -1.f : (x1 > 0 ? +1.f : 0.f);

				float r = sqrt(0.25f - y1 * y1);
				float phi = 2 * piConstant * absx1;
				float l = 0.5f - r;

				float phi1 = phi * p1;

				if (i == 0 || i == stepsSpace - 1) sphereWrapCoords[i][j][k][0] = x1 * (1 - p1);
				else sphereWrapCoords[i][j][k][0] = sgnx1 * r / sin(phi1);

				sphereWrapCoords[i][j][k][1] = -(l * p1 + abs(sphereWrapCoords[i][j][k][0]) * tan(phi1 / 2.f));
			}
		}
	}
}

void getSphereWrapCoords(float x1, float y1, float p1, float &x2, float &y2, float &z2) {
	unsigned i = ((unsigned)(clamp(x1 + 0.5f, 0, 1) * (stepsSpace - 1)));
	if (i > stepsSpace - 1) i = stepsSpace - 1;

	unsigned j = ((unsigned)(clamp(y1 + 0.5f, 0, 1) * (stepsSpace - 1)));
	if (j > stepsSpace - 1) j = stepsSpace - 1;

	unsigned k = ((unsigned)(clamp(p1, 0, 1) * (stepsTime - 1)));
	if (k > stepsTime - 1) k = stepsTime - 1;

	x2 = sphereWrapCoords[i][j][k][0];
	y2 = y1;
	z2 = sphereWrapCoords[i][j][k][1];
}

void getSphereWrapCoords(unsigned i, unsigned j, float p1, float &x2, float &y2, float &z2) {
	unsigned k = ((unsigned)(clamp(p1, 0, 1) * (stepsTime - 1)));
	if (k > stepsTime - 1) k = stepsTime - 1;

	x2 = sphereWrapCoords[i][j][k][0];
	y2 = ((float)j) / (stepsSpace - 1) - 0.5f;
	if (y2 > stepsSpace - 1) y2 = stepsSpace - 1.f;
	z2 = sphereWrapCoords[i][j][k][1];
}

void utilityClearSphereWrapCoords() {
	for (unsigned i = 0; i < stepsSpace; ++i) {
		for (unsigned j = 0; j < stepsSpace; ++j) {			
			for (unsigned k = 0; k < stepsTime; ++k) {
				delete [] sphereWrapCoords[i][j][k];
			}

			delete [] sphereWrapCoords[i][j];
		}

		delete [] sphereWrapCoords[i];
	}

	delete [] sphereWrapCoords;
}
*/