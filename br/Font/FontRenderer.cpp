#include "FontRenderer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <glm\glm.hpp>
#include "..\Graphics\Shaders\ShaderHandler.h"
#include "../Utils/MathUtils.h"

using namespace std;

GLuint FontRenderer::fontTexId;
GLuint FontRenderer::vbo;
FT_Library FontRenderer::ft;
FT_Face FontRenderer::face;
float FontRenderer::sx;
float FontRenderer::sy;
vector<Text*> FontRenderer::textList;

FontRenderer::FontRenderer() {	
}

FontRenderer::~FontRenderer() {	
}

void FontRenderer::init(int screenWidth, int screenHeight) {
	setupTexture();
	setupVBO();

	if (FT_Init_FreeType(&ft)) {
		cerr << "could not init freetype" << endl;
	}

	if (FT_New_Face(ft, "Roboto-Regular.ttf", 0, &face)) {
		cerr << "Could not open font." << endl;
	}
	setPixelSize(48);

	sx = 2.0 / (float)screenWidth;
	sy = 2.0 / (float)screenHeight;
}

void FontRenderer::cleanUp() {
	glDeleteTextures(1, &fontTexId);
	glDeleteBuffers(1, &vbo);
}

void FontRenderer::addText(Text* text) {
	textList.push_back(text);
}

void FontRenderer::removeText(Text* textToRemove) {
	for (auto iter = textList.begin(); iter != textList.end(); ++iter)
	{
		if (*iter == textToRemove) {
			textList.erase(iter);
			break;
		}
	}
}

void FontRenderer::setPixelSize(int size) {
	FT_Set_Pixel_Sizes(face, 0, size);
}

void FontRenderer::prepareRender() {
	ShaderHandler::fontShader->comeHere();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontTexId);
	glDisable(GL_DEPTH_TEST);
}

void FontRenderer::render() {
	prepareRender();
	const char *p;
	ShaderHandler::fontShader->uploadVec(glm::vec4(1, 1, 1, 1), "color");
	// Loop through all texts
	for (Text* textEntry : textList) {
		const char* text = textEntry->text.c_str();
		float x = textEntry->x;
		float y = textEntry->y;
		vec2 pos{ x, y };
		MathUtils::GUItoOpenGLCoord(pos);
		x = pos.x;
		y = pos.y;
		setPixelSize(textEntry->size);
		for (p = text; *p; p++) {
			if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			float x2 = x + face->glyph->bitmap_left * sx;
			float y2 = -y - face->glyph->bitmap_top * sy;
			float w = face->glyph->bitmap.width * sx;
			float h = face->glyph->bitmap.rows * sy;

			GLfloat box[4][4] = {
				{ x2,     -y2    , 0, 0 },
				{ x2 + w, -y2    , 1, 0 },
				{ x2,     -y2 - h, 0, 1 },
				{ x2 + w, -y2 - h, 1, 1 },
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			x += (face->glyph->advance.x / 64) * sx;
			y += (face->glyph->advance.y / 64) * sy;
		}
	}
	
	finishRender();
}

void FontRenderer::finishRender() {
	glDisable(GL_BLEND);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	ShaderHandler::fontShader->pissOff();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

void FontRenderer::setupVBO() {
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FontRenderer::setupTexture() {	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &fontTexId);
	glBindTexture(GL_TEXTURE_2D, fontTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}