#pragma once
#include "Math/Vector2D.h"
#include "Math/Color.h"

namespace nc
{
	struct Particle
	{
		Vector2D position;
		Vector2D prevPosition;
		Vector2D velocity;
		Color color;
		float damping{ 0.98f };
		float lifetime;
		bool active{ false };
	};
}