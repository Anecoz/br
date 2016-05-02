#include "Button.h"
#include "../../Utils/MathUtils.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/MousePosInput.h"

#include <iostream>

Button::Button(string text, int textSize, glm::vec2 position) {
	m_text = text;
	m_textSize = textSize;
	m_position = position;
	m_width = 0.14f;
	m_height = 0.05f;
	setupText();
}

Button::Button(string text, int textSize, glm::vec2 position, float width, float height) {
	m_text = text;
	m_textSize = textSize;
	m_position = position;
	m_width = width;
	m_height = height;
	setupText();
}

void Button::setCallback(const std::function<void()> &callback) {
	f_callback = callback;
}

void Button::setupText() {
	p_text = new Text(m_text, m_position.x, m_position.y, m_textSize);
}

void Button::update() {
	glm::vec2 mouseGUIPos = MathUtils::screenSpaceToGUI(MousePosInput::getPosition());
	bool isInside = MathUtils::isWithinGUIBox(mouseGUIPos, m_position.x, m_position.y - m_height, m_width, m_height);
	if (MouseButtonInput::isMouseLeftDown()) {
		if (!m_pressing && isInside) {
			m_pressing = true;
		}
	}
	else if (m_pressing && isInside) {
		m_pressing = false;
		f_callback();
	}
	else if (isInside) {
		p_text->size = m_textSize * 1.5f;
	}
	else {
		m_pressing = false;
		p_text->size = m_textSize;
	}
}

void Button::remove() {
	delete p_text;
	p_text = nullptr;
}

Button::~Button() {
	remove();
}
