#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <algorithm>

using namespace std;

class KeyInput {

public:
	~KeyInput();

	static void invoke(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool isKeyDown(int key) {
		return keys[key];
	}

	static bool isKeyClicked(int key) {
		if (!keys[key])
			return false;
		if (find(pressed->begin(), pressed->end(), key) != pressed->end())
			return false;
		pressed->push_back(key);
		return true;
	}

private:
	static bool keys[512];
	static vector<int>* pressed;
};

