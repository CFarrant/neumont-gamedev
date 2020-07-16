// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "core.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <string>
#include <list>

std::list<nc::Actor*> actors;
float frameTime;
float spawnTimer{ 0 };

template <typename T>
nc::Actor* GetActor()
{
	nc::Actor* result{ nullptr };

	for (nc::Actor* actor : actors)
	{
		result = dynamic_cast<T*>(actor);
		if (result) { break; }
	}

	return result;
}

template <typename T>
std::vector<nc::Actor*> GetActors()
{
	std::vector<nc::Actor*> results;

	for (nc::Actor* actor : actors)
	{
		T* result = dynamic_cast<T*>(actor);
		if (result) { results.push_back(result); }
	}

	return results;
}

bool Update(float dt)
{
	frameTime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto removeActors = GetActors<Enemy>();
		for (auto actor : removeActors)
		{
			auto iter = std::find(actors.begin(), actors.end(), actor);
			delete* iter;
			actors.erase(iter);
		}
	}

	spawnTimer += dt;
	if (spawnTimer >= 3) 
	{
		spawnTimer = 0.0f;
		nc::Actor* enemy = new Enemy();
		enemy->Load("enemy.actor");
		dynamic_cast<Enemy*>(enemy)->SetTarget(GetActor<Player>());
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
		enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
		actors.push_back(enemy);
	}

	for(nc::Actor* actor : actors)
	{
		actor->Update(dt);
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{1,1,1});
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());

	for (nc::Actor* actor : actors)
	{
		actor->Draw(graphics);
	}
}

int main()
{
	nc::Actor* player = new Player();
	player->Load("player.actor");
	actors.push_back(player);
	
	for (int i = 0; i < 5; i++)
	{
		nc::Actor* enemy = new Enemy();
		enemy->Load("enemy.actor");
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
		enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
		actors.push_back(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
