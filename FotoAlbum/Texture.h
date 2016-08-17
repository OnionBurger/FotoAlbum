#pragma once

#include <stdlib.h>
#include <string>
#include "glut.h"
#include "GL.H"

class Texture {
	int width, height;
	float cropX, cropY;
	GLuint name;
	std::string file;

	GLint texParam;

public:
	Texture();

	bool load(const std::string texFile);

	void bind() const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	float getCropX() const { return cropX; }
	float getCropY() const { return cropY; }

	const char* getFile() const { return file.c_str(); }

	bool lexBefore(const Texture *T) const;

	void draw(int windowWidth, int windowHeight) const;

	~Texture();
};