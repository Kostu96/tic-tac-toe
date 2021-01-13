#include "state_stack.h"

#include <cassert>

State::Ptr StateStack::createState(StateID stateID)
{
	auto found = m_factories.find(stateID);
	assert(found != m_factories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : m_pendingList)
	{
		switch (change.m_action)
		{
		case Action::Push:
			m_stack.push_back(createState(change.m_stateID));
			break;
		case Action::Pop:
			m_stack.pop_back();
			break;
		case Action::Clear:
			m_stack.clear();
			break;
		}
	}

	m_pendingList.clear();
}

StateStack::StateStack(State::Context context) :
	m_stack(),
	m_pendingList(),
	m_context(context),
	m_factories()
{
}

void StateStack::update(sf::Time dt)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		if (!(*it)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr & state : m_stack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		if (!(*it)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(StateID stateID)
{
	m_pendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	m_pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	m_pendingList.push_back(PendingChange(Action::Clear));
}

StateStack::PendingChange::PendingChange(Action action, StateID stateID) :
	m_action(action),
	m_stateID(stateID)
{
}
