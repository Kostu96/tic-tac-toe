#include "Board.h"

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			target.draw(m_squares[i][j], states);
}

Board::Board(sf::Font& font, Turn& turn) :
	m_turn(turn)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			m_squares[i][j].setPosition(j * 150.f, i * 150.f);
			m_squares[i][j].setFont(font);
		}
}

void Board::handleClick(int x, int y)
{
	x -= (int)getPosition().x;
	y -= (int)getPosition().y;

	int i = x / 150;
	int j = y / 150;

	if (m_squares[j][i].getState() == Square::State::None)
		if (m_turn == Turn::X)
		{
			m_turn = Turn::O;
			m_squares[j][i].setState(Square::State::X);
		}
		else if (m_turn == Turn::O)
		{
			m_turn = Turn::X;
			m_squares[j][i].setState(Square::State::O);
		}
}

std::string Board::check() const
{
	int count = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (m_squares[i][j].getState() != Square::State::None) ++count;

	Square::State winner = Square::State::None;
	// very very very bad code - not scalable. Do not copy under any circumstances
	if (m_squares[0][0].getState() == m_squares[0][1].getState() && m_squares[0][1].getState() == m_squares[0][2].getState())
		winner = m_squares[0][0].getState();
	else if (m_squares[1][0].getState() == m_squares[1][1].getState() && m_squares[1][1].getState() == m_squares[1][2].getState())
		winner = m_squares[1][0].getState();
	else if (m_squares[2][0].getState() == m_squares[2][1].getState() && m_squares[2][1].getState() == m_squares[2][2].getState())
		winner = m_squares[2][0].getState();
	else if (m_squares[0][0].getState() == m_squares[1][0].getState() && m_squares[1][0].getState() == m_squares[2][0].getState())
		winner = m_squares[0][0].getState();
	else if (m_squares[0][1].getState() == m_squares[1][1].getState() && m_squares[1][1].getState() == m_squares[2][1].getState())
		winner = m_squares[0][1].getState();
	else if (m_squares[0][2].getState() == m_squares[1][2].getState() && m_squares[1][2].getState() == m_squares[2][2].getState())
		winner = m_squares[0][2].getState();
	else if (m_squares[0][0].getState() == m_squares[1][1].getState() && m_squares[1][1].getState() == m_squares[2][2].getState())
		winner = m_squares[0][0].getState();
	else if (m_squares[0][2].getState() == m_squares[1][1].getState() && m_squares[1][1].getState() == m_squares[2][0].getState())
		winner = m_squares[0][2].getState();

	if (winner == Square::State::O) return "O";
	else if (winner == Square::State::X) return "X";

	if (count == 9)
		return "Draw";

	return "None";
}

bool Board::contains(int x, int y)
{
	return x > getPosition().x && x < getPosition().x + getSize().x &&
		   y > getPosition().y && y < getPosition().y + getSize().y;
}
