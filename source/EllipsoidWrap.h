#pragma once

#include "TextureTransition.h"

class EllipsoidWrap : public TextureTransition {
	float t;

	void actualDraw(int windowWidth, int windowHeight) const;

public:
	EllipsoidWrap(long duration);
};