#include "Application.h"

#include <SFML/Window/Event.hpp>

#include "states/state_ids.h"
#include "states/state.h"
#include "states/title_state.h"
#include "states/menu_state.h"
#include "states/game_state.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

void Application::processInput()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		m_stateStack.handleEvent(e);

		switch (e.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Application::update(sf::Time dt)
{
	m_stateStack.update(dt);
}

void Application::render()
{
	m_window.clear();
	m_stateStack.draw();
	m_window.display();
}

void Application::registerStates()
{
	m_stateStack.registerState<Title>(StateID::Title);
	m_stateStack.registerState<Menu>(StateID::Menu);
	m_stateStack.registerState<Game>(StateID::Game);
}

Application::Application() :
	m_window(sf::VideoMode(800, 600), "Tic Tac Toe | Kostu96", sf::Style::Close),
	m_stateStack(State::Context(m_window, m_textures, m_fonts))
{
	m_window.setKeyRepeatEnabled(false);
	m_window.setVerticalSyncEnabled(true);

	m_fonts.load(FontID::Console, "assets/consolab.ttf");
	m_fonts.load(FontID::Main, "assets/segoeui.ttf");

	registerStates();
	m_stateStack.pushState(StateID::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time dt;
	while (m_window.isOpen())
	{
		dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processInput();
			update(TIME_PER_FRAME);
			if (m_stateStack.isEmpty())
				m_window.close();
		}
		render();
	}
}
