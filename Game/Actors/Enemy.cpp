#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h"
#include <fstream>

bool Enemy::Load(const std::string & filename)
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

void Enemy::Update(float dt)
{
	nc::Vector2D direction = m_target->GetTransform().position - m_transform.position;
	nc::Vector2D velocity = direction.Normalized() * m_thrust;
	m_transform.position += velocity * dt;
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90);

	m_transform.Update();
}

void Enemy::OnCollision(Actor * actor)
{
	if (actor->GetType() == eType::PROJECTILE) 
	{
		m_destroy = true;
		/*nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow, nc::Color::orange };
		nc::Color color = colors[rand() % 4];*/
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::red, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::orange, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::yellow, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::white, 1, 100, 200);
	}
}
