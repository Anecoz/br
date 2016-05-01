#include "StateMachine.h"

#include <iostream>
#include <memory>

StateMachine::StateMachine() 
	: m_resume{ false }, m_running{ false } {
	std::cout << "Statemachine Init.." << std::endl;
}

void StateMachine::run(std::unique_ptr<State> state) {
	m_running = true;
	m_states.push(std::move(state));
}

void StateMachine::nextState() {
	if (m_resume) {
		// Cleanup the current state
		if (!m_states.empty())
			m_states.pop();
		// Resume previous state
		if (!m_states.empty())
			m_states.top()->resume();
		m_resume = false;
	}

	// If there is no state add one
	if (!m_states.empty()) {
		std::unique_ptr<State> temp = m_states.top()->next();
		if (temp != nullptr) {
			// Replace the current state
			if (temp->isReplacing())
				m_states.pop();
			else
				m_states.top()->pause();

			m_states.push(std::move(temp));
		}
	}
}

void StateMachine::lastState() {
	m_resume = true;
}

void StateMachine::update() {
	m_states.top()->update();
}

void StateMachine::render() {
	m_states.top()->render();
}