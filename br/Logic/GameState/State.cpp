#include "State.h"

State::State(StateMachine& machine, bool replace) 
	: m_machine{ machine }, m_replacing{ replace } {

}

std::unique_ptr<State> State::next() {
	return std::move(m_next);
}

bool State::isReplacing() {
	return m_replacing;
}