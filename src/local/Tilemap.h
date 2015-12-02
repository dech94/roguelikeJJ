#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Heightmap.h"

namespace local
{
	class Tilemap : public sf::Drawable, public sf::Transformable
	{
		public:
			explicit Tilemap(local::Heightmap heightmap);
			virtual ~Tilemap();
			bool load(sf::Vector2u tileSize);
			
		
		private:
			sf::Texture m_tileset;
			local::Heightmap m_heightmap;
			sf::VertexArray m_tilemap;
			
			int convert(float value)
			{
				return 1;
			}
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				//on applique la transformation
				states.transform *= getTransform();
				
				//on applique la texturedu tileset
				states.texture = &m_tileset;
				
				//on dessine le tableau de vertex
				target.draw(m_tilemap, states);
			}
		
	};
}

#endif // TILEMAP_H
