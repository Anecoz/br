#include "OverState.h"
#include "../StateMachine.h"

#include <iostream>

OverState::OverState(StateMachine& machine, GLFWwindow& window, bool replace)
	: State{ machine, window, replace } {
	Text* Titel = new Text("GAME OVER", 0.4f, 0.1f, 40);
	
	m_texts.push_back(Titel);

	std::cout << "Over State Init" << std::endl;
}

void OverState::pause() {
	std::cout << "Over State Pause" << std::endl;
}

void OverState::resume() {
	std::cout << "Over State Resume" << std::endl;
}

void OverState::update() {

	for (Button* b : m_buttons) {
		b->update();
	}
}

void OverState::render() {

}

void OverState::cleanUp() {
	for (Button* b : m_buttons) {
		b->remove();
	}
	for (Text* t : m_texts) {
		delete t;
		t = nullptr;
	}
}