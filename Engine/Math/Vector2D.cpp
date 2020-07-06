#include "pch.h"
#include "Vector2D.h"

namespace nc
{
	const Vector2D Vector2D::left = Vector2D{ -1, 0 };
	const Vector2D Vector2D::right = Vector2D{ 1, 0 };
	const Vector2D Vector2D::up = Vector2D{ 0, -1 };
	const Vector2D Vector2D::down = Vector2D{ 0, 1 };
	const Vector2D Vector2D::forward = Vector2D{ 1, 0 };
}