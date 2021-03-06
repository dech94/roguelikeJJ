#include "Obstaclemap.h"

namespace local
{
	/*explicit*/ Obstaclemap::Obstaclemap(local::Heightmap& heightmap)
	:Tilemap(heightmap)
	{
		m_obstacle.resize(m_heightmap.getWidth()*m_heightmap.getHeight());
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
					m_obstacle[idx] = (sf::IntRect((i)*tileSize.x, j*tileSize.y, tileSize.x, tileSize.y));
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
			else if (value < -0.11 && value > -0.114)
			{
				tile = 3;
			}
			else if ((value < 0.1 && value > 0.08) || (value < 0.13 && value > 0.128) || (value < 0.20 && value > 0.198) || (value < 0.60 && value > 0.588))
			{
				tile = 2;
			}
			else
			{
				tile = 1;
			}

	return tile;
	}

	int Obstaclemap::isReachable(sf::IntRect rec, int dir)
	{
		int posblock = 4;
		for(unsigned int i=0;i<m_obstacle.size();i++)
		{
			if(rec.intersects(m_obstacle[i]))
			{
				posblock = dir;
			}
		}
		return posblock;
	}
}

