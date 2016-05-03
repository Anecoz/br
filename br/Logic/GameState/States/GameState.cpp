#include "GameState.h"
#include "../StateMachine.h"
#include "../../../Audio/AudioMaster.h"
#include "../../../Graphics/Shaders/ShaderHandler.h"
#include "../../../Graphics/Shadows/ShadowHandler.h"
#include "../../../Graphics/Lighting/LightHandler.h"

#include <iostream>

GameState::GameState(StateMachine& machine, GLFWwindow& window, bool replace)
	: State{ machine, window, replace } {
	m_level = new Level("Resource/maps/map_01.tmx");
	m_camera = new Camera(1280, 720);
	m_player = new Player();

	ShadowHandler::calcShadowCaster(m_level);

	AudioMaster::setListenerData(vec2(0), vec2(0));

	std::cout << "Game State Init" << std::endl;
}

void GameState::pause() {
	std::cout << "Game State Pause" << std::endl;
}

void GameState::resume() {
	std::cout << "Game State Resume" << std::endl;
}

void GameState::update() {
	for (Button* b : m_buttons) {
		b->update();
	}

	if (b_cleanMe) {
		cleanUp();
		b_cleanMe = false;
	}
	m_camera->update(m_player->getPosition(), m_player->getSpeed(), m_level);
	m_player->update(m_level, m_camera->getProjection());
}

void GameState::render() {
	ShadowHandler::calcShadowMap(LightHandler::lightList, m_camera->getProjection(), m_level, m_player);

	m_level->render(m_camera->getProjection());
	m_player->render(m_camera->getProjection());
}

void GameState::cleanUp() {
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

	delete m_level;
	m_level = nullptr;
	delete m_camera;
	m_camera = nullptr;
}