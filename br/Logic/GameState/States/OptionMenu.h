#pragma once

#include <vector>

#include "../State.h"
#include "../../../Graphics/GUI/Button.h"
#include "../../../Font/Text.h"

class StateMachine;

class OptionMenu : public State {
public:
	OptionMenu(StateMachine& machine, GLFWwindow& window, bool replace = true);

	void pause();
	void resume();
	void update();
	void render();

private:
	vector<Button*> m_buttons;
	vector<Text*> m_texts;
	void cleanUp();
};
