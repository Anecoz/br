#include "Text.h"
#include "FontRenderer.h"
#include <iostream>

using namespace std;

Text::Text(string text, float x, float y, int size) {
	this->text = text;
	this->x = x;
	this->y = y;
	this->size = size;

	// Add this text to the fontrenderer
	FontRenderer::addText(this);
}

Text::~Text() {
	FontRenderer::removeText(this);
}

bool Text::operator==(const Text& rhs) {
	return (text == rhs.text &&
		size == rhs.size &&
		x == rhs.x &&
		y == rhs.y);
}