#pragma once

#include <memory>

class StateMachine;

class State {
public:
	State(StateMachine& machine, bool replace = true);
	virtual ~State() = default;

	State(const State&) = delete;
	State& operator=(const State&) = delete;

	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	std::unique_ptr<State> next();

	bool isReplacing();

protected:
	StateMachine& m_machine;
	bool m_replacing;
	std::unique_ptr<State> m_next;
};