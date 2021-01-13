#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "asset_manager.h"
#include "asset_ids.h"
#include "states/state_stack.h"

class Application :
	private sf::NonCopyable
{
private:
	static const sf::Time TIME_PER_FRAME;

	sf::RenderWindow m_window;
	TextureManager m_textures;
	FontManager m_fonts;
	StateStack m_stateStack;

	void processInput();
	void update(sf::Time dt);
	void render();
	void registerStates();
public:
	Application();
	void run();
};
