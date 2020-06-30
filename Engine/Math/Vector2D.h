#pragma once

namespace nc
{
	struct Vector2D
	{
		float x, y;

		Vector2D() : x{ 0 }, y{ 0 } {}
		Vector2D(float x, float y) : x{ x }, y{ y } {}

		void Set(float x, float y) { this->x = x; this->y = y; }

		Vector2D operator + (const Vector2D& v) const { return Vector2D{ x + v.x, y + v.y }; }
		Vector2D operator - (const Vector2D& v) const { return Vector2D{ x - v.x, y - v.y }; }
		Vector2D operator * (const Vector2D& v) const { return Vector2D{ x * v.x, y * v.y }; }
		Vector2D operator / (const Vector2D& v) const { return Vector2D{ x / v.x, y / v.y }; }

		Vector2D operator + (float s) const { return Vector2D{ x + s, y + s }; }
		Vector2D operator - (float s) const { return Vector2D{ x - s, y - s }; }
		Vector2D operator * (float s) const { return Vector2D{ x * s, y * s }; }
		Vector2D operator / (float s) const { return Vector2D{ x / s, y / s }; }
	};
}
