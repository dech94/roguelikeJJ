#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include <SFML/Graphics.hpp>
#include "Noise.h"


namespace local {
  class Heightmap {
  public:
	explicit Heightmap(int width, int height, unsigned seed);
	virtual ~Heightmap();
	float getValue(int x, int y) const;
	void setValue(int x, int y, float value);
	void Compute();
	int getWidth() const;
	int getHeight() const;
	sf::VertexArray Print();

  private:
	int m_width;
	int m_height;
	std::vector<float> m_map;
	local::Noise m_noise;
  };
}
#endif // HEIGHTMAP_H
