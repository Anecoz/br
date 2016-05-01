#include "MousePosInput.h"

double MousePosInput::x;
double MousePosInput::y;

void MousePosInput::invoke(GLFWwindow* window, double xPos, double yPos) {
	x = xPos;
	y = yPos;
}