#pragma once

#include <vector>

extern void utilityInit();

extern float sqrtOf2;

extern float getRandFloat(float upperExclusive);
extern unsigned getRandUnsigned(unsigned upperExclusive);

extern float clamp(float x, float lower, float higher);

extern std::vector<float*> circleCoords;

extern unsigned stepsSpace;
extern void getSphereCoords(unsigned i, unsigned j, float p, float &x, float &y, float &z);

extern void utilityClear();

/*
extern unsigned stepsSpace, stepsTime;
extern void getSphereWrapCoords(float x1, float y1, float p1, float &x2, float &y2, float &z2);
extern void getSphereWrapCoords(unsigned i, unsigned j, float p1, float &x2, float &y2, float &z2);
*/