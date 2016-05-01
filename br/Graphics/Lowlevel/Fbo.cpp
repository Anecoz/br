#include "Fbo.h"

Fbo::Fbo(int width, int height) {
	this->width = width;
	this->height = height;
	initialiseFramebuffer();
}

Fbo::~Fbo() {
	glDeleteFramebuffers(1, &fboId);
	glDeleteTextures(1, &colourTextureId);
}

void Fbo::bind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
	glViewport(0, 0, width, height);
}

void Fbo::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720); // ADD CORRECT RESOLUTION
}

void Fbo::initialiseFramebuffer() {
	createFramebuffer();
	createTextureAttachment();
	unbind();
}

void Fbo::createFramebuffer() {
	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void Fbo::createTextureAttachment() {
	glGenTextures(1, &colourTextureId);
	glBindTexture(GL_TEXTURE_2D, colourTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourTextureId, 0);
}