#include "MainMenu.h"
#include "../StateMachine.h"

#include <iostream>

MainMenu::MainMenu(StateMachine& machine, bool replace) 
	: State{machine, replace} {

	std::cout << "Main Menu Init.." << std::endl;
}

void MainMenu::pause() {
	std::cout << "Main Menu Pause" << std::endl;
}

void MainMenu::resume() {
	std::cout << "Main Menu Resume" << std::endl;
}

void MainMenu::update() {

}

void MainMenu::render() {

}