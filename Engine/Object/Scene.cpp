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
	this->m_actors.push_back(actor);
}

void nc::Scene::RemoveActor(Actor * actor)
{
	std::list<Actor*>::iterator iter = std::find(this->m_actors.begin(), this->m_actors.end(), actor);
	if (iter != this->m_actors.end())
	{
		delete* iter;
		this->m_actors.erase(iter);
	}
}
