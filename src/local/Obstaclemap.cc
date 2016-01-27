#include "Obstaclemap.h"

namespace local
{
	/*explicit*/ Obstaclemap::Obstaclemap(const local::Heightmap& heightmap)
	:Tilemap(heightmap)
	{
		m_obstacle.resize(1);
	}

	/*virtual*/ Obstaclemap::~Obstaclemap()
	{

	}

	void Obstaclemap::update(sf::Vector2u tileSize, int x, int y)
	{
		
		x=floor(x/32);
		y=floor(y/32);
//		printf("%d, %d\n",x,y);
		
		//TODO vérifier le changement de tile 
		std::size_t idx = 0;

		//On remplit le tableau de vertex avec des quad
		for (int i = x-MARGE; i < x+MARGE+1; i ++)
		{
			for (int j = y-MARGE; j < y+MARGE+1; j ++)
			{
				float value = m_heightmap.getValue(i,j);
			
				int tileNum = convert(value);

				if(tileNum != 1)
				{
					m_obstacle.add(sf::IntRect((i+1)*tileSize.x, j*tileSize.y, tileSize.x, tileSize.y));
					m_obstacle.resize(m_obstacle.size()++);
				}
			
				int posX = tileNum % (m_tileset.getSize().x/tileSize.x);
				int posY = tileNum / (m_tileset.getSize().x/tileSize.x);
			
				//on récupère un pointeur vers le quad courant
				sf::Vertex* quad= &m_tilemap[idx * 4];

				//on définit la position pour chacun des coins du quad
				quad[0].position = sf::Vector2f(i*tileSize.x, j*tileSize.y);
				quad[1].position = sf::Vector2f((i+1)*tileSize.x, j*tileSize.y);
				quad[2].position = sf::Vector2f((i+1)*tileSize.x, (j+1)*tileSize.y);
				quad[3].position = sf::Vector2f(i*tileSize.x, (j+1)*tileSize.y);
			
				//on définit les coordonnées de la texture à utiliser
				quad[0].texCoords = sf::Vector2f(posX*tileSize.x, posY*tileSize.y);
				quad[1].texCoords = sf::Vector2f((posX+1)*tileSize.x, posY*tileSize.y);
				quad[2].texCoords = sf::Vector2f((posX+1)*tileSize.x, (posY+1)*tileSize.y);
				quad[3].texCoords = sf::Vector2f(posX*tileSize.x, (posY+1)*tileSize.y);

				idx++;
			}
		}
	}

	int Obstaclemap::convert(float value){
	
		int tile = 1;
			if(value < -0.2)
			{
				tile = 0;
			}
			else
			{
				tile = 1;
			}

	return tile;
	}

	bool Obstaclemap::isReachable(sf::IntRect rec)
	{
		return false;
	}
}

