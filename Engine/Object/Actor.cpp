#pragma once

#include "pch.h"
#include "Actor.h"
#include <fstream>
#include <string>

nc::Actor::Actor() {}

nc::Actor::Actor(const Transform& transform, const Shape& shape)
{
	m_shape = shape;
	m_transform = transform;
}

bool nc::Actor::Load(const std::string & filename)
{
	bool success = false;
	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		Load(stream);

		stream.close();
	}
	return success;
}

void nc::Actor::Load(std::istream & stream)
{
	stream >> m_transform;

	std::string shapename;
	std::getline(stream, shapename);

	m_shape.Load(shapename);
}

void nc::Actor::Update(float dt)
{
}

void nc::Actor::Draw(Core::Graphics & graphics)
{
	m_shape.Draw(graphics, m_transform);
}

nc::Transform& nc::Actor::GetTransform()
{
	return this->m_transform;
}

nc::Shape& nc::Actor::GetShape()
{
	return this->m_shape;
}
