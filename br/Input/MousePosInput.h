#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

using namespace glm;

class MousePosInput {

public:
	static vec2 getPosition() { return vec2(x, y); }

	static void invoke(GLFWwindow* window, double xPos, double yPos);

private:
	static double x;
	static double y;
};