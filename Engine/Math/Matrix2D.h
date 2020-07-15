#pragma once
#include "Vector2D.h"

namespace nc
{
	struct Matrix2D
	{
		float m[2][2]; // column / row
		// m[0][0] m[1][0]
		// m[0][1] m[1][1]

		Matrix2D() = default;
		Matrix2D(const Vector2D& column1, const Vector2D& column2)
		{
			m[0][0] = column1[0]; m[1][0] = column2[0];
			m[0][1] = column1[1]; m[1][1] = column2[1];
		}

		void Scale(float s)
		{
			m[0][0] = s; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s;
		}

		void Scale(float sx, float sy)
		{
			m[0][0] = sx; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = sy;
		}

		void Scale(const Vector2D& s) 
		{
			m[0][0] = s.x; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s.y;
		}

		void Rotate(float angle) 
		{
			m[0][0] = std::cos(angle); m[1][0] = std::sin(angle);
			m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle);
		}

		void SetIdentity() {
			m[0][0] = 1; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = 1;
		}

		Matrix2D operator * (const Matrix2D& mx)
		{
			Matrix2D result;

			result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1];
			result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1];
			result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1];
			result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1];

			return result;
		}

		Vector2D operator * (const Vector2D& v)
		{
			Vector2D result;

			result.x = v.x * m[0][0] + v.y * m[0][1];
			result.y = v.x * m[1][0] + v.y * m[1][1];

			return result;
		}

		friend Vector2D operator * (const Vector2D& v, const Matrix2D& mx) 
		{
			Vector2D result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1];

			return result;
		}
	};
}