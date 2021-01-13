#include "menu_state.h"

#include "../gui/button.h"

#include <SFML/Graphics/RenderWindow.hpp>

Menu::Menu(StateStack& stack, Context context) :
	State(stack, context),
	m_GUIContainer(),
	m_window(*context.m_window)
{
	auto playButton = std::make_shared<GUI::Button>(*context.m_fonts, sf::Vector2f(250, 64));
	playButton->setPosition(275, 250);
	playButton->setText("Play");
	playButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StateID::Game);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.m_fonts, sf::Vector2f(250, 64));
	exitButton->setPosition(275, 320);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});

	m_GUIContainer.pack(playButton);
	m_GUIContainer.pack(exitButton);
}

void Menu::draw()
{
	sf::RenderWindow & window = *getContext().m_window;
	window.draw(m_GUIContainer);
}

bool Menu::update(sf::Time dt)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	m_GUIContainer.handleRealTimeInput(mousePos);
	return true;
}

bool Menu::handleEvent(const sf::Event& event)
{
	m_GUIContainer.handleEvent(event);
	return true;
}
