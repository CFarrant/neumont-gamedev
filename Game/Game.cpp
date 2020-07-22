// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "core.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Object/Scene.h"
#include <string>
#include <list>

nc::Scene scene;
float frameTime;
float spawnTimer{ 0 };

bool Update(float dt)
{
	frameTime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	spawnTimer += dt;
	if (spawnTimer >= 3)
	{
		spawnTimer = 0.0f;
		nc::Actor* enemy = new Enemy();
		enemy->Load("enemy.actor");
		dynamic_cast<Enemy*>(enemy)->SetTarget(scene.GetActor<Player>());
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
		enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
		scene.AddActor(enemy);
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow, nc::Color::orange };
		nc::Color color = colors[rand() % 4];

		g_particleSystem.Create(nc::Vector2D{x, y}, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{1,1,1});
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	scene.Startup();
	g_particleSystem.Startup();

	nc::Actor* player = new Player();
	player->Load("player.actor");
	scene.AddActor(player);
	
	for (int i = 0; i < 5; i++)
	{
		nc::Actor* enemy = new Enemy();
		enemy->Load("enemy.actor");
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
		enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
		scene.AddActor(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	g_particleSystem.Shutdown();
}
