#include "Tilemap.h"

/*explicit*/Tilemap::Tilemap(local::Heightmap heightmap)
:m_heightmap(heightmap)
{
	
}

/*virtual*/Tilemap::~Tilemap()
{

}

bool Tilemap::load( sf::Vector2u tileSize)
{
	//chargement des tiles
	if (!m_tileset.loadFromFile("tile.png"))
	{
		return false;
	}
	
	m_tilemap.setPrimitiveType(sf::Quads);
	size = m_heightmap.getHeight()*m_heightmap.getWidth()*4;
	m_tilemap.resize(size);

	//On remplit le tableau de vertex avec des quad
	for (unsigned int i = 0; i < m_heightmap.getWidth(); i ++)
	{
		for (unsigned int j = 0; j < m_heightmap.getHeight(); j ++)
		{
			float value = m_heightmap.getValue[i,j];
			
			int tileNum = convert(value);
			
			int posX = tileNum % (m_tileset.getSize().x/tileSize.x);
			int posY = tileNum / (m_tileset.getSize().x/tileSize.x);
			
			//on récupère un pointeur vers le quad courant
			sf::Vertex* quad= &m_tilemap[(i+j*m_heightmap.getWidth())*4];
			
			//on définit la position pour chacun des coins du quad
			quad[0].position = game::Vector2f(i*tileSize.x, j*tileSize.y);
			quad[1].position = game::Vector2f((i+1)*tileSize.x, j*tileSize.y);
			quad[2].position = game::Vector2f((i+1)*tileSize.x, (j+1)*tileSize.y);
			quad[3].position = game::Vector2f(i*tileSize.x, (j+1)*tileSize.y);
			
			//on définit les coordonnées de la texture à utiliser
			quad[0].texCoords = game::Vector2f(posX*tileSize.x, posY*tileSize.y);
			quad[1].texCoords = game::Vector2f((posX+1)*tileSize.x, posY*tileSize.y);
			quad[2].texCoords = game::Vector2f((posX+1)*tileSize.x, (posY+1)*tileSize.y);
			quad[3].texCoords = game::Vector2f(posX*tileSize.x, (posY+1)*tileSize.y);
		}
	}
	
	return true;
}
