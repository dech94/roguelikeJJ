#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstdint>
#include <array>
#include <random>
#include <cmath>
#include <../game/Vector.h>

namespace local {
  class Noise {
  public:
    	Noise();
	~Noise();
	void Compute();
	float linear_interpolate(float a, float b, float x);

  private:
	std::mt19937_64 engine;
	std::array<game::Vector2f, 256> m_grad;
	std::array<uint8_t, 256> m_permut;

	 const game::Vector2f& get(uint8_t i, uint8_t j) const
	{
		uint8_t index = i + m_permut.at(j);
		return m_grad.at(index);
	}
  };
}
#endif // NOISE_H
