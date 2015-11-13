#include "noise.h"

int main() {
	int size = 10;
	Noise noisetest(size);
	noisetest.Compute();
	noisetest.to_String();
return 0;
}
