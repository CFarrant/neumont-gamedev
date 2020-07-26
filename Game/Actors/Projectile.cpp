#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
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
	m_lifetime -= dt;
	m_destroy = (m_lifetime <= 0);
	nc::Vector2D direction = nc::Vector2D::Rotate(nc::Vector2D::up, m_transform.angle);
	nc::Vector2D velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;
	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::white, 0.5f, 100, 200);
	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::red, 0.5f, 100, 200);
	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::yellow, 0.5f, 100, 200);
	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::orange, 0.5f, 100, 200);


	m_transform.Update();
}
