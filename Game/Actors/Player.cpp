#include "Player.h"
#include "Math/Math.h"
#include <fstream>

bool Player::Load(const std::string & filename)
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

		std::getline(stream, line); //stream into rotation rate
		m_rotationRate = stof(line);

		stream.close();
	}

	return success;
}

void Player::Update(float dt)
{
	nc::Vector2D force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2D::up * m_thrust; }
	force = nc::Vector2D::Rotate(force, m_transform.angle);
	//force = force + nc::Vector2D{ 0, 200 }; //gravity values
	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.99f;

	m_transform.position = m_transform.position + (m_velocity * dt);

	//rotate
	if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * nc::DegreesToRadians(m_rotationRate)); }
	if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * nc::DegreesToRadians(m_rotationRate)); }

	//wrap
	if (m_transform.position.x > 800) { m_transform.position.x = 0; }
	if (m_transform.position.x < 0) { m_transform.position.x = 800; }
	if (m_transform.position.y > 600) { m_transform.position.y = 0; }
	if (m_transform.position.y < 0) { m_transform.position.y = 600; }
}
