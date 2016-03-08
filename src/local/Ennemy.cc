#include "Ennemy.h"

namespace local {

/*explicit*/Ennemy::Ennemy()
	{
		m_charPos.x = 0;
		m_charPos.y = 0;
		m_dirEnnemy = 0;
		m_gameOver = false;
	}

/*virtuel*/Ennemy::~Ennemy()
	{
	}

	sf::Vector2f Ennemy::getPosition()
	{
		return m_charPos;
	}

	int Ennemy::getDir()
	{
		return m_dirEnnemy;
	}

	void Ennemy::setPosition(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
	}

	sf::IntRect Ennemy::getHitBox()
	{
		switch(m_dirEnnemy)
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

	void Ennemy::attack(int posPersoX, int posPersoY, int limX, int limY)
	{
		int nextX = m_charPos.x;
		int nextY = m_charPos.y;
		int dir = 5;
		if(m_charPos.y - posPersoY == 0){
			if (m_charPos.x - posPersoX > 0 && m_charPos.x - posPersoX < 550)
			{
				dir = 2;
			}
			else if (m_charPos.x - posPersoX < 0 && m_charPos.x - posPersoX > -550)
			{
				dir = 3;
			}
			else if (m_charPos.x - posPersoX == 0)
			{
				m_gameOver = true;
				dir = 5;
			}
			else
			{
				dir = 5;
			}
		}
		if (m_charPos.y - posPersoY > 0 && m_charPos.y - posPersoY < 550)
		{
			dir = 0;
		}
		if (m_charPos.y - posPersoY < 0 && m_charPos.y - posPersoY > -550)
		{
			dir = 1;
		}
		switch(dir)
		{
			case 0 :
				nextY -= m_speed;
				if (nextY > 1000)
				{
					m_charPos.y -= m_speed;
					m_dirEnnemy=0;
				}
				break;

			case 1 :
				nextY += m_speed;
				if (nextY < limY)
				{
					m_charPos.y += m_speed;
					m_dirEnnemy=1;
				}
				break;

			case 2 :
				nextX -= m_speed;
				if (nextX > 1000)
				{
					m_charPos.x -= m_speed;
					m_dirEnnemy=2;
				}
				break;

			case 3 :
				nextX += m_speed;
				if (nextX < limX)
				{
					m_charPos.x += m_speed;
					m_dirEnnemy=3;
				}
				break;

			default :
				break;
		}
	}
	bool Ennemy::load(sf::Vector2u tileSize, std::string tileset)
	{
		//chargement des tiles
		if (!m_skin.loadFromFile(tileset))
		{
			return false;
		}
		return true;
	}
	
	void Ennemy::update(sf::Vector2u tileSize, int x, int y)
	{
		spriteEnnemy.setTexture(m_skin);
		spriteEnnemy.setTextureRect(sf::IntRect(m_dirEnnemy*32, 0, 32, 32));
		spriteEnnemy.setPosition(m_charPos);
	}

	void Ennemy::cleanTile()
	{
		m_Ennemy.clear();
	}

	bool Ennemy::getStatus()
	{
		return m_gameOver;
	}
}


