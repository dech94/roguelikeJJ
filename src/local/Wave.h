#ifndef WAVE_H
#define WAVE_H

#include "Ennemy.h"

namespace local{
	class Wave
	{
	public:
		explicit Wave(int x, int y, int number);
		virtual ~Wave();
		void update(sf::Vector2u tileSize, int x, int y);
		
	private:
		sf::Vector2f m_charPos;
		bool m_gameOver;
	};
}

#endif //WAVE_H
