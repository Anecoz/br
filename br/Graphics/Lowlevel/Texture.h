#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>

using namespace std;

class Texture
{
public:
	Texture(unsigned width, unsigned height, GLuint id, GLint type);
	Texture(string path, float scale);
	Texture(string path);

	~Texture();

	void bind();
	void unbind();

	float getWidthAfterScale() { return widthAfterScale; }
	float getHeightAfterScale() { return heightAfterScale; }
	float getScale() { return scale; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	GLuint getId() { return texId; }

private:
	unsigned width, height;
	float widthAfterScale;
	float heightAfterScale;
	float scale;
	GLuint texId;
	GLint type = GL_TEXTURE_2D;

	void setSizes();
};

