#pragma once

#include <cstdlib> //srand, rand
#include <ctime> //time for rand seed

namespace RandUtils
{
	void SeedRand(unsigned int seed = (unsigned int)time(NULL));
	float RandFloat(float min = 0.0f, float max = 0.0f);
	int RandInt(int min = 0, int max = 0);
}

