#pragma once

#include <vector>

#include "../State.h"
#include "../../../Graphics/GUI/Button.h"
#include "../../../Graphics/GUI/Slider.h"
#include "../../../Graphics/GUI/CheckBox.h"
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
	Slider* slider;
	Text* volumeValue;
	CheckBox* checkbox;

	void cleanUp();
	bool b_cleanMe;
};
