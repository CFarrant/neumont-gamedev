#include "pch.h"
#include "Vector2D.h"

namespace nc
{
	const Vector2D Vector2D::left = Vector2D{ -1, 0 };
	const Vector2D Vector2D::right = Vector2D{ 1, 0 };
	const Vector2D Vector2D::up = Vector2D{ 0, -1 };
	const Vector2D Vector2D::down = Vector2D{ 0, 1 };
	const Vector2D Vector2D::forward = Vector2D{ 1, 0 };

	std::istream & operator>>(std::istream & stream, Vector2D & v)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			// {0, -3}
			std::string vx = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			v.x = std::stof(vx);

			std::string vy = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			v.y = std::stof(vy);
		}

		return stream;
	}
}