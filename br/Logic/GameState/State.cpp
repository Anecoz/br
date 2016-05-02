#include "State.h"

State::State(StateMachine& machine, GLFWwindow& window, bool replace)
	: m_machine{ machine }, m_replacing{ replace }, m_window{ window } {

}

std::unique_ptr<State> State::next() {
	return std::move(m_next);
}

bool State::isReplacing() {
	return m_replacing;
}