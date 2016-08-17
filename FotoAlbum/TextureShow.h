#pragma once

#include <vector>
#include <string>

class Texture;
class TextureTransition;
class Standing;

class TextureShow {
	unsigned textureCurrIndex;
	std::vector<Texture*> textures;
	void randTex();

	TextureTransition *transitionCurr;
	TextureTransition *transitionStanding;
	std::vector<TextureTransition*> transitionsEnter, transitionsExit;
	void chooseTrans();

	int order; // 0 - alphabetical, 1 - random
	int phase;
	long durationStand, durationTrans;
	bool paused;

	void addTransition(const std::string desc);

	void loadTextures(const char *folderPath, const char *extension);
	void addTex(Texture *tex);

	void syncTrans();

	void prevTex();
	void nextPhase();
	void nextTex();

public:
	TextureShow();
	
	void init();
	void loadTextures(const char *folderPath);

	void pauseToggle();
	void forcePrev();
	void forceNext();
	
	void time(long elapsedMs);
	void draw(int windowWidth, int windowHeight) const;

	~TextureShow();
};