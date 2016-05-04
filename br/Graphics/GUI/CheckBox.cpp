#include "CheckBox.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Utils/MathUtils.h"

CheckBox::CheckBox(glm::vec2 position, bool& value) : m_isChecked{ value } {
	m_position = position;
}

CheckBox::~CheckBox() {
}

void CheckBox::update() {
	glm::vec2 mouseRAWPos = MousePosInput::getPosition();
	glm::vec2 mouseGUIPos = MathUtils::screenSpaceToGUI(MousePosInput::getPosition());

	/*if (MouseButtonInput::isMouseLeftDown() &&
		MathUtils::isWithinGUIBox(mouseGUIPos, m_position.x, m_position.y, texture->getWidthAfterScale(), texture->getHeightAfterScale())) {
		m_isChecked != m_isChecked;
	}*/
}