#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

namespace sf
{
	class Event;
}

namespace GUI
{
	class Component :
		public sf::Drawable,
		public sf::Transformable,
		private sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;
	
		Component() : m_isSelected(false), m_isActive(false) {}
		virtual ~Component() {}
		virtual bool isSelectable() const = 0;
		bool isSelected() const { return m_isSelected; }
		virtual void select() { m_isSelected = true; }
		virtual void deselect() { m_isSelected = false; }
		virtual bool isActive() const { return m_isActive; }
		virtual void activate() { m_isActive = true; }
		virtual void deactivate() { m_isActive = false; }
		virtual void handleEvent(const sf::Event & event) = 0;
		virtual void handleRealTimeInput(sf::Vector2i mousePos) = 0;
	private:
		bool m_isSelected;
		bool m_isActive;
	};
}
