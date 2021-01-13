#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Square :
	public sf::Drawable,
	public sf::Transformable,
	private sf::NonCopyable
{
public:
	enum class State
	{
		None,
		O,
		X
	};

	Square();
	void setFont(sf::Font& font) { m_symbol.setFont(font); }
	void setState(State state);
	State getState() const { return m_state; }
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

	sf::RectangleShape m_box;
	State m_state;
	sf::Text m_symbol;
};
