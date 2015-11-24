#include "Map.h"

#include <cstdio>

namespace local {

Map::Map(int width, int height)
:m_width(width)
,m_height(height)
,m_noise()
{
	m_map.resize(width * height);
}

Map::~Map()
{

}

float Map::getValue(int x, int y)
{
	return m_map[y*m_width + x];

}

void Map::setValue(int x, int y, float value)
{
	m_map[y*m_width + x] = value;
	// m_map.insert(m_map.begin()+(y*m_width + x),value);
}

void Map::Compute()
{
	for(int i=0;i<m_width;i++)
	{
		for(int j=0;j<m_height;j++)
		{
			setValue(i, j, m_noise.Compute(static_cast<float>(i) / m_width, static_cast<float>(j) / m_height));
			//m_map.push_back(((m_noise.Stack(4,0.5,0.01,i,j))+1)/2);
			//printf("%f ",m_noise.Stack(30,0.5,0.1,i,j));
		}
	
	}
}

sf::VertexArray Map::Print()
{
	// tableau de vertex (futur -> étagement altitudinal + tiles)
	sf::VertexArray pixel(sf::Points,(m_width*m_height));
	int count = 0;
	for (int j = 0; j < m_height; j ++)
	{
		for (int i = 0; i < m_width; i ++)
		{
			pixel[count].position = sf::Vector2f(i, j);
			float value = getValue(i, j);
			uint8_t c = 255 * (value + 1) / 2;
			pixel[count].color = sf::Color(c, c, c, 255);
			count++;
		}
	}
	return pixel;
}

}

