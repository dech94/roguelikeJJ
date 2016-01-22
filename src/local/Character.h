#ifndef CHARACTER_H
#define CHARACTER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Character //: public sf::Drawable, public sf::Transformable
	{
	public:

		explicit Character(int x, int y);
		virtual ~Character();
		sf::Vector2f getPosition();
		void setPosition(int x, int y);
		void move(int dir, int limX, int limY);
		bool load(sf::Vector2u tileSize, std::string tileset);
		void update(sf::Vector2u tileSize, int x, int y);
		void cleanTile();
		sf::Sprite spritePerso;
		
	private:
		sf::Vector2f m_charPos;
		const static int m_speed = 4; //in pixel
		sf::Texture m_skin;
		sf::VertexArray m_character;
		int m_dirCharacter;
		

		
		//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		//{
//			sf::RectangleShape character(sf::Vector2f(32, 32));

//			character.setPosition(m_charPos.x, m_charPos.y);

//			//on applique la texturedu tileset
//			states.texture = &m_skin;

//			target.draw(character, states);
			//window.draw(spritePerso);

		//}
	};
}

#endif //CHARACTER_H
