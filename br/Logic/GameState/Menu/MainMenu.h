#pragma once

#include "../State.h"

class StateMachine;

class MainMenu : public State {
public:
	MainMenu(StateMachine& machine, bool replace = true);

	void pause();
	void resume();
	void update();
	void render();

private:

};

