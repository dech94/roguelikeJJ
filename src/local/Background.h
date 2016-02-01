#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Tilemap.h"
#include "Heightmap.h"

namespace local
{
	class Background : public local::Tilemap
	{
		public:

			Background(const local::Heightmap& heightmap);
			virtual ~Background();
			int convert(float value);
	};
}
#endif // BACKGROUND_H
