#include "game_state.h"

#include "../asset_manager.h"
#include "../gui/button.h"

#include "SFML/Graphics/RenderWindow.hpp"

bool Game::update(sf::Time dt)
{
	if (m_gameState == GameState::Running)
	{
		if (m_turn == Turn::X)
			m_text.setString("Next turn: X");
		else if (m_turn == Turn::O)
			m_text.setString("Next turn: O");

		std::string winner = m_board.check();
		if (winner == "X")
		{
			m_text.setString("Winner: X!");
			m_gameState = GameState::XWin;
		}
		else if (winner == "O")
		{
			m_text.setString("Winner: O!");
			m_gameState = GameState::OWin;
		}
		else if (winner == "Draw")
		{
			m_text.setString("Draw!");
			m_gameState = GameState::Draw;
		}
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	m_GUIContainer.handleRealTimeInput(mousePos);

	return true;
}

void Game::draw()
{
	sf::RenderWindow & window = *getContext().m_window;
	window.draw(m_text);
	window.draw(m_board);
	window.draw(m_GUIContainer);
}

bool Game::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left &&
		m_gameState == GameState::Running &&
		m_board.contains(event.mouseButton.x, event.mouseButton.y))
	{
		m_board.handleClick(event.mouseButton.x, event.mouseButton.y);
	}

	m_GUIContainer.handleEvent(event);

	return true;
}

Game::Game(StateStack & stack, Context context) :
	State(stack, context),
	m_gameState(GameState::Running),
	m_turn(Turn::O),
	m_board(context.m_fonts->get(FontID::Console), m_turn),
	m_text("Next turn: O", context.m_fonts->get(FontID::Main), 44),
	m_window(*context.m_window)
{
	m_board.setPosition(30.f, 80.f);
	m_text.setPosition(30.f, 20.f);

	auto restartButton = std::make_shared<GUI::Button>(*context.m_fonts, sf::Vector2f(250, 64));
	restartButton->setPosition(525, 150);
	restartButton->setText("Restart");
	restartButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StateID::Game);
	});

	auto menuButton = std::make_shared<GUI::Button>(*context.m_fonts, sf::Vector2f(250, 64));
	menuButton->setPosition(525, 220);
	menuButton->setText("Main Menu");
	menuButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StateID::Menu);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.m_fonts, sf::Vector2f(250, 64));
	exitButton->setPosition(525, 290);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});

	m_GUIContainer.pack(restartButton);
	m_GUIContainer.pack(menuButton);
	m_GUIContainer.pack(exitButton);
}
