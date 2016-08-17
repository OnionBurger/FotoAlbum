#include "Texture.h"
#include <cctype>
#include <vector>
#include <iostream>
#include "corona.h"

Texture::Texture() {
	texParam = GL_NEAREST;
}

bool Texture::load(const std::string texFile) {
	std::cout << "Opening: " << texFile << std::endl;

	glGenTextures(1, &name);

	glBindTexture(GL_TEXTURE_2D, name);

	corona::Image *image = corona::OpenImage(texFile.c_str(), corona::PF_R8G8B8A8);
	if (!image) {
		std::cout << "\tError reading file!" << std::endl;
		return false;
	}

	corona::FlipImage(image, corona::CA_X);

	int imageToPow2Width = 1; while (imageToPow2Width < image->getWidth()) imageToPow2Width *= 2;
	int imageToPow2Height = 1; while (imageToPow2Height < image->getHeight()) imageToPow2Height *= 2;

	unsigned char *coronaPixels = (unsigned char*)image->getPixels();

	int colLen = 4;

	std::vector<unsigned char> imageToPow2(imageToPow2Width * imageToPow2Height * colLen);
	for (int y = 0; y < image->getHeight(); ++y) {
		for (int x = 0; x < image->getWidth(); ++x) {
			for (int c = 0; c < colLen; ++c) {
				imageToPow2[colLen * imageToPow2Width * y + colLen * x + c] = coronaPixels[colLen * image->getWidth() * y + colLen * x + c];
			}
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageToPow2Width, imageToPow2Height, 
		0, GL_RGBA, GL_UNSIGNED_BYTE, &imageToPow2[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);

	width = image->getWidth();
	height = image->getHeight();

	cropX = ((float)width) / imageToPow2Width;
	cropY = ((float)height) / imageToPow2Height;

	file = texFile;
	for (unsigned i = 0; i < file.size(); ++i)
		file[i] = tolower(file[i]);

	delete image;

	return true;
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, name);
}

bool Texture::lexBefore(const Texture *T) const {
	return file.compare(T->file) < 0;
}

void Texture::draw(int windowWidth, int windowHeight) const {
	int left = -width / 2;
	int right = left + width;
	int bottom = -height / 2;
	int top = bottom + height;

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2i(left, bottom);
		glTexCoord2f(cropX, 0); glVertex2i(right, bottom);
		glTexCoord2f(cropX, cropY); glVertex2i(right, top);
		glTexCoord2f(0, cropY); glVertex2i(left, top);
	glEnd();
}

Texture::~Texture() {
}