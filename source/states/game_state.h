#pragma once
#include "State.h"
#include "../Board.h"
#include "../GUI/Container.h"

class Game :
	public State
{

public:
	Game(StateStack& stack, Context context);
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
private:
	enum class GameState
	{
		Running,
		XWin,
		OWin,
		Draw
	};

	GameState m_gameState;
	Turn m_turn;
	Board m_board;
	sf::Text m_text;
	GUI::Container m_GUIContainer;
	sf::RenderWindow& m_window;
};
