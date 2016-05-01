#include "OptionMenu.h"
#include "../StateMachine.h"

#include <iostream>

OptionMenu::OptionMenu(StateMachine& machine, bool replace) 
	: State{ machine, replace } {
	std::cout << "Options Menu Init.." << std::endl;

	Text* Titel = new Text("OPTIONS MENU", 0.4f, 0.1f, 40);

	Button* applyButton = new Button("OPTIONS", 30, glm::vec2(0.45f, 0.35f));
	Button* backButton = new Button("EXIT", 30, glm::vec2(0.45f, 0.45f));

	applyButton->setCallback([this] {
		std::cout << "APPLYING" << std::endl;
		// Set config file
	});
	backButton->setCallback([this] {
		cleanUp();
		m_machine.lastState();
	});

	buttons.push_back(applyButton);
	buttons.push_back(backButton);

	texts.push_back(Titel);
}

void OptionMenu::pause() {
	std::cout << "Options Menu Pause" << std::endl;
}

void OptionMenu::resume() {
	std::cout << "Options Menu Resume" << std::endl;
}

void OptionMenu::update() {

	for (Button* b : buttons) {
		b->update();
	}
}

void OptionMenu::render() {

}

void OptionMenu::cleanUp() {
	for (Button* b : buttons) {
		b->remove();
	}
	for (Text* t : texts) {
		delete t;
		t = nullptr;
	}
}