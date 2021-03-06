#ifndef CHARACTER_H
#define CHARACTER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Character
	{
	public:
		explicit Character(int x, int y);
		virtual ~Character();
		sf::Vector2f getPosition();
		int getDir();
		void setPosition(int x, int y);
		void move(int dir, int limX, int limY, int dirBlock);
		bool load(sf::Vector2u tileSize, std::string tileset);
		void update(sf::Vector2u tileSize, int x, int y);
		void cleanTile();
		sf::Sprite spritePerso;
		sf::IntRect getHitBox();
		
	private:
		sf::Vector2f m_charPos;
		const static int m_speed = 2; //in pixel
		sf::Texture m_skin;
		sf::VertexArray m_character;
		int m_dirCharacter;
	};
}

#endif //CHARACTER_H
