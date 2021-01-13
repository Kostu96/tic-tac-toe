#include "button.h"

#include "../asset_manager.h"
#include "../utility.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>

namespace GUI
{
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_rect, states);
		target.draw(m_text, states);
	}

	Button::Button(const FontManager& fonts, sf::Vector2f size) :
		m_callback(),
		m_rect(size),
		m_text("", fonts.get(FontID::Main), 44)
	{
		m_rect.setFillColor(sf::Color(NORMAL_COLOR));

		sf::FloatRect bounds = m_rect.getLocalBounds();
		m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}
	
	void Button::setText(const std::string& text)
	{
		m_text.setString(text);
		centerOrigin(m_text);
	}
	
	void Button::select()
	{
		Component::select();
		m_rect.setFillColor(sf::Color(SELECTED_COLOR));
	}
	
	void Button::deselect()
	{
		Component::deselect();
		m_rect.setFillColor(sf::Color(NORMAL_COLOR));
	}
	
	void Button::activate()
	{
		Component::activate();

		if (m_callback)
			m_callback();
	}

	void Button::handleRealTimeInput(sf::Vector2i mousePos)
	{
		sf::Vector2f pos = getPosition();
		sf::FloatRect size = m_rect.getLocalBounds();
		sf::FloatRect bounding(pos.x, pos.y, size.width, size.height);

		if (bounding.contains(mousePos.x, mousePos.y))
			select();
		else
			deselect();
	}
}
