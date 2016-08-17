#pragma once

#include "TextureTransition.h"

class Standing : public TextureTransition {
	void actualDraw(int windowWidth, int windowHeight) const;

public:
	Standing(long duration) : TextureTransition(duration) {}
};