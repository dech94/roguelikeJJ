#include "Wave.h"

namespace local {

/*explicit*/Wave::Wave(int x, int y, int ennemies, unsigned seed, int HMAP_WIDTH, int HMAP_HEIGHT)
	{
		m_charPos.x = x;
		m_charPos.y = y;
		m_gameOver = false;
		m_ennemies = ennemies;
		m_pool.resize(m_ennemies);

		//seed engine (en parametre du constr)
		engine.seed(seed);

		// generate gradients
		std::uniform_int_distribution<int> posX(32*32, HMAP_WIDTH*32-32);
		std::uniform_int_distribution<int> posY(32*32, HMAP_HEIGHT*32-32);

		for (int i = 0; i<m_ennemies ; ++i) 
		{
			Ennemy e; 
			e.setPosition(posX(engine),posY(engine));
			m_pool[i]= e;
			  if (!m_pool[i].load(sf::Vector2u(32,32), "bat.png"))
			  {
				printf("ERREUR");
			  }
		}
	}

/*virtuel*/Wave::~Wave()
	{
	}
	
	void Wave::update(int posPersoX, int posPersoY, int limX, int limY)
	{
		for (int i = 0; i<m_ennemies ; ++i) 
		{
			m_pool[i].attack(posPersoX, posPersoY, limX, limY);
			m_pool[i].update(sf::Vector2u(32,32), posPersoX, posPersoY);
		}
	}

	bool Wave::getStatus()
	{
		bool tmp = false;
		for (int i = 0; i<m_ennemies ; ++i) 
		{
			if(m_pool[i].getStatus())
			{
				tmp = true;
			}
		}
		return tmp;
	}

	sf::Sprite Wave::getSprite(int i)
	{
		return m_pool[i].spriteEnnemy;
	}
}

