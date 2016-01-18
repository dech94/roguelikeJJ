#ifndef OBSTACLEMAP_H
#define OBSTCLEMAP_H

#include "Tilemap.h"
#include "Heightmap.h"

namespace local
{
	class Obstaclemap : public local::Tilemap
	{
		public:

			Obstaclemap(const local::Heightmap& heightmap);
			virtual ~Obstaclemap();
			int convert(float value);
			bool isReachable(int x, int y);

	};
}
#endif // OBSTACLEMAP_H
