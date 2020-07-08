#pragma once
#include "Vector2D.h"

namespace nc
{
	struct Transform
	{
		Vector2D position;
		float scale;
		float angle;

		Transform() : position{ 0,0 }, scale{ 1 }, angle{ 0 } {}
		Transform(const Vector2D& position, float scale = 1, float angle = 0) : position{ position }, scale{ scale }, angle{ angle } {}

		friend std::istream& operator >> (std::istream& stream, Transform& t);
	};
}
