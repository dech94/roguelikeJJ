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

	int Character::getDir()
	{
		return m_dirCharacter;
	}

	void Character::setPosition(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
	}

	sf::IntRect Character::getHitBox()
	{
		switch(m_dirCharacter)
		{
			case 0 :
					return (sf::IntRect(m_charPos.x,m_charPos.y-m_speed,16,32));
					break;
			case 1 :
					return (sf::IntRect(m_charPos.x,m_charPos.y+m_speed,16,32));
					break;
			case 2 : 
					return (sf::IntRect(m_charPos.x-m_speed,m_charPos.y,16,32));
					break;
			case 3 :
					return (sf::IntRect(m_charPos.x+m_speed,m_charPos.y,16,32));
					break;
			default:
					return (sf::IntRect(m_charPos.x,m_charPos.y,16,32));
		}
	}

	void Character::move(int dir, int limX, int limY, int dirBlock)
	{
		int nextX = m_charPos.x;
		int nextY = m_charPos.y;
		switch(dir)
		{
			case 0 :
				if(dirBlock!=0){
					nextY -= m_speed;
					if (nextY > 1000)
					{
						m_charPos.y -= m_speed;
						m_dirCharacter=0;
					}
				}
				break;

			case 1 :
				if(dirBlock!=1){
					nextY += m_speed;
					if (nextY < limY)
					{
						m_charPos.y += m_speed;
						m_dirCharacter=1;
					}
				}
				break;

			case 2 :
				if(dirBlock!=2){
					nextX -= m_speed;
					if (nextX > 1000)
					{
						m_charPos.x -= m_speed;
						m_dirCharacter=2;
					}
				}
				break;

			case 3 :
				if(dirBlock!=3){
					nextX += m_speed;
					if (nextX < limX)
					{
						m_charPos.x += m_speed;
						m_dirCharacter=3;
					}
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
		return true;
	}
	
	void Character::update(sf::Vector2u tileSize, int x, int y)
	{
		spritePerso.setTexture(m_skin);
		spritePerso.setTextureRect(sf::IntRect(m_dirCharacter*32, 0, 32, 32));
		spritePerso.setPosition(m_charPos);
	}

		void Character::cleanTile()
	{
		m_character.clear();
	}
}
