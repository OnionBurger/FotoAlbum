#pragma once

#include "TextureTransition.h"

class Bring : public TextureTransition {
	float distance;

	void actualDraw(int windowWidth, int windowHeight) const;

public:
	Bring(long duration);
};