#include "Character.h"

namespace local {

/*explicit*/Character::Character(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
		m_dirCharacter = 0;
	}

/*virtuel*/Character::~Character()
	{
	}

	sf::Vector2f Character::getPosition()
	{
		return m_charPos;
	}

	void Character::setPosition(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
	}

	void Character::move(int dir, int limX, int limY)
	{
		int nextX = m_charPos.x;
		int nextY = m_charPos.y;
		switch(dir)
		{
			case 0 :
				nextY -= m_speed;
				if (nextY > 1000)
				{
					m_charPos.y -= m_speed;
					m_dirCharacter=0;
				}
				break;

			case 1 :
				nextY += m_speed;
				if (nextY < limY)
				{
					m_charPos.y += m_speed;
					m_dirCharacter=1;
				}
				break;

			case 2 :
				nextX -= m_speed;
				if (nextX > 1000)
				{
					m_charPos.x -= m_speed;
					m_dirCharacter=2;
				}
				break;

			case 3 :
				nextX += m_speed;
				if (nextX < limX)
				{
					m_charPos.x += m_speed;
					m_dirCharacter=3;
				}
				break;

			default :
				break;
		}
	}
	bool Character::load(sf::Vector2u tileSize, std::string tileset)
	{
		//chargement des tiles
		if (!m_skin.loadFromFile(tileset))
		{
			return false;
		}
		//m_character.setPrimitiveType(sf::Quads);
		//m_character.resize(2);
		return true;
	}
	
	void Character::update(sf::Vector2u tileSize, int x, int y)
	{
		//int tileNum = m_dirCharacter;
		spritePerso.setTexture(m_skin);
		spritePerso.setTextureRect(sf::IntRect(m_dirCharacter*32, 0, 32, 32));
		spritePerso.setPosition(m_charPos);
//		int posX = tileNum % (m_skin.getSize().x/tileSize.x);
//		int posY = tileNum / (m_skin.getSize().x/tileSize.x);
//			
//		//on récupère un pointeur vers le quad courant
//		sf::Vertex* quad= &m_character[0];

//		//on définit la position pour chacun des coins du quad
//		quad[0].position = sf::Vector2f(m_charPos.x-16, m_charPos.y-16);
//		quad[1].position = sf::Vector2f(m_charPos.x-16, m_charPos.y+16);
//		quad[2].position = sf::Vector2f(m_charPos.x+16, m_charPos.y+16);
//		quad[3].position = sf::Vector2f(m_charPos.x+16, m_charPos.y-16);
//			
//		//on définit les coordonnées de la texture à utiliser
//		quad[0].texCoords = sf::Vector2f(posX*tileSize.x, posY*tileSize.y);
//		quad[1].texCoords = sf::Vector2f((posX+1)*tileSize.x, posY*tileSize.y);
//		quad[2].texCoords = sf::Vector2f((posX+1)*tileSize.x, (posY+1)*tileSize.y);
//		quad[3].texCoords = sf::Vector2f(posX*tileSize.x, (posY+1)*tileSize.y);

//		//on définit les coordonnées de la texture à utiliser
//		quad[0].texCoords = sf::Vector2f(0, 0);
//		quad[1].texCoords = sf::Vector2f(0, 32);
//		quad[2].texCoords = sf::Vector2f(32, 32);
//		quad[3].texCoords = sf::Vector2f(32, 0);

	}

		void Character::cleanTile()
	{
		m_character.clear();
	}
}
