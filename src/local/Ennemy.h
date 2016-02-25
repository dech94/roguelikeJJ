#ifndef ENNEMY_H
#define ENNEMY_H

#include <game/Entity.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Ennemy
	{
	public:
		explicit Ennemy(int x, int y);
		virtual ~Ennemy();
		sf::Vector2f getPosition();
		int getDir();
		void setPosition(int x, int y);
		void attack(int posPersoX, int posPersoY, int limX, int limY);
		bool load(sf::Vector2u tileSize, std::string tileset);
		void update(sf::Vector2u tileSize, int x, int y);
		void cleanTile();
		sf::Sprite spriteEnnemy;
		sf::IntRect getHitBox();
		
	private:
		sf::Vector2f m_charPos;
		const static int m_speed = 2; //in pixel
		sf::Texture m_skin;
		sf::VertexArray m_Ennemy;
		int m_dirEnnemy;
	};
}

#endif //ENNEMY_H
