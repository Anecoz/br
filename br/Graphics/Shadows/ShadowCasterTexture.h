#pragma once

#include <GL\glew.h>

class ShadowCasterTexture
{
public:
	ShadowCasterTexture();
	~ShadowCasterTexture();

	void init(int width, int height);
	void addAt(int tx, int ty, GLubyte isShaderCaster);
	void convertToTexture();

	void bind();
	void unbind();

private:
	GLubyte* data;
	GLuint texId;
	int width;
	int height;
};

