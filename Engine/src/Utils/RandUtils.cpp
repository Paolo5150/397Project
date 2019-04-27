#include "RandUtils.h"

namespace RandUtils
{
	void SeedRand(unsigned int seed) //Seeds with the time by default
	{
		srand(seed);
	}

	float RandFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = max - min;
		float r = random * diff;
		return min + r;
	}

	int RandInt(int min, int max)
	{
		return min + (std::rand() % (max - min + 1));
	}
}