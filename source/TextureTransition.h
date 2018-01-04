#pragma once

#include "Texture.h"

class TextureTransition {
	bool reverse;
	Texture *texture;
	
	long timeSum, duration;

protected:
	long getTimeSum() const { return timeSum; }
	long getDuration() const { return duration; }
	float getTimeRatio(bool mindReverse = true) const;

	const Texture* getTexture() const { return texture; }

	virtual void actualDraw(int windowWidth, int windowHeight) const =0;

public:
	TextureTransition(long duration);

	bool getReverse() const { return reverse; }
	void setReverse(bool rev) { reverse = rev; }

	void setTexture(Texture *tex) { texture = tex; }
	
	long time(long elapsedMs);
	void resetTime() { timeSum = 0; }
	bool isOver() const { return timeSum >= duration; }

	void draw(int windowWidth, int windowHeight) const;

	virtual ~TextureTransition();
};