#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstdint>
#include <array>
#include <random>
#include <cmath>
#include <cassert>
#include <game/Vector.h>
#include <chrono>

namespace local {
	class Noise {
	public:
		explicit Noise(unsigned seed);
		virtual ~Noise();
		float Compute(float x, float y);
		float Stack(int nbAppel, float persistance, float x, float y);

	private:
		std::mt19937_64 engine;
		std::array<game::Vector2f, 256> m_grad;
		std::array<uint8_t, 256> m_permut;

		game::Vector2f& getGrad(uint8_t i, uint8_t j)
		{
			uint8_t index = i + m_permut.at(j);
			return m_grad.at(index);
		}

		float prodScal(const game::Vector2f& a, const game::Vector2f& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		 float linear_interpolate(float a, float b, float x)
		{
			return a * (1.0 - x) + b * x;
		}

		float cos_interpolate(float x)
		{
			return (1.0 - std::cos(M_PI * x)) * 0.5;
		}
	};
}
#endif // NOISE_H
