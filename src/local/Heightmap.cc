#include "Heightmap.h"

#include <cstdio>

namespace local {

Heightmap::Heightmap(int width, int height, unsigned seed)
:m_width(width)
,m_height(height)
,m_noise(seed)
{
	m_map.resize(width * height);
}

Heightmap::~Heightmap()
{

}

float Heightmap::getValue(int x, int y) const
{
	return m_map[y*m_width + x];

}

void Heightmap::setValue(int x, int y, float value)
{
	m_map[y*m_width + x] = value;
	// m_map.insert(m_map.begin()+(y*m_width + x),value);
}

void Heightmap::Compute()
{
	float x,y;
	for(int i=0;i<m_width;i++)
	{
		x = static_cast<float>(i) / m_width;
		for(int j=0;j<m_height;j++)
		{
			y = static_cast<float>(j) / m_height;
			//setValue(i, j, m_noise.Compute(x,y));
			setValue(i, j, m_noise.Stack(10,0.5,x,y));
			//printf("%f ",m_noise.Stack(10,0.5,x,y));
		}
	
	}
}

int Heightmap::getWidth() const
{
	return m_width;
}

int Heightmap::getHeight() const
{
	return m_height;
}

sf::VertexArray Heightmap::Print()
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
			uint8_t r = 0;
			uint8_t g = 0;
			uint8_t b = 0;
			uint8_t alpha = 255;//*std::fabs(value);
			if(value < -0.5)
			{
				r = 0;
				g = 127;
				b = 255;
			}
			else if(value < -0.4)
			{
				r = 116;
				g = 208;
				b = 241;
			}
			else if(value < -0.2)
			{
				r = 254;
				g = 227;
				b = 71;
			}
			else if(value < 0.15)
			{
				r = 58;
				g = 137;
				b = 35;
			}
			else if(value < 0.4)
			{
				r = 0;
				g = 86;
				b = 27;
			}
			else if(value < 0.5)
			{
				r = 204;
				g = 85;
				b = 0;
			}
			else if(value < 0.7)
			{
				r = 206;
				g = 206;
				b = 206;
				//alpha = 255;
			}
			else
			{
				r = 255;
				g = 255;
				b = 255;
				//alpha = 255;
			}
			//uint8_t c = 255 * (value + 1) / 2;
			pixel[count].color = sf::Color(r, g, b, alpha);
			count++;
		}
	}
	return pixel;
}

}

