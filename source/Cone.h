#pragma once

#include "TextureTransition.h"

class Cone : public TextureTransition {
	void actualDraw(int windowWidth, int windowHeight) const;

public:
	Cone(long duration);
};