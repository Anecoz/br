#include "MainMenu.h"
#include "GameState.h"
#include "OptionMenu.h"
#include "../StateMachine.h"

#include <iostream>

MainMenu::MainMenu(StateMachine& machine, bool replace) 
	: State{machine, replace} {
	std::cout << "Main Menu Init.." << std::endl;

	Text* Titel = new Text("Main Menu", 0.4f, 0.1f, 40);

	Button* playButton = new Button("PLAY", 30, glm::vec2(0.45f, 0.3f));
	Button* optionButton = new Button("OPTIONS", 30, glm::vec2(0.45f, 0.35f));
	Button* exitButton = new Button("EXIT", 30, glm::vec2(0.45f, 0.45f));

	playButton->setCallback([this] {
		std::cout << "PLAYING" << std::endl;
		m_next = StateMachine::build<GameState>(m_machine, true);
	});
	optionButton->setCallback([this] {
		std::cout << "OPTION MENU" << std::endl;
		m_next = StateMachine::build<OptionMenu>(m_machine, false);
	});
	exitButton->setCallback([this] {
		cleanUp();
		m_machine.quit();
	});

	buttons.push_back(playButton);
	buttons.push_back(optionButton);
	buttons.push_back(exitButton);

	texts.push_back(Titel);
}

void MainMenu::pause() {
	std::cout << "Main Menu Pause" << std::endl;
}

void MainMenu::resume() {
	std::cout << "Main Menu Resume" << std::endl;
}

void MainMenu::update() {

	for (Button* b : buttons) {
		b->update();
	}
}

void MainMenu::render() {

}

void MainMenu::cleanUp() {
	for (Button* b : buttons) {
		b->remove();
	}
	for (Text* t : texts) {
		delete t;
		t = nullptr;
	}
}