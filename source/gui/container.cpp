#include "container.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (const Component::Ptr& child : m_children)
			target.draw(*child, states);
	}

	void Container::select(std::size_t index)
	{
		if (m_children[index]->isSelectable())
		{
			if (hasSelection())
				m_children[m_selectedChild]->deselect();

			m_children[index]->select();
			m_selectedChild = index;
		}
	}

	void Container::selectNext()
	{
		if (m_selectedChild == -1)
		{
			select(0);
			return;
		}

		if (!hasSelection())
			return;

		long next = m_selectedChild;
		do
			next = (next + 1l) % m_children.size();
		while (!m_children[next]->isSelectable());

		select(next);
	}

	void Container::selectPrevious()
	{
		if (m_selectedChild == -1)
		{
			select(0);
			return;
		}

		if (!hasSelection())
			return;

		int prev = m_selectedChild;
		do
			prev = (prev + m_children.size() - 1) % m_children.size();
		while (!m_children[prev]->isSelectable());

		select(prev);
	}

	Container::Container() :
		m_children(),
		m_selectedChild(-1),
		m_isMouseInput(false)
	{
	}
	
	void Container::pack(Component::Ptr component)
	{
		m_children.push_back(component);
	}
	
	void Container::handleEvent(const sf::Event& event)
	{
		if (hasSelection() && m_children[m_selectedChild]->isActive())
			m_children[m_selectedChild]->handleEvent(event);
		else if (event.type == sf::Event::KeyPressed)
		{
			m_isMouseInput = false;
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				selectPrevious();
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				selectNext();
			else if (event.key.code == sf::Keyboard::Return)
				if (hasSelection())
					m_children[m_selectedChild]->activate();
		}
		else if (event.type == sf::Event::MouseMoved)
			m_isMouseInput = true;
		else if (event.type == sf::Event::MouseButtonPressed)
			if (hasSelection())
				m_children[m_selectedChild]->activate();
	}
	
	void Container::handleRealTimeInput(sf::Vector2i mousePos)
	{
		if (m_isMouseInput)
		{
			if (m_selectedChild != -1)
			{
				m_children[m_selectedChild]->deselect();
				m_selectedChild = -1;
			}

			for (auto & child : m_children)
				child->handleRealTimeInput(mousePos);

			for (int i = 0; i < m_children.size() && m_selectedChild == -1; ++i)
				if (m_children[i]->isSelected())
					m_selectedChild = i;
		}
	}
}
