#pragma once

#include "States\MainMenu.h"
#include "StateMachine.h"

class Application {
public:
	Application();

	void run();

private:
	void InitWindowHandle();
	void InitResources();

	StateMachine m_machine;

	GLFWwindow* m_window;
};

