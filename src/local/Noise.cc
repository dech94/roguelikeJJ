#include "Noise.h"

namespace local {

Noise::Noise()
{
	// generate gradients
	std::uniform_real_distribution<float> borne_grad(0.0, 2.0 * M_PI);
	for (size_t i = 0; i<m_grad.size() ; ++i) 
	{
		float angle = borne_grad(engine);
		m_grad[i].x = std::cos(angle);
		m_grad[i].y = std::sin(angle);
	}

	// initialize permutation
	for (uint8_t i = 0; i < 256; ++i)
	{
		m_permut[i] = i;
	}

	//m_perm[255] = 255; // On place 255 à la fin du tableau de permutation

	// generate permutation
	std::uniform_int_distribution<uint8_t> borne_permut(0, 255);
	for (unsigned i = 0; i < 2560; ++i)
	{
		uint8_t j = borne_permut(engine);
		uint8_t k = borne_permut(engine);
		std::swap(m_permut[j], m_permut[k]);
	}
}

Noise::~Noise()
{

}

void Compute()
{
	//TODO
}

float Noise::linear_interpolate(float a, float b, float x)
{
	return (1. - x) * a + x * b;
}

}
