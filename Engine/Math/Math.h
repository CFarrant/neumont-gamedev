#pragma 
#include "Vector2D.h"

namespace nc 
{
	const float PI = 3.14159265358979f; // 180*
	const float TWO_PI = PI * 2; // 360*
	const float HALF_PI = PI * 0.5f; // 90*
	const float RAD_TO_DEG = 180.0f / PI;
	const float DEG_TO_RAD = PI / 180.0f;

	inline float RadiansToDegrees(float radians) { return radians * (180.0f / PI); }
	inline float DegreesToRadians(float degrees) { return degrees * (PI / 180.0f); }

	template <typename T>
	inline T Clamp(T v, T min, T max)
	{
		if (v < min) { v = min; }
		if (v > max) { v = max; }

		return v;
	}

	template <>
	inline nc::Vector2D Clamp<nc::Vector2D>(nc::Vector2D v, nc::Vector2D min, nc::Vector2D max)
	{
		v.x = Clamp(v.x, min.x, max.y);
		v.y = Clamp(v.y, min.y, max.y);

		return v;
	}

	template <typename T>
	inline T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);
		return (a + ((b - a) * t)); // t = 0 - 1;
	}
}