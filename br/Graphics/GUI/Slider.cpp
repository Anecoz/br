#include "Slider.h"
#include "../../Utils/ResourceHandler.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Utils/MathUtils.h"

#include <iostream>

Slider::Slider(glm::vec2 position, float length, float& value) : m_value {value},
	GUIElement(ResourceHandler::sliderTexture, ResourceHandler::sliderQuad, position) {
	m_length = length;
	MAX = position.x + length;
	MIN = position.x;

	this->position.x = position.x + value * length;
}

Slider::~Slider() {
}

void Slider::update() {
	glm::vec2 mouseGUIPos = MathUtils::screenSpaceToGUI(MousePosInput::getPosition());

	// Check the dragging status of the whole window
	if (!m_isDragging) {
		if (MouseButtonInput::isMouseLeftDown() &&
			MathUtils::isWithinGUIBox(mouseGUIPos, position.x + 0.017f, position.y - 0.05f, 0.017f, 0.05f)) {
			offset.x = mouseGUIPos.x - position.x;
			m_isDragging = true;
		}
	}
	else {
		// Check if we've let go
		if (!MouseButtonInput::isMouseLeftDown()) {
			m_isDragging = false;
		}
		else {
			position.x = mouseGUIPos.x - offset.x;
			if (position.x < MIN)
				position.x = MIN;
			else if (position.x > MAX)
				position.x = MAX;

			m_value = (position.x - MIN) / m_length;
		}
	}
}
