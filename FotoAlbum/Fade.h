#pragma once

#include "TextureTransition.h"

class Fade : public TextureTransition {
	void actualDraw(int windowWidth, int windowHeight) const;

public:
	Fade(long duration);
};