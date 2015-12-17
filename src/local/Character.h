#ifndef CHARACTER_H
#define CHARACTER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Character : public sf::Drawable, public sf::Transformable
	{
	public:

		explicit Character(int x, int y);
		virtual ~Character();
		sf::Vector2f getPosition();
		void setPosition(int x, int y);
		void move(int dir);
		
	private:
		sf::Vector2f m_charPos;
		const static int m_speed = 4; //in pixel
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			sf::RectangleShape character(sf::Vector2f(32, 32));

			character.setFillColor(sf::Color(255, 0, 0));

			character.setPosition(m_charPos.x, m_charPos.y);

			target.draw(character, states);
		}
	};
}

#endif //CHARACTER_H
