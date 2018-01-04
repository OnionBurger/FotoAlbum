#pragma once

#include "TextureTransition.h"

class WipeDown : public TextureTransition {
	void actualDraw(int windowWidth, int windowHeight) const;

public:
	WipeDown(long duration);
};