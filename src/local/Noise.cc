#include "Noise.h"

namespace local {

	Noise::Noise(unsigned seed)
	{
		//seed engine (en parametre du constr)
		engine.seed(seed);

		// generate gradients
		std::uniform_real_distribution<float> borne_grad(0.0, 2.0 * M_PI);
		for (size_t i = 0; i<m_grad.size() ; ++i) 
		{
			float angle = borne_grad(engine);
			m_grad[i].x = std::cos(angle);
			m_grad[i].y = std::sin(angle);
		}

		// initialize permutation
		for (uint8_t i = 0; i < 255; ++i)
		{
			m_permut[i] = i;
		}

		m_permut[255] = 255; // On place 255 à la fin du tableau de permutation -> cc: boucle infinie

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

	float Noise::Compute(float x, float y)
	{
		uint8_t X = (uint8_t) std::fmod(x,256);
		float rx = std::fmod(x,1);

		uint8_t Y = (uint8_t) std::fmod(y,256);
		float ry = std::fmod(y,1);

		float nw = prodScal(getGrad(X  ,Y  ),{rx  ,ry  });
		float ne = prodScal(getGrad(X+1,Y  ),{rx-1,ry  });
		float sw = prodScal(getGrad(X  ,Y+1),{rx  ,ry-1});
		float se = prodScal(getGrad(X+1,Y+1),{rx-1,ry-1});

		float n = linear_interpolate(nw, ne, cos_interpolate(rx)); //cos_interpolate(rx));
		float s = linear_interpolate(sw, se, cos_interpolate(rx)); // cos_interpolate(rx));

		return linear_interpolate(n, s, cos_interpolate(ry)); //cos_interpolate(ry));
	}

	float Noise::Stack(int nbAppel, float persistance, float x, float y)
	{
		float res = 0;
		float f = 2; // diversification du paysage
		float amplitude = 2.7; //amplitude entre valeur min-max

		for(int i=0; i < nbAppel; i++)
		{
			//On additionne le buit avec res
			res+=Compute(x*f,y*f)*amplitude;

			//On change de bruit
			amplitude*=persistance;
			f*=2;
		}

		//pour conserver nos valeurs entre -1 et 1
		float limite_geo = (1 - persistance) / (1 - amplitude);

		return res*limite_geo;
	}

}
