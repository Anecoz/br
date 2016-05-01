#pragma once
#include <GL\glew.h>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Text.h"

using std::vector;

class FontRenderer
{
public:
	FontRenderer();
	~FontRenderer();

	static void init(int screenWidth, int screenHeight);
	static void cleanUp();

	static void setPixelSize(int size);
	static void addText(Text* text);
	static void removeText(Text* textToRemove);
	static void render();

private:
	static GLuint fontTexId;
	static GLuint vbo;
	static FT_Library ft;
	static FT_Face face;
	static float sx;
	static float sy;
	static vector<Text*> textList;

	static void setupTexture();
	static void setupVBO();

	static void prepareRender();
	static void finishRender();
};

