#pragma once
#include <string>

using std::string;

// Holds information about a piece of text in the game
class Text
{
public:
	Text(string text, float x, float y, int size);
	~Text();

	string text;
	float x;
	float y;
	int size;

	bool operator==(const Text& rhs);
};

