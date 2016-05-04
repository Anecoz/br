#include "CheckBox.h"
#include "../../Utils/ResourceHandler.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Utils/MathUtils.h"

CheckBox::CheckBox(glm::vec2 position, int& value) : b_isChecked(value),
	GUIElement(value ? ResourceHandler::checkboxONTexture : ResourceHandler::checkboxOFFTexture,
		ResourceHandler::checkBoxQuad, position) {
}

CheckBox::~CheckBox() {
}

void CheckBox::update() {
	glm::vec2 mouseGUIPos = MathUtils::screenSpaceToGUI(MousePosInput::getPosition());

	if (MouseButtonInput::isMouseButtonClicked(GLFW_MOUSE_BUTTON_1) &&
		MathUtils::isWithinGUIBox(mouseGUIPos, position.x, position.y - 0.05f, 0.05f, 0.05f)) {
		if (b_isChecked) {
			this->texture = ResourceHandler::checkboxOFFTexture;
			b_isChecked = 0;
		}
		else {
			this->texture = ResourceHandler::checkboxONTexture;
			b_isChecked = 1;
		}
	}
}