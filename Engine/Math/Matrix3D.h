#pragma once
#include "Vector2D.h"

namespace nc
{
	struct Matrix3D
	{
		float m[3][3]; // column / row
		// m[0][0] m[1][0] m[2][0]
		// m[0][1] m[1][1] m[2][1]
		// m[0][2] m[1][2] m[2][2]

		void Scale(float s)
		{
			m[0][0] = s; m[1][0] = 0; m[2][0] = 0;
			m[0][1] = 0; m[1][1] = s; m[2][1] = 0;
			m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
		}

		void Scale(float sx, float sy)
		{
			m[0][0] = sx; m[1][0] = 0; m[2][0] = 0;
			m[0][1] = 0; m[1][1] = sy; m[2][1] = 0;
			m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
		}

		void Scale(const Vector2D& s)
		{
			m[0][0] = s.x; m[1][0] = 0; m[2][0] = 0;
			m[0][1] = 0; m[1][1] = s.y; m[2][1] = 0;
			m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
		}

		void Rotate(float angle)
		{
			m[0][0] = std::cos(angle); m[1][0] = std::sin(angle); m[2][0] = 0;
			m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle); m[2][1] = 0;
			m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
		}

		void SetIdentity() {
			m[0][0] = 1; m[1][0] = 0; m[2][0] = 0;
			m[0][1] = 0; m[1][1] = 1; m[2][1] = 0;
			m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
		}

		void Translate(const Vector2D& v)
		{
			m[0][0] = 1; m[1][0] = 0; m[2][0] = 0;
			m[0][1] = 0; m[1][1] = 1; m[2][1] = 0;
			m[0][2] = v.x; m[1][2] = v.y; m[2][2] = 1;
		}

		Matrix3D operator * (const Matrix3D& mx)
		{
			Matrix3D result;

			result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2];

			return result;
		}

		Vector2D operator * (const Vector2D& v)
		{
			Vector2D result;

			result.x = v.x * m[0][0] + v.y * m[0][1] + m[0][2];
			result.y = v.x * m[1][0] + v.y * m[1][1] + m[1][2];

			return result;
		}

		friend Vector2D operator * (const Vector2D& v, const Matrix3D& mx)
		{
			Vector2D result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

			return result;
		}
	};
}