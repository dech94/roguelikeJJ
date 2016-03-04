#ifndef WAVE_H
#define WAVE_H

#include "Ennemy.h"
#include <random>

namespace local{
	class Wave
	{
	public:
		explicit Wave(int x, int y, int ennemies, unsigned seed, int HMAP_WIDTH, int HMAP_HEIGHT);
		virtual ~Wave();
		void update(int posPersoX, int posPersoY, int limX, int limY);
		bool getStatus();
		sf::Sprite getSprite(int i);
	private:
		sf::Vector2f m_charPos;
		bool m_gameOver;
		std::vector<Ennemy> m_pool;
		int m_ennemies;
		std::mt19937_64 engine;
	};
}

#endif //WAVE_H
