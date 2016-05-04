#include "Slider.h"
#include "../../Utils/ResourceHandler.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Utils/MathUtils.h"

Slider::Slider(glm::vec2 position, float length, float& value) : m_value {value},
	DrawableEntity(ResourceHandler::sliderTexture, position, -0.3f) {
	this->mesh = ResourceHandler::sliderQuad;
	m_length = length;
}

Slider::~Slider() {
}

void Slider::update() {
	glm::vec2 mouseRAWPos = MousePosInput::getPosition();
	glm::vec2 mouseGUIPos = MathUtils::screenSpaceToGUI(MousePosInput::getPosition());
	glm::vec2 offset;

	// Check the dragging status of the whole window
	if (!m_isDragging) {
		if (MouseButtonInput::isMouseLeftDown() &&
			MathUtils::isWithinGUIBox(mouseGUIPos, position.x, position.y, texture->getWidthAfterScale(), texture->getHeightAfterScale())) {
			offset = MathUtils::screenSpaceToGUI(mouseRAWPos) - position;
			m_isDragging = true;
		}
	}
	// Check if we've let go
	if (!MouseButtonInput::isMouseLeftDown()) {
		m_isDragging = false;
	}
	else {
		glm::vec2 GUIpos = MathUtils::screenSpaceToGUI(mouseRAWPos);
		position.x = GUIpos.x - offset.x;
	}
}
