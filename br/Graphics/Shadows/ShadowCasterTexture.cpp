#include "ShadowCasterTexture.h"
#include "../../Utils/GraphicsUtils.h"
#include <iostream>

using namespace std;


ShadowCasterTexture::ShadowCasterTexture() {

}

ShadowCasterTexture::~ShadowCasterTexture() {
	glDeleteTextures(1, &texId);
}

void ShadowCasterTexture::init(int width, int height) {
	this->width = width;
	this->height = height;
	data = new GLubyte[width*height*4];
}

void ShadowCasterTexture::addAt(int tx, int ty, GLubyte isShadowCaster) {
	data[(ty*width + tx)*4 + 0] = isShadowCaster;
	data[(ty*width + tx)*4 + 1] = isShadowCaster;
	data[(ty*width + tx)*4 + 2] = isShadowCaster;
	data[(ty*width + tx)*4 + 3] = isShadowCaster;
}

void ShadowCasterTexture::convertToTexture() {

	// DEBUG (SAVE FOR LATER)
	/*for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) {
			cout << "data at: " << x << "," << y << " is: " << static_cast<unsigned>(data[y * width + x]) << endl;
		}*/
	
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data; data = nullptr;

	// DEBUG
	/*GLubyte* back = new GLubyte[width*height*4];
	glBindTexture(GL_TEXTURE_2D, texId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, back);

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) {
			cout << "back at: " << x << "," << y << " is: " << static_cast<unsigned>(back[y * width + x]) << endl;
		}

	delete[] back;*/
}

void ShadowCasterTexture::bind() {
	glBindTexture(GL_TEXTURE_2D, texId);
}

void ShadowCasterTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}