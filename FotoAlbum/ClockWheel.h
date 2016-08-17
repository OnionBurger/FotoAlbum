#pragma once

#include "TextureTransition.h"
#include "utility.h"

class ClockWheel : public TextureTransition {
	std::vector<float*> coordsVertex, coordsTex;

	void actualDraw(int windowWidth, int windowHeight) const;

public:
	ClockWheel(long duration);

	~ClockWheel();
};