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

	string text;
	float x;
	float y;
	int size;

	bool getVisibility() { return visible; }
	void setVisibility(bool val) { visible = val; }

	bool operator==(const Text& rhs);

private:
	bool visible = true;
};

