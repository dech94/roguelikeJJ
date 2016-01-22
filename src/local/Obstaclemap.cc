#include "Obstaclemap.h"

namespace local
{
	/*explicit*/ Obstaclemap::Obstaclemap(const local::Heightmap& heightmap)
	:Tilemap(heightmap)
	{
	
	}

	/*virtual*/ Obstaclemap::~Obstaclemap()
	{

	}

	int Obstaclemap::convert(float value){
	
		int tile = 1;
			if(value < -0.1)
			{
				tile = 0;
			}
			else
			{
				tile = 1;
			}

	return tile;
	}

	bool Obstaclemap::isReachable(int x, int y)
	{
		return false;
	}
}

