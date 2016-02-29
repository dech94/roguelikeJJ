#include "Rewardmap.h"

namespace local
{
	/*explicit*/ Rewardmap::Rewardmap(local::Heightmap& heightmap)
	:Tilemap(heightmap)
	{
		m_obstacle.resize(m_heightmap.getWidth()*m_heightmap.getHeight());
		m_type.resize(m_heightmap.getWidth()*m_heightmap.getHeight());
	}

	/*virtual*/ Rewardmap::~Rewardmap()
	{

	}

	void Rewardmap::update(sf::Vector2u tileSize, int x, int y)
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

				if(tileNum != 0)
				{
					m_obstacle[idx] = (sf::IntRect((i)*tileSize.x, j*tileSize.y, tileSize.x, tileSize.y));
					m_type[idx] = (tileNum);
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

	int Rewardmap::convert(float value){
	
		int tile = 0;
			if(value < -0.10 && value > -0.101)
			{
				tile = 1;
			}
			else if (value < 0.30 && value > 0.299)
			{
				tile = 2;
			}
			else if (value < 0.50 && value > 0.499)
			{
				tile = 3;
			}
			else if (value < 0.80 && value > 0.799)
			{
				tile = 4;
			}
			/*else if (value == 2)
			{
				tile = 5;
			}*/
			else
			{
				tile = 0;
			}

	return tile;
	}

	int Rewardmap::isColecable(sf::IntRect rec)
	{
		sf::Vector2u tileSize(32,32);
		int key = 0;
		for(unsigned int k=0;k<m_obstacle.size();k++)
		{
			if(rec.intersects(m_obstacle[k]))
			{
				key = m_type[k];
				int ibis = m_obstacle[k].left/tileSize.x;
				int jbis = m_obstacle[k].top/tileSize.y;
				m_heightmap.setValue(ibis,jbis,m_heightmap.getValue(ibis,jbis)+0.0001);
				m_type[k]=0;
				m_obstacle[k]=(sf::IntRect(0, 0, 32, 32));
			}
		}
		
		return key;
	}
}

