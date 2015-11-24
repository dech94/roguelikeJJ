#include "Map.h"

namespace local {

Map::Map(int width, int height)
:m_width(width)
,m_height(height)
,m_noise()
{
	std::vector<float> map;
	m_map = map;

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
	m_map.insert(m_map.begin()+(y*m_width + x),value);
}

void Map::Compute()
{
	for(float i=0;i<m_width;i++)
	{
		for(float j=0;j<m_height;j++)
		{
			m_map.push_back((m_noise.Compute(i,j)));
			//m_map.push_back(std::fabs(m_noise.Stack(4,0.5,0.1,i,j)));
			//printf("%f ",m_noise.Stack(30,0.5,0.1,i,j));
		}
	
	}
}

sf::VertexArray Map::Print()
{
	// tableau de vertex (futur -> étagement altitudinal + tiles)
	sf::VertexArray pixel(sf::Points,(m_width*m_height));
	int count = 0;
	for (int i = 0; i < m_width; i ++)
	{
		for (int j = 0; j < m_height; j ++)
		{
			pixel[count].position = sf::Vector2f(i, j);
			pixel[count].color = sf::Color(255,255,255,255*getValue(i,j));
			count++;
		}
	}
	return pixel;
}

}

