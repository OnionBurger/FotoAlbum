#include "TextureShow.h"
#include <Windows.h>
#include "Texture.h"
#include <iostream>
#include <fstream>
#include "utility.h"

#include "Standing.h"
#include "Sudden.h"
#include "WipeDown.h"
#include "Fade.h"
#include "NewsSpin.h"
#include "ClockWheel.h"
#include "EllipsoidWrap.h"
#include "Bring.h"
#include "Cone.h"

TextureShow::TextureShow() {
	phase = -1;
	durationStand = 2000;
	durationTrans = 1000;
	order = 0;
	paused = false;
	transitionCurr = 0;
}

void TextureShow::addTransition(const std::string desc) {
	if (desc.empty() || (desc[0] != '+' && desc[0] != '-'))
		return;

	bool enter = desc[0] == '+';

	std::string name(desc.substr(1));
	for (unsigned i = 0; i < name.size(); ++i) name[i] = tolower(name[i]);
	
	TextureTransition *transition = 0;
	
	if (name == "sudden") transition = new Sudden();
	else if (name == "wipe" || name == "wipedown") transition = new WipeDown(durationTrans);
	else if (name == "fade") transition = new Fade(durationTrans);
	else if (name == "newsspin" || name == "news" || name == "spin") transition = new NewsSpin(durationTrans);
	else if (name == "clock" || name == "clockwheel") transition = new ClockWheel(durationTrans);
	else if (name == "ellipsoid" || name == "ellipsoidwrap") transition = new EllipsoidWrap(durationTrans);
	else if (name == "bring") transition = new Bring(durationTrans);
	else if (name == "cone") transition = new Cone(durationTrans);

	if (transition != 0)
		(enter ? transitionsEnter : transitionsExit).push_back(transition);
}

void TextureShow::init() {
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	std::string folder;
	std::ifstream config("config.txt");
	if (!config.is_open()) {
		folder = "slike";
	} else {
		config >> folder;

		config >> order >> durationStand >> durationTrans;
		
		std::string desc;
		while (!config.eof()) {
			config >> desc;
			addTransition(desc);
		}

		config.close();
	}
	
	std::cout << "Folder: " << folder << std::endl;
	std::cout << "Order=" << (order ? "Alpha" : "Rand") << std::endl;
	std::cout << "DurStand=" << durationStand << std::endl;
	std::cout << "DurTrans=" << durationTrans << std::endl;
	
	std::cout << std::endl;
	loadTextures(folder.c_str());
	
	transitionStanding = new Standing(durationStand);

	if (transitionsEnter.empty()) transitionsEnter.push_back(new Sudden());
	if (transitionsExit.empty()) transitionsExit.push_back(new Sudden());

	for (unsigned i = 0; i < transitionsExit.size(); ++i)
		transitionsExit[i]->setReverse(true);

	phase = -1;
	chooseTrans();
	syncTrans();
}

void TextureShow::loadTextures(const char *folderPath, const char *extension) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	std::string searchStr(folderPath);
	searchStr += "/*.";
	searchStr += extension;
	hFind = FindFirstFile(searchStr.c_str(), &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind)
		return;

	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		
		std::string texFile(folderPath);
		texFile += "/";
		texFile += FindFileData.cFileName;
		
		Texture *tex = new Texture();
		if (tex->load(texFile)) addTex(tex);
		else delete tex;
	} while (FindNextFile(hFind, &FindFileData) != 0);
}

void TextureShow::loadTextures(const char *folderPath) {
	loadTextures(folderPath, "bmp");
	loadTextures(folderPath, "png");
	loadTextures(folderPath, "jpg");
	loadTextures(folderPath, "jpeg");

	textureCurrIndex = 0;
	textures[textureCurrIndex]->bind();

	std::cout << std::endl << "Drawing: " << textures[textureCurrIndex]->getFile() << std::endl;
}

void TextureShow::addTex(Texture *tex) {
	if (order != 0 || textures.empty() || textures[textures.size() - 1]->lexBefore(tex)) {
		textures.push_back(tex);
		return;
	}

	unsigned index;
	for (index = 0; index < textures.size(); ++index) {
		if (tex->lexBefore(textures[index]))
			break;
	}

	Texture *prev = tex;
	for (; index < textures.size(); ++index) {
		Texture *temp = textures[index];
		textures[index] = prev;
		prev = temp;
	}

	textures.push_back(prev);
}

void TextureShow::chooseTrans() {
	if (phase < 0) {
		unsigned index = getRandUnsigned(transitionsEnter.size());
		transitionCurr = transitionsEnter[index];
	} else if (phase == 0) {
		transitionCurr = transitionStanding;
	} else {
		unsigned index = getRandUnsigned(transitionsExit.size());
		transitionCurr = transitionsExit[index];
	}
}

void TextureShow::pauseToggle() {
	paused = !paused;
}

void TextureShow::forcePrev() {
	prevTex();
	if (!paused) {
		phase = -1;
		chooseTrans();
	}
	syncTrans();
}

void TextureShow::forceNext() {
	nextTex();
	if (!paused) {
		phase = -1;
		chooseTrans();
	}
	syncTrans();
}

void TextureShow::time(long elapsedMs) {
	if (paused) return;

	transitionCurr->time(elapsedMs);

	if (transitionCurr->isOver())
		nextPhase();
}

void TextureShow::syncTrans() {
	transitionCurr->setTexture(textures[textureCurrIndex]);
	transitionCurr->resetTime();
}

void TextureShow::randTex() {
	if (textures.size() == 1) {
		textureCurrIndex = 0;
		return;
	}

	unsigned index = getRandUnsigned(textures.size() - 1);
	if (index >= textureCurrIndex) ++index;

	textureCurrIndex = index;
}

void TextureShow::prevTex() {
	if (order == 0) {
		if (textureCurrIndex == 0) textureCurrIndex = textures.size() - 1;
		else --textureCurrIndex;
	} else {
		randTex();
	}

	textures[textureCurrIndex]->bind();
	std::cout << "Drawing: " << textures[textureCurrIndex]->getFile() << std::endl;
}

void TextureShow::nextPhase() {
	if (phase < 0) {
		phase = 0;
		chooseTrans();
		syncTrans();
	} else if (phase == 0) {
		phase = 1;
		chooseTrans();
		syncTrans();
	} else {
		nextTex();
		phase = -1;
		chooseTrans();
		syncTrans();
	}
}

void TextureShow::nextTex() {
	if (order == 0) {
		++textureCurrIndex;
		if (textureCurrIndex >= textures.size()) textureCurrIndex = 0;
	} else {
		randTex();
	}

	textures[textureCurrIndex]->bind();
	std::cout << "Drawing: " << textures[textureCurrIndex]->getFile() << std::endl;
}

void TextureShow::draw(int windowWidth, int windowHeight) const {
	Texture *currTex = textures[textureCurrIndex];

	glPushMatrix();
		if (currTex->getWidth() > windowWidth || currTex->getHeight() > windowHeight) {
			float scaleX = ((float)windowWidth) / currTex->getWidth();
			float scaleY = ((float)windowHeight) / currTex->getHeight();

			float scale = scaleX < scaleY ? scaleX : scaleY;

			glScalef(scale, scale, 1);
		}

		transitionCurr->draw(windowWidth, windowHeight);
	glPopMatrix();
}

TextureShow::~TextureShow() {
	for (unsigned i = 0; i < textures.size(); ++i)
		delete textures[i];

	delete transitionStanding;
	
	for (unsigned i = 0; i < transitionsEnter.size(); ++i)
		delete transitionsEnter[i];
	
	for (unsigned i = 0; i < transitionsExit.size(); ++i)
		delete transitionsExit[i];
}