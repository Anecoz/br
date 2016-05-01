#include "KeyInput.h"

bool KeyInput::keys[512];
vector<int>* KeyInput::pressed = new vector<int>;

KeyInput::~KeyInput() {
	delete pressed;
	pressed = nullptr;
}

void KeyInput::invoke(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keys[key] = action != GLFW_RELEASE;
	if (action == GLFW_RELEASE && find(pressed->begin(), pressed->end(), key) != pressed->end()) {
		pressed->erase(remove(pressed->begin(), pressed->end(), key), pressed->end());
	}
}