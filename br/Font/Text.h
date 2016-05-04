#pragma once
#include <string>

using std::string;

// Holds information about a piece of text in the game
class Text
{
public:
	// Take x and y in GUI coordinate system
	Text(string text, float x, float y, int size);
	~Text();	

	bool getVisibility() { return visible; }
	void setVisibility(bool val) { visible = val; }

	void setText(string text) { this->text = text; }
	string& getText() { return text; }
	float getX() { return x; }
	float getY() { return y; }
	int getSize() { return size; }
	void setSize(int size) { this->size = size; }

	bool operator==(const Text& rhs);

	string text;
private:
	bool visible = true;
	float x;
	float y;
	int size;
};

