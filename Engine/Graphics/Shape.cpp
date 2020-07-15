#include "pch.h"
#include "../Math/Matrix2D.h"
#include "Shape.h"
#include <fstream>

nc::Shape::Shape() {}

nc::Shape::Shape(const std::vector<nc::Vector2D>& points, const Color& color)
{
	this->m_points = points;
	this->m_color = color;
}

bool nc::Shape::Load(const std::string & filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_color; //read color

		std::string line; //read number of points
		std::getline(stream, line);
		size_t size;
		size = stoi(line);

		for (size_t i = 0; i < size; i++) //read points
		{
			Vector2D point;
			stream >> point;
			m_points.push_back(point);
		}

		stream.close();
	}

	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2D position, float scale, float angle)
{
	graphics.SetColor(this->m_color);

	Matrix2D mxs; //Scale
	mxs.Scale(scale);
	Matrix2D mxr; // Rotate
	mxr.Rotate(angle);

	Matrix2D mx = mxs * mxr; //Scale & Rotate

	for (size_t i = 0; i < this->m_points.size() - 1; i++)
	{
		nc::Vector2D p1 = this->m_points[i];
		nc::Vector2D p2 = this->m_points[i + 1];

		//scale & rotate
		p1 = p1 * mx; //scaling shape
		p2 = p2 * mx; //scaling shape

		p1 = p1 + position; //translating shape
		p2 = p2 + position; //translating shape

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y); //drawing shape
	}
}

void nc::Shape::Draw(Core::Graphics & graphics, const Transform & transform)
{
	Draw(graphics, transform.position, transform.scale, transform.angle);
}

void nc::Shape::SetColor(Color color)
{
	this->m_color = color;
}

const nc::Color & nc::Shape::GetColor() const
{
	return this->m_color;
}