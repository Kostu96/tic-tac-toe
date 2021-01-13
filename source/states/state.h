#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

#include "state_ids.h"
#include "../asset_ids.h"

class StateStack;

namespace sf
{
	class RenderWindow;
}

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts);

		sf::RenderWindow* m_window;
		TextureManager* m_textures;
		FontManager* m_fonts;
	};

	State(StateStack& stack, Context context);
	virtual ~State() {}
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
protected:
	void requestStackPush(StateID stateID);
	void requestStackPop();
	void requestStateClear();
	Context getContext() const { return m_context; }
private:
	StateStack* m_stack;
	Context m_context;
};
