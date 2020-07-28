#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
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
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		g_audioSystem.PlayAudio("Laser");
		nc::Actor* projectile = new Projectile();
		projectile->Load("projectile.actor");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	nc::Vector2D force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2D::up * m_thrust; }
	force = nc::Vector2D::Rotate(force, m_transform.angle);
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

	if (force.LengthSquared() > 0)
	{
		Actor* locator = m_children[0];
		g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle(), 20, 1, nc::Color::white, 1, 100, 200);
		g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle(), 20, 1, nc::Color::red, 1, 100, 200);
		g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle(), 20, 1, nc::Color::yellow, 1, 100, 200);
		g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle(), 20, 1, nc::Color::orange, 1, 100, 200);
	}

	m_transform.Update();

	for (Actor* child : m_children)
	{
		child->Update(dt);
	}
}

void Player::OnCollision(Actor * actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
		m_destroy = true;

		auto enemies = m_scene->GetActors<Enemy>();
		for (auto enemy : enemies) {
			enemy->SetTarget(nullptr);
		}

		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::red, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::orange, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::yellow, 1, 100, 200);
		g_particleSystem.Create(m_transform.position, 0, 180, 90, nc::Color::white, 1, 100, 200);
		g_audioSystem.PlayAudio("Explosion");
	}
}
