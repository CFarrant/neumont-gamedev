#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

nc::ParticleSystem g_particleSystem;

void nc::ParticleSystem::Startup()
{
	m_particles = new Particle[5000];
	m_size = 5000;
}

void nc::ParticleSystem::Shutdown()
{
	delete[] m_particles;
}

void nc::ParticleSystem::Update(float dt)
{
	for (size_t i = 0; i < m_size; i++) 
	{
		Particle* p = &m_particles[i];
		if (p->active)
		{
			p->lifetime -= dt;
			p->active = (p->lifetime > 0);
			p->prevPosition = p->position;
			p->position = p->position + (p->velocity * dt);
			p->velocity = p->velocity * p->damping;
		}
	}
}

void nc::ParticleSystem::Draw(Core::Graphics & graphics)
{
	for (size_t i = 0; i < m_size; i++)
	{
		Particle* p = &m_particles[i];
		if (p->active)
		{
			graphics.SetColor(p->color);
			graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
		}
	}
}

//void nc::ParticleSystem::Create(const Vector2D & position, float angle, float angleRange, size_t count, const Color[] colors, float lifetime, float speedMin, float speedMax)
//{
//	for (size_t i = 0; i < count; i++) {
//		Particle* p = GetFreeParticle();
//		if (p)
//		{
//			p->active = true;
//			p->lifetime = lifetime;
//			p->position = position;
//			p->prevPosition = position;
//
//			nc::Color color = colors[rand() % 4];
//
//			p->color = color;
//
//			float angleRandom = nc::DegreesToRadians(nc::Random(-angleRange, angleRange));
//			Vector2D direction = Vector2D::Rotate(Vector2D::down, angle + angleRandom);
//			p->velocity = direction * nc::Random(speedMin, speedMax);
//		}
//	}
//}

void nc::ParticleSystem::Create(const Vector2D & position, float angle, float angleRange, size_t count, const Color color, float lifetime, float speedMin, float speedMax)
{
	for (size_t i = 0; i < count; i++) {
		Particle* p = GetFreeParticle();
		if (p)
		{
			p->active = true;
			p->lifetime = lifetime;
			p->position = position;
			p->prevPosition = position;
			p->color = color;

			float angleRandom = nc::DegreesToRadians(nc::Random(-angleRange, angleRange));
			Vector2D direction = Vector2D::Rotate(Vector2D::down, angle + angleRandom);
			p->velocity = direction * nc::Random(speedMin, speedMax);
		}
	}
}

nc::Particle* nc::ParticleSystem::GetFreeParticle()
{
	Particle* freeParticle{ nullptr };

	for (size_t i = 0; i < m_size; i++)
	{
		Particle* p = &m_particles[i];
		if (!p->active)
		{
			freeParticle = p;
			break;
		}
	}

	return freeParticle;
}
