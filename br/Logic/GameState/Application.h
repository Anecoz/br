#pragma once

#include "Menu\MainMenu.h"
#include "StateMachine.h"

class Application {
public:
	Application();

	void run();

private:
	StateMachine m_machine;
};

