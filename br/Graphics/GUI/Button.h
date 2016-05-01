#pragma once

#include <glm\glm.hpp>
#include <string>
#include <functional>

#include "../../Font/Text.h"

using namespace std;

class Button
{
public:
	Button(string text, int textSize, glm::vec2 position);
	Button(string text, int textSize, glm::vec2 position, float width, float height);
	~Button();

	void update();

	float getWidth() { return m_width; };
	float getHeight() { return m_height; };

	void setPosition(glm::vec2 position) { m_position = position; };
	void setCallback(const std::function<void()> &callback);

	void remove();
private:
	void setupText();

	float m_width;
	float m_height;
	int m_textSize;
	glm::vec2 m_position;
	string m_text;
	bool m_pressing;
	Text* p_text;

	function<void()> m_callback;
};

