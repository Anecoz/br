#include "GameState.h"
#include "../StateMachine.h"

#include <iostream>

GameState::GameState(StateMachine& machine, bool replace)
	: State{ machine, replace } {
	std::cout << "Game State Init.." << std::endl;

}

void GameState::pause() {
	std::cout << "Game State Pause" << std::endl;
}

void GameState::resume() {
	std::cout << "Game State Resume" << std::endl;
}

void GameState::update() {

	for (Button* b : buttons) {
		b->update();
	}
}

void GameState::render() {

}

void GameState::cleanUp() {
	for (Button* b : buttons) {
		b->remove();
	}
	for (Text* t : texts) {
		delete t;
		t = nullptr;
	}
}