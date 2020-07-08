#pragma once
#include <istream>
#include <string>

namespace nc
{
	struct Vector2D
	{
		float x, y;

		Vector2D() : x{ 0 }, y{ 0 } {}
		Vector2D(float x, float y) : x{ x }, y{ y } {}
		Vector2D(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

		float& operator [] (size_t index) { return (&x)[index]; }
		const float& operator [] (size_t index) const { return (&x)[index]; }

		void Set(float x, float y) { this->x = x; this->y = y; }

		Vector2D operator + (const Vector2D& v) const { return Vector2D{ x + v.x, y + v.y }; }
		Vector2D operator - (const Vector2D& v) const { return Vector2D{ x - v.x, y - v.y }; }
		Vector2D operator * (const Vector2D& v) const { return Vector2D{ x * v.x, y * v.y }; }
		Vector2D operator / (const Vector2D& v) const { return Vector2D{ x / v.x, y / v.y }; }

		Vector2D operator + (float s) const { return Vector2D{ x + s, y + s }; }
		Vector2D operator - (float s) const { return Vector2D{ x - s, y - s }; }
		Vector2D operator * (float s) const { return Vector2D{ x * s, y * s }; }
		Vector2D operator / (float s) const { return Vector2D{ x / s, y / s }; }

		Vector2D& operator += (const Vector2D& v) { x += v.x; y += v.y; return *this; }
		Vector2D& operator -= (const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
		Vector2D& operator *= (const Vector2D& v) { x *= v.x; y *= v.y; return *this; }
		Vector2D& operator /= (const Vector2D& v) { x /= v.x; y /= v.y; return *this; }

		Vector2D& operator += (float s) { x += s; y += s; return *this; }
		Vector2D& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2D& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2D& operator /= (float s) { x /= s; y /= s; return *this; }

		Vector2D operator - () { return Vector2D{ -x, -y }; }

		friend std::istream& operator >> (std::istream& stream, Vector2D& v);

		float Length() const;
		float LengthSquared() const;
		
		static float Distance(const Vector2D& v1, const Vector2D& v2);
		Vector2D Normalized() const;
		void Normalize();
		static Vector2D Rotate(const Vector2D& v, float radians);

		static const Vector2D left; // { -1, 0 }
		static const Vector2D right; // { 1, 0 }
		static const Vector2D up; // { 0, -1 }
		static const Vector2D down; // { 0, 1 }
		static const Vector2D forward; // { 1, 0 }
	};

	inline float Vector2D::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline float Vector2D::LengthSquared() const
	{
		return (x * x) + (y * y);
	}

	inline float Vector2D::Distance(const Vector2D& v1, const Vector2D& v2)
	{
		Vector2D v = v1 - v2;
		return v.Length();
	}
	
	inline Vector2D Vector2D::Normalized() const
	{
		float length = Length();
		Vector2D n = (length == 0.0f) ? Vector2D{ 0.0f, 0.0f } : *this / length;
		return n;
	}
	
	inline void Vector2D::Normalize()
	{
		float length = Length();
		if (length == 0.0f)
		{
			*this = Vector2D{ 0.0f, 0.0f };
		}
		else
		{
			*this /= length;
		}
	}

	inline Vector2D Vector2D::Rotate(const Vector2D& v, float radians) 
	{
		float x = v.x * std::cos(radians) - v.y * std::sin(radians);
		float y = v.x * std::sin(radians) + v.y * std::cos(radians);
		return Vector2D{ x, y };
	}
}
