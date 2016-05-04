#include "OptionMenu.h"
#include "MainMenu.h"
#include "../StateMachine.h"
#include "../../../Utils/ConfigUtils.h"
#include "../../../Graphics/Camera.h"

#include <iostream>

OptionMenu::OptionMenu(StateMachine& machine, GLFWwindow& window, bool replace)
	: State{ machine, window, replace } {

	Text* Titel = new Text("OPTIONS MENU", 0.4f, 0.1f, 40);

	Text* vsyncLabel = new Text("VSYNC", 0.3f, 0.25f, 20);
	Text* resolutionLabel = new Text("RESOLUTION", 0.3f, 0.3f, 20);
	Text* volumeLabel = new Text("VOLUME", 0.3f, 0.35f, 20);
	slider = new Slider(glm::vec2(0.5f, 0.5f), 0.1f, ConfigUtils::VOLUME);

	Button* applyButton = new Button("APPLY", 30, glm::vec2(0.83f, 0.95f));
	Button* backButton = new Button("BACK", 30, glm::vec2(0.1f, 0.95f));

	applyButton->setCallback([this] {
		std::cout << "APPLYING TO CONFIG" << std::endl;
		// Set config file
		ConfigUtils::setAllValues();
		ConfigUtils::saveConfig();
		// TODO: Create new window with new parameters from the config file
	});
	backButton->setCallback([this] {
		m_next = StateMachine::build<MainMenu>(m_machine, m_window, false);
		b_cleanMe = true;
	});

	m_buttons.push_back(applyButton);
	m_buttons.push_back(backButton);

	m_texts.push_back(Titel);
	m_texts.push_back(vsyncLabel);
	m_texts.push_back(resolutionLabel);
	m_texts.push_back(volumeLabel);

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

	//slider->update();

	if (b_cleanMe) {
		cleanUp();
		b_cleanMe = false;
	}
}

void OptionMenu::render() {
	/*if(slider != nullptr)
		slider->render();*/
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

	delete slider;
	slider = nullptr;

	m_buttons.clear();
	m_texts.clear();
}