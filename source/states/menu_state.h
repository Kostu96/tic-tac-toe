#pragma once
#include "State.h"
#include "../GUI/Container.h"

class Menu :
	public State
{
public:
	Menu(StateStack& stack, Context context);
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
private:
	GUI::Container m_GUIContainer;
	sf::RenderWindow& m_window;
};
