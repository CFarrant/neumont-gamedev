#include "pch.h"
#include "Scene.h"
#include "Actor.h"

void nc::Scene::Startup()
{
	//nothing
}

void nc::Scene::Shutdown()
{
	std::vector<Actor*> removeActors = GetActors<Actor>();
	for (auto actor : removeActors)
	{
		auto iter = std::find(this->m_actors.begin(), this->m_actors.end(), actor);
		delete* iter;
		this->m_actors.erase(iter);
	}
	this->m_actors.clear();
}

void nc::Scene::Update(float dt)
{
	std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
	for (size_t i = 0; i < actors.size(); i++)
	{
		for (size_t j = i + 1; j < actors.size(); j++)
		{
			float distance = Vector2D::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
			if (distance <= 10)
			{
				actors[i]->OnCollision(actors[j]);
				actors[j]->OnCollision(actors[i]);
			}
		}
	}

	auto iter = m_actors.begin();
	while (iter != m_actors.end())
	{
		if ((*iter)->IsDestroyed()) 
		{
			delete* iter;
			iter = m_actors.erase(iter);
		}
		else { iter++; }
	}

	for (nc::Actor* actor : this->m_actors)
	{
		actor->Update(dt);
	}
}

void nc::Scene::Draw(Core::Graphics & graphics)
{
	for (nc::Actor* actor : this->m_actors)
	{
		actor->Draw(graphics);
	}
}

void nc::Scene::AddActor(Actor * actor)
{
	actor->SetScene(this);
	this->m_actors.push_back(actor);
}

void nc::Scene::RemoveActor(Actor * actor)
{
	auto iter = std::find(this->m_actors.begin(), this->m_actors.end(), actor);
	if (iter != this->m_actors.end())
	{
		delete* iter;
		this->m_actors.erase(iter);
	}
}
