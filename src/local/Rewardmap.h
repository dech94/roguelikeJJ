#ifndef REWARDMAP_H
#define REWARDMAP_H

#include "Tilemap.h"
#include "Heightmap.h"

namespace local
{
	class Rewardmap : public local::Tilemap
	{
		public:

			Rewardmap(local::Heightmap& heightmap);
			virtual ~Rewardmap();
			void update(sf::Vector2u tileSize, int x, int y);
			int convert(float value);
			int isColecable(sf::IntRect rec);

		private:

			std::vector<sf::IntRect> m_obstacle;
			std::vector<int> m_type;

	};
}
#endif // Rewardmap_H
