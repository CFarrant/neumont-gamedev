#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player() {}
	virtual ~Player() {}

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

protected:
	float m_thrust;
	float m_rotationRate;
	nc::Vector2D m_velocity;
};