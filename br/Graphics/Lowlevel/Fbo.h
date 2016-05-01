#pragma once

#include <GL\glew.h>

class Fbo
{
public:
	Fbo(int width, int height);
	~Fbo();

	void bind();
	void unbind();

	GLuint getColourTextureId() { return colourTextureId; }

private:
	int width;
	int height;
	GLuint fboId, colourTextureId;

	void initialiseFramebuffer();
	void createFramebuffer();
	void createTextureAttachment();

};

