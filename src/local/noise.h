#ifndef NOISE_H
#define NOISE_H

#include<stdlib.h>
#include<stdio.h>
#include <time.h>

  class Noise {
  public:
    	Noise(int size);
	~Noise();
	float get(int x, int y);
	void set(int x, int y, float value);
	void Compute();
	void to_String();
	float random(float a, float b);
	
  private:
	int m_size;
	float ** m_map;
  };

#endif // NOISE_H
