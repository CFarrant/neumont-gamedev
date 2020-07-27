#pragma once
#include "Object/Actor.h"

class Locator : public nc::Actor
{
public:
	Locator() {}
	virtual ~Locator() {}

	virtual eType GetType() { return eType::LOCATOR; }

	virtual void Update(float dt) override;
};