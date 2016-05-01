#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <algorithm>
#include <vector>

using namespace std;

class MouseButtonInput {

public:

	static void invoke(GLFWwindow* window, int button, int action, int mods);

	static bool isMouseLeftDown() { return LEFT_DOWN; }
	static bool isMouseRightDown() { return RIGHT_DOWN; }

	static bool isMouseButtonClicked(int button) {
		if (!buttons[button])
			return false;
		if (find(pressed.begin(), pressed.end(), button) != pressed.end())
			return false;
		pressed.push_back(button);
		return true;
	}
private:

	static bool LEFT_DOWN;
	static bool RIGHT_DOWN;
	static vector<int> pressed;
	static bool buttons[128];

};