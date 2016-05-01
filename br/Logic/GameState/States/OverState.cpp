#include "OverState.h"
#include "../StateMachine.h"

#include <iostream>

OverState::OverState(StateMachine& machine, bool replace)
	: State{ machine, replace } {
	std::cout << "Over State Init.." << std::endl;

	Text* Titel = new Text("GAME OVER", 0.4f, 0.1f, 40);
	
	texts.push_back(Titel);
}

void OverState::pause() {
	std::cout << "Over State Pause" << std::endl;
}

void OverState::resume() {
	std::cout << "Over State Resume" << std::endl;
}

void OverState::update() {

	for (Button* b : buttons) {
		b->update();
	}
}

void OverState::render() {

}

void OverState::cleanUp() {
	for (Button* b : buttons) {
		b->remove();
	}
	for (Text* t : texts) {
		delete t;
		t = nullptr;
	}
}