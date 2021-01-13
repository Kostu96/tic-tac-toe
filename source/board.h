#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Square.h"
#include <array>

enum class Turn {
	O,
	X,
};

class Board :
	public sf::Drawable,
	public sf::Transformable,
	private sf::NonCopyable
{
public:
	Board(sf::Font& font, Turn& turn);
	void handleClick(int x, int y);
	sf::Vector2f getSize() const { return sf::Vector2f(3 * 150, 3 * 150); }
	std::string check() const;
	bool contains(int x, int y);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::array<std::array<Square, 3>, 3> m_squares;
	Turn& m_turn;
};
