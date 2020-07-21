#pragma once
#include <random>

namespace nc
{
	inline float Random() // 0 - 1.0
	{
		return rand() / static_cast<float>(RAND_MAX); // 0 / 10 = 0 | 5 / 10 = 0.5 | 10 / 10 = 1.0
	}

	inline float Random(float min, float max) // 3 - 10 = 7 | 3 + 7 * (0 - 1)
	{
		if (min > max)
		{
			std::swap(min, max);
		}
		return min + ((max - min) * Random());
	}
}