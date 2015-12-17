#ifndef CHARACTER_H
#define CHARACTER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Character {
	public:
		explicit Character(int x, int y);
		virtual ~Character();
		sf::Vector2f getPosition();
		void setPosition(int x, int y);
		
	private:
		sf::Vector2f m_charPos;
		
		virtual void draw(sf::RenderTarget& target) const
		{
			sf::RectangleShape character(sf::Vector2f(32, 32));

			character.setFillColor(sf::Color(255, 0, 0));

			character.setPosition(m_charPos.x, m_charPos.y);
		}
	};
}

#endif //CHARACTER_H
