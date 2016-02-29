#include "Background.h"

namespace local
{
	/*explicit*/ Background::Background(local::Heightmap& heightmap)
	:Tilemap(heightmap)
	{
	
	}

	/*virtual*/ Background::~Background()
	{

	}

	int Background::convert(float value)
	{
		int tile = 0;
			if(value < -0.5)
			{
				tile = 0;
			}
			else if(value < -0.4)
			{
				tile = 1;
			}
			else if(value < -0.2)
			{
				tile = 2;
			}
			else if(value < -0.1)
			{
				tile = 3;
			}
			else if(value < 0)
			{
				tile = 4;
			}
			else if(value < 0.5)
			{
				tile = 4;
			}
			else if(value < 0.7)
			{
				tile = 7;
			}
			else
			{
				tile = 8;
			}
	return tile;
	}
}

