#include "MouseButtonInput.h"

bool MouseButtonInput::LEFT_DOWN = false;
bool MouseButtonInput::RIGHT_DOWN = false;
vector<int> MouseButtonInput::pressed;
bool MouseButtonInput::buttons[128];

void MouseButtonInput::invoke(GLFWwindow* window, int button, int action, int mods) {
	buttons[button] = action != GLFW_RELEASE;

	if (action == GLFW_RELEASE && find(pressed.begin(), pressed.end(), button) != pressed.end())
		pressed.erase(remove(pressed.begin(), pressed.end(), button), pressed.end());

	if (button == GLFW_MOUSE_BUTTON_1) {
		if (action == GLFW_PRESS)
			LEFT_DOWN = true;
		else if (action == GLFW_RELEASE)
			LEFT_DOWN = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_2) {
		if (action == GLFW_PRESS)
			RIGHT_DOWN = true;
		else if (action == GLFW_RELEASE)
			RIGHT_DOWN = false;
	}
}