#pragma once
#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Title :
	public State
{
public:
	Title(StateStack& stack, Context context);
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
private:
	sf::Text m_text1;
	sf::Sprite m_sfml;
	sf::Time m_time;
	bool draw1 = false;
	bool draw2 = false;
};
