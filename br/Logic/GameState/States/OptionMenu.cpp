#include "OptionMenu.h"
#include "MainMenu.h"
#include "../StateMachine.h"

#include <iostream>

OptionMenu::OptionMenu(StateMachine& machine, GLFWwindow& window, bool replace)
	: State{ machine, window, replace } {

	Text* Titel = new Text("OPTIONS MENU", 0.4f, 0.1f, 40);

	Button* applyButton = new Button("APPLY", 30, glm::vec2(0.45f, 0.35f));
	Button* backButton = new Button("BACK", 30, glm::vec2(0.45f, 0.45f));

	applyButton->setCallback([this] {
		std::cout << "APPLYING TO CONFIG" << std::endl;
		// Set config file
	});
	backButton->setCallback([this] {
		m_next = StateMachine::build<MainMenu>(m_machine, m_window, false);
		b_cleanMe = true;
	});

	m_buttons.push_back(applyButton);
	m_buttons.push_back(backButton);

	m_texts.push_back(Titel);

	std::cout << "Options Menu Init" << std::endl;
}

void OptionMenu::pause() {
	std::cout << "Options Menu Pause" << std::endl;

	for (Button* b : m_buttons) {
		b->setVisibility(false);
	}
	for (Text* t : m_texts) {
		t->setVisibility(false);
	}
}

void OptionMenu::resume() {
	std::cout << "Options Menu Resume" << std::endl;

	for (Button* b : m_buttons) {
		b->setVisibility(true);
	}
	for (Text* t : m_texts) {
		t->setVisibility(true);
	}
}

void OptionMenu::update() {

	for (Button* b : m_buttons) {
		b->update();
	}

	if (b_cleanMe) {
		cleanUp();
		b_cleanMe = false;
	}
}

void OptionMenu::render() {

}

void OptionMenu::cleanUp() {
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