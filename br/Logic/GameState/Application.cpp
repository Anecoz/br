#include "Application.h"

Application::Application() {
	//Init stuff
}

void Application::run() {
	// create gl window stuff

	m_machine.run(StateMachine::build<MainMenu>(m_machine, false));

	while (m_machine.runnning()) {
		m_machine.nextState();
		m_machine.update();
		m_machine.render();
	}

	// cleanup stuff
}