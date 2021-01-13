#include "title_state.h"

#include "../asset_manager.h"
#include "../utility.h"

#include <SFML/Graphics/RenderWindow.hpp>

Title::Title(StateStack & stack, Context context) :
	State(stack, context),
	m_text1("Kostu96", context.m_fonts->get(FontID::Main), 72),
	m_time(sf::Time::Zero)
{
	centerOrigin(m_text1);
	m_text1.setPosition(context.m_window->getView().getSize() / 2.f);
	m_text1.setFillColor(sf::Color(255, 255, 255, 0));

	context.m_textures->load(TextureID::SFMLLogo, "assets/sfml-logo.png");
	m_sfml.setTexture(context.m_textures->get(TextureID::SFMLLogo));
	centerOrigin(m_sfml);
	m_sfml.setPosition(context.m_window->getView().getSize() / 2.f);
	m_sfml.setScale(.5f, .5f);
}

void Title::draw()
{
	sf::RenderWindow & window = *getContext().m_window;
	if (draw1)
		window.draw(m_text1);
	if (draw2)
		window.draw(m_sfml);
}

bool Title::update(sf::Time dt)
{
	m_time += dt;
	
	// Ugly code for animation - at least extract magics to constants.
	if (m_time > sf::seconds(0.5f) && m_time <= sf::seconds(1.5f))
	{
		draw1 = true;
		draw2 = false;
		float percent = (m_time.asSeconds() - 0.5f) / 1.f;
		sf::Color color(255, 255, 255, sf::Uint8(percent * 255));
		m_text1.setFillColor(color);
	}
	else if (m_time > sf::seconds(2.f) && m_time <= sf::seconds(3.f))
	{
		draw1 = true;
		draw2 = false;
		float percent = 1 - (m_time.asSeconds() - 2.f) / 1.f;
		sf::Color color(255, 255, 255, sf::Uint8(percent * 255));
		m_text1.setFillColor(color);
	}
	else if (m_time > sf::seconds(3.5f) && m_time <= sf::seconds(4.5f))
	{
		draw1 = false;
		draw2 = true;
		float percent = (m_time.asSeconds() - 3.5f) / 1.f;
		sf::Color color(255, 255, 255, sf::Uint8(percent * 255));
		m_sfml.setColor(color);
	}
	else if (m_time > sf::seconds(5.f) && m_time <= sf::seconds(6.f))
	{
		draw1 = false;
		draw2 = true;
		float percent = 1 - (m_time.asSeconds() - 4.f) / 1.f;
		sf::Color color(255, 255, 255, sf::Uint8(percent * 255));
		m_sfml.setColor(color);
	}
	else if (m_time > sf::seconds(6.5f))
	{
		requestStackPop();
		requestStackPush(StateID::Menu);
	}
	return true;
}

bool Title::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
		if (draw2)
		{
			requestStackPop();
			requestStackPush(StateID::Menu);
		}
		else if (draw1)
			m_time = sf::seconds(3.5);

	return true;
}
