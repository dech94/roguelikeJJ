#include "noise.h"

Noise::Noise(int size)
:m_size(size)
{
	m_map = new float *[size];
	for (int i = 0; i < size; i++)
	{
		m_map[i] = new float [size];
	}
}

Noise::~Noise()
{
	for (int i = 0; i < m_size; i ++)
	{
		
		delete [] m_map[i];
	}
	m_size = 0;
	delete [] m_map;
}

float Noise::get(int x, int y)
{
	return m_map[x][y];

}

void Noise::set(int x, int y, float value)
{
	m_map[x][y] = value;
}

void Noise::Compute()
{
	srand (time(NULL));
	for(int i=0;i<m_size;i++)
	{
		for(int j=0;j<m_size;j++)
		{
			set(i,j,random(-1,1));
		}
	}
}

void Noise::to_String()
{
	for(int i=0;i<m_size;i++)
	{
		for(int j=0;j<m_size;j++)
		{
			printf("[%f]",m_map[i][j]);
		}
		printf("\n");
	}
}

float Noise::random(float a, float b)
{
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

