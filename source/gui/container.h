#pragma once
#include "component.h"

#include <vector>

namespace GUI
{
	class Container :
		public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr;

		Container();
		void pack(Component::Ptr component);
		bool isSelectable() const override { return false; }
		void handleEvent(const sf::Event & event) override;
		void handleRealTimeInput(sf::Vector2i mousePos) override;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool hasSelection() const { return m_selectedChild >= 0; }
		void select(std::size_t index);
		void selectNext();
		void selectPrevious();

		std::vector<Component::Ptr> m_children;
		int m_selectedChild;
		bool m_isMouseInput;
	};
}
