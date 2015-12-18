#include "Character.h"

namespace local {

/*explicit*/Character::Character(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
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

	void Character::move(int dir)
	{
		//TODO variable marge=1000, récup dyna taille hmap
		int nextX;
		int nextY;
		switch(dir)
		{
			case 0 :
				nextY = m_charPos.y - m_speed;
				if (nextY > 1000)
				{
					m_charPos.y -= m_speed;
				}
				break;

			case 1 :
				nextY = m_charPos.y + m_speed;
				if (nextY < 500*32 - 1000)
				{
					m_charPos.y += m_speed;
				}
				break;

			case 2 :
				nextX = m_charPos.x - m_speed;
				if (nextX > 1000)
				{
					m_charPos.x -= m_speed;
				}
				break;

			case 3 :
				nextX = m_charPos.x + m_speed;
				if (nextX < 500*32 - 1000)
				{
					m_charPos.x += m_speed;
				}
				break;

			default :
				break;
		}
	}
}
