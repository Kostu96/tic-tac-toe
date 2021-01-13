#include "Square.h"

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_box, states);
	target.draw(m_symbol, states);
}

Square::Square() :
	m_box(sf::Vector2f(148.f, 148.f)),
	m_state(State::None),
	m_symbol()
{
	m_box.setPosition(1.f, 1.f);
	m_box.setFillColor(sf::Color::Black);
	m_box.setOutlineColor(sf::Color::White);
	m_box.setOutlineThickness(1.f);
	m_symbol.setString("");
	m_symbol.setCharacterSize(150);
	m_symbol.setPosition(30, -30);
}

void Square::setState(State state)
{
	m_state = state;
	update();
}

void Square::update()
{
	switch (m_state)
	{
	case State::None:
		m_symbol.setString("");
		break;
	case State::O:
		m_symbol.setString("O");
		break;
	case State::X:
		m_symbol.setString("X");
		break;
	}
}
