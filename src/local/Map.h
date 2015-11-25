#ifndef MAP_H
#define MAP_H

#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include <SFML/Graphics.hpp>
#include "Noise.h"


namespace local {
  class Map {
  public:
	explicit Map(int width, int height, unsigned seed);
	virtual ~Map();
	float getValue(int x, int y);
	void setValue(int x, int y, float value);
	void Compute();

	sf::VertexArray Print();



  private:
	int m_width;
	int m_height;
	std::vector<float> m_map;
	local::Noise m_noise;
  };
}
#endif // MAP_H
