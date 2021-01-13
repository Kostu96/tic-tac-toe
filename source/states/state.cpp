#include "state.h"

#include "state_stack.h"

void State::requestStackPush(StateID stateID)
{
	m_stack->pushState(stateID);
}

void State::requestStackPop()
{
	m_stack->popState();
}

void State::requestStateClear()
{
	m_stack->clearStates();
}

State::State(StateStack & stack, Context context) :
	m_stack(&stack),
	m_context(context)
{
}

State::Context::Context(sf::RenderWindow & window, TextureManager & textures, FontManager & fonts) :
	m_window(&window),
	m_textures(&textures),
	m_fonts(&fonts)
{
}
