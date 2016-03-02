#include "Wave.h"

namespace local {

/*explicit*/Ennemy::Ennemy(int x, int y)
	{
		m_charPos.x = x;
		m_charPos.y = y;
		m_gameOver = false;
	}

/*virtuel*/Ennemy::~Ennemy()
	{
	}
	
	void Wave::update(sf::Vector2u tileSize, int x, int y)
	{
		
	}
}
