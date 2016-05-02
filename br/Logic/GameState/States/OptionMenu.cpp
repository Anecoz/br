#include "OptionMenu.h"
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
		cleanUp();
		m_machine.lastState();
	});

	m_buttons.push_back(applyButton);
	m_buttons.push_back(backButton);

	m_texts.push_back(Titel);

	std::cout << "Options Menu Init" << std::endl;
}

void OptionMenu::pause() {
	std::cout << "Options Menu Pause" << std::endl;
}

void OptionMenu::resume() {
	std::cout << "Options Menu Resume" << std::endl;
}

void OptionMenu::update() {

	for (Button* b : m_buttons) {
		b->update();
	}
}

void OptionMenu::render() {

}

void OptionMenu::cleanUp() {
	for (Button* b : m_buttons) {
		b->remove();
	}
	for (Text* t : m_texts) {
		delete t;
		t = nullptr;
	}
}