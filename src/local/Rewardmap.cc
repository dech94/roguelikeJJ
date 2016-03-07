#include "Rewardmap.h"

namespace local
{
	/*explicit*/ Rewardmap::Rewardmap(local::Heightmap& heightmap, unsigned seed, int HMAP_WIDTH, int HMAP_HEIGHT)
	:Tilemap(heightmap)
	{
		m_obstacle.resize(m_heightmap.getWidth()*m_heightmap.getHeight());
		m_type.resize(m_heightmap.getWidth()*m_heightmap.getHeight());

		//seed engine (en parametre du constr)
		engine.seed(seed);

		// generate gradients
		std::uniform_int_distribution<int> posX(32, HMAP_WIDTH-32);
		std::uniform_int_distribution<int> posY(32, HMAP_HEIGHT-32);
		sf::Vector2u position;
		m_reward.resize(100);
		for (int i = 0; i<100 ; ++i) 
		{
			position.x = posX(engine);
			position.y = posY(engine);
			m_reward[i]=position;
		}
	}

	/*virtual*/ Rewardmap::~Rewardmap()
	{

	}

	void Rewardmap::update(sf::Vector2u tileSize, int x, int y)
	{
		x=floor(x/32);//récupérer la tile courante
		y=floor(y/32);
		//printf("%d, %d\n",x,y);
		
		//TODO vérifier le changement de tile 
		std::size_t idx = 0;

		//On remplit le tableau de vertex avec des quad
		for (int i = x-MARGE; i < x+MARGE+1; i ++)
		{
			for (int j = y-MARGE; j < y+MARGE+1; j ++)
			{
				float value = m_heightmap.getValue(i,j);
				int tileNum = 0;
				sf::Vector2u tmp = {i,j};

				for (unsigned k = 0; k < 100; k++)
				{
					if(m_reward[k] == tmp)
					{
						tileNum = convert(value);
						m_obstacle[k] = (sf::IntRect((i)*tileSize.x, j*tileSize.y, tileSize.x, tileSize.y));
						m_type[k] = tileNum;

					}
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
			if(value < 0.20 && value >= -0.10)
			{
				tile = 1;
			}
			else if (value < 0.40 && value >= 0.20)
			{
				tile = 2;
			}
			else if (value < 0.60 && value >= 0.40)
			{
				tile = 3;
			}
			else if (value < 0.9 && value >= 0.60)
			{
				tile = 4;
			}
			else
			{
				tile = 0;
			}

	return tile;
	}

	int Rewardmap::isColecable(sf::IntRect rec, int HMAP_WIDTH, int HMAP_HEIGHT)
	{
		int key = 0;
		int tmp = 0;
		for(unsigned int k=0;k<m_obstacle.size();k++)
		{
			if(rec.intersects(m_obstacle[k]))
			{
				key = m_type[k];
				tmp = k;
			}
		}
		if(tmp!=0)
		{
			m_reward.erase(m_reward.begin()+tmp);
			m_obstacle.erase(m_obstacle.begin()+tmp);
			m_type.erase(m_type.begin()+tmp);

			std::uniform_int_distribution<int> posX(32, HMAP_WIDTH-32);
			std::uniform_int_distribution<int> posY(32, HMAP_HEIGHT-32);
			sf::Vector2u position;
			position.x = posX(engine);
			position.y = posY(engine);
			m_reward[tmp]=position;
		}
		return key;
	}
}

