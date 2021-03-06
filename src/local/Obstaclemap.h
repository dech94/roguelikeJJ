#ifndef OBSTACLEMAP_H
#define OBSTCLEMAP_H

#include "Tilemap.h"
#include "Heightmap.h"

namespace local
{
	class Obstaclemap : public local::Tilemap
	{
		public:

			Obstaclemap(local::Heightmap& heightmap);
			virtual ~Obstaclemap();
			void update(sf::Vector2u tileSize, int x, int y);
			int convert(float value);
			int isReachable(sf::IntRect rec, int dir);

		private:

			std::vector<sf::IntRect> m_obstacle;

	};
}
#endif // OBSTACLEMAP_H
