#pragma once
#include "state.h"
#include "state_ids.h"

#include <SFML/System/NonCopyable.hpp>

#include <functional>
#include <vector>
#include <map>

class StateStack :
	private sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);
	template <typename T>
	void registerState(StateID stateID);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushState(StateID stateID);
	void popState();
	void clearStates();
	bool isEmpty() const { return m_stack.empty(); }
private:
	struct PendingChange
	{
		PendingChange(Action action, StateID stateID = StateID::None);

		Action m_action;
		StateID m_stateID;
	};

	State::Ptr createState(StateID stateID);
	void applyPendingChanges();

	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<StateID, std::function<State::Ptr()>> m_factories;
};

template <typename T>
void StateStack::registerState(StateID stateID)
{
	m_factories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, m_context));
	};
}
