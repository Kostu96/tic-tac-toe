#pragma once
#include "component.h"
#include "../asset_ids.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>

namespace GUI
{
	class Button :
		public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

		constexpr static unsigned int NORMAL_COLOR = 0x46dc64ff;
		constexpr static unsigned int SELECTED_COLOR = 0x1e6e32ff;
	
		Button(const FontManager& fonts, sf::Vector2f size);
		void setCallback(Callback&& callback) { m_callback = std::move(callback); }
		void setText(const std::string & text);
		bool isSelectable() const override { return true; }
		void select() override;
		void deselect() override;
		void activate() override;
		void handleEvent(const sf::Event& event) override {}
		void handleRealTimeInput(sf::Vector2i mousePos) override;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		Callback m_callback;
		sf::RectangleShape m_rect;
		sf::Text m_text;
	};
}
