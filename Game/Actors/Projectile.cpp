#include "Projectile.h"
#include "Math/Math.h"
#include <fstream>

void Projectile::OnCollision(Actor * actor)
{
	if (actor->GetType() == eType::ENEMY) {
		m_destroy = true;
	}
}

bool Projectile::Load(const std::string & filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		Actor::Load(stream);

		std::string line;
		std::getline(stream, line); //stream into thrust
		m_thrust = stof(line);
	}

	return false;
}

void Projectile::Update(float dt)
{
	nc::Vector2D direction = nc::Vector2D::Rotate(nc::Vector2D::up, m_transform.angle);
	nc::Vector2D velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;
	//m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90);

	m_transform.Update();
}
