#pragma once

#include "TextureTransition.h"

class NewsSpin : public TextureTransition {
	int spins;

	void actualDraw(int windowWidth, int windowHeight) const;

public:
	NewsSpin(long duration);
};