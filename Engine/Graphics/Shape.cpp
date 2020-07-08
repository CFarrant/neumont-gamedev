#include "pch.h"
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

		while (!stream.eof()) //read points
		{
			Vector2D point;
			stream >> point;
			if (!stream.eof())
			{
				m_points.push_back(point);
			}
		}

		stream.close();
	}

	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2D position, float scale, float angle)
{
	graphics.SetColor(this->m_color);
	for (size_t i = 0; i < this->m_points.size() - 1; i++)
	{
		nc::Vector2D p1 = this->m_points[i];
		nc::Vector2D p2 = this->m_points[i + 1];

		p1 = p1 * scale; //scaling shape
		p2 = p2 * scale; //scaling shape

		p1 = nc::Vector2D::Rotate(p1, angle); //rotating shape
		p2 = nc::Vector2D::Rotate(p2, angle); //rotating shape

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