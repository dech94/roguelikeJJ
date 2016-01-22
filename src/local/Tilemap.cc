#include "Tilemap.h"

namespace local
{
	/*explicit*/ Tilemap::Tilemap(const local::Heightmap& heightmap)
	:m_heightmap(heightmap)
	{
	
	}

	/*virtual*/ Tilemap::~Tilemap()
	{

	}

	bool Tilemap::load(sf::Vector2u tileSize, std::string tileset)
	{
		//chargement des tiles
		if (!m_tileset.loadFromFile(tileset))
		{
			return false;
		}
		m_tilemap.setPrimitiveType(sf::Quads);

		// int size = m_heightmap.getHeight()*m_heightmap.getWidth()*4;
		int size = (2 * MARGE + 1) * (2 * MARGE + 1) * 4;
		m_tilemap.resize(size);

		return true;
	}
	
	void Tilemap::update(sf::Vector2u tileSize, int x, int y)
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

	void Tilemap::cleanTile()
	{
		m_tilemap.clear();
	}

	int Tilemap::convert(float value){
	
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
				tile = 5;
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

