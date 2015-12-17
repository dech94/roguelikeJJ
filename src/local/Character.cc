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
}
