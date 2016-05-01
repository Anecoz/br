#include "Texture.h"
#include "../../Utils/GraphicsUtils.h"

Texture::Texture(unsigned width, unsigned height, GLuint id, GLint type) {
	this->width = width;
	this->height = height;
	this->texId = id;
	this->type = type;
}

Texture::Texture(string path, float scale) {
	this->scale = scale;
	texId = GraphicsUtils::loadPNGToTexture(path.c_str(), width, height);
	setSizes();
}

Texture::Texture(string path) {
	this->scale = 1.0f;
	texId = GraphicsUtils::loadPNGToTexture(path.c_str(), width, height);	
}

void Texture::bind() {
	glBindTexture(type, texId);
}

void Texture::unbind() {
	glBindTexture(type, 0);
}

void Texture::setSizes() {
	if (width > 1.0 || height > 1.0) {
		if (width >= height) {
			heightAfterScale = height / width;
			widthAfterScale = 1.0f;
		}
		else {
			widthAfterScale = width / height;
			heightAfterScale = 1.0f;
		}
	}

	widthAfterScale *= scale;
	heightAfterScale *= scale;
}

Texture::~Texture() {
	glDeleteTextures(1, &texId);
}
