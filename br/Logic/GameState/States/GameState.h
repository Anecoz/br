#pragma once

#include <vector>

#include "../State.h"
#include "../../../Graphics/GUI/Button.h"
#include "../../../Font/Text.h"
#include "../../../Graphics/Camera.h"

class StateMachine;

class GameState : public State {
public:
	GameState(StateMachine& machine, GLFWwindow& window, bool replace = true);

	void pause();
	void resume();
	void update();
	void render();

private:
	vector<Button*> m_buttons;
	vector<Text*> m_texts;
	void cleanUp();

	bool b_cleanMe;

	Level* m_level;
	Camera* m_camera;
};
