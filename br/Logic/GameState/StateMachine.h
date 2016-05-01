#pragma once

#include "State.h"

#include <memory>
#include <stack>

class StateMachine {
public:
	StateMachine();

	void run(std::unique_ptr<State> state);

	void nextState();
	void lastState();
	void update();
	void render();

	bool runnning() { return m_running; }
	void quit() { m_running = false; }

	template <typename T>
	static std::unique_ptr<T> build(StateMachine& machine, bool replace = true);

private:
	std::stack<std::unique_ptr<State>> m_states;

	bool m_resume;
	bool m_running;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, bool replace) {
	return std::unique_ptr<T>(new T(machine, replace));
}

