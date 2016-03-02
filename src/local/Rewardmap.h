#ifndef REWARDMAP_H
#define REWARDMAP_H

#include "Tilemap.h"
#include "Heightmap.h"
#include <random>

namespace local
{
	class Rewardmap : public local::Tilemap
	{
		public:

			Rewardmap(local::Heightmap& heightmap, unsigned seed, int HMAP_WIDTH, int HMAP_HEIGHT);
			virtual ~Rewardmap();
			void update(sf::Vector2u tileSize, int x, int y);
			int convert(float value);
			int isColecable(sf::IntRect rec, int HMAP_WIDTH, int HMAP_HEIGHT);

		private:

			std::vector<sf::IntRect> m_obstacle;
			std::vector<int> m_type;
			std::mt19937_64 engine;
			std::vector<sf::Vector2u> m_reward;

	};
}
#endif // Rewardmap_H
