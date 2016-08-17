#pragma once

#include "TextureTransition.h"

class Sudden : public TextureTransition {
	void actualDraw(int windowWidth, int windowHeight) const;

public:
	Sudden();
};