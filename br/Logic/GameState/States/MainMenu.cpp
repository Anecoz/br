#include "MainMenu.h"
#include "GameState.h"
#include "OptionMenu.h"
#include "../StateMachine.h"

#include <iostream>

MainMenu::MainMenu(StateMachine& machine, GLFWwindow& window,bool replace) 
	: State{machine, window, replace} {
	Text* Titel = new Text("MAIN MENU", 0.4f, 0.1f, 40);

	Button* playButton = new Button("PLAY", 30, glm::vec2(0.45f, 0.3f));
	Button* optionButton = new Button("OPTIONS", 30, glm::vec2(0.45f, 0.35f));
	Button* exitButton = new Button("EXIT", 30, glm::vec2(0.45f, 0.45f));

	playButton->setCallback([this] {
		m_next = StateMachine::build<GameState>(m_machine, m_window, true);
	});
	optionButton->setCallback([this] {
		m_next = StateMachine::build<OptionMenu>(m_machine, m_window , false);
		b_cleanMe = true;
	});
	exitButton->setCallback([this] {
		m_machine.quit();
	});

	m_buttons.push_back(playButton);
	m_buttons.push_back(optionButton);
	m_buttons.push_back(exitButton);

	m_texts.push_back(Titel);

	std::cout << "Main Menu Init" << std::endl;
}

void MainMenu::pause() {
	std::cout << "Main Menu Pause" << std::endl;
	
	for (Button* b : m_buttons) {
		b->setVisibility(false);
	}
	for (Text* t : m_texts) {
		t->setVisibility(false);
	}
}

void MainMenu::resume() {
	std::cout << "Main Menu Resume" << std::endl;

	for (Button* b : m_buttons) {
		b->setVisibility(true);
	}
	for (Text* t : m_texts) {
		t->setVisibility(true);
	}
}

void MainMenu::update() {
	for (Button* b : m_buttons) {
		b->update();
	}

	if (b_cleanMe) {
		cleanUp();
		b_cleanMe = false;
	}
}

void MainMenu::render() {

}

void MainMenu::cleanUp() {
	for (Button* b : m_buttons) {
		b->remove();
		delete b;
	}
	for (Text* t : m_texts) {
		delete t;
		t = nullptr;
	}

	m_buttons.clear();
	m_texts.clear();
}