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

float thrust = 300.0;
nc::Vector2D velocity;

Player player;
Enemy enemy;

float t{ 0 };

float frameTime;
float roundTime;
using timer_t = DWORD;
timer_t prevTime, deltaTime;
bool gameOver{ false };

bool Update(float dt) // delta time (60 fps) (1 / 60 = 0.016)
{
	// dt = current frame time - previous frame time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	t = t + (dt * 5.0f);

	frameTime = dt;
	//roundTime += dt;
	//if (roundTime >= 5) { gameOver = true; }
	//dt = dt * 0.25f;
	//if (gameOver) { dt = 0; }

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	player.Update(dt);
	enemy.Update(dt);

	//translate
	//if (Core::Input::IsPressed('A')) { position += nc::Vector2D::left * thrust * dt; }
	//if (Core::Input::IsPressed('D')) { position += nc::Vector2D::right * thrust * dt; }

	//nc::Vector2D target = nc::Vector2D{ x,y };
	//nc::Vector2D direction = target - position; // (head <- tail)

	//position = position + direction.Normalized() * 5.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{1,1,1});
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000).c_str());

	//float v = (std::sin(t) + 1.0f) * 0.5f;
	//nc::Vector2D p = nc::Lerp(nc::Vector2D{ 400,300 }, nc::Vector2D{ 400,100 }, v);
	//nc::Color c = nc::Lerp(nc::Color{ 0,0,1 }, nc::Color{ 1,0,0 }, v);
	//graphics.SetColor(c);
	//graphics.DrawString(p.x, p.y, "The Last Starfighter!");

	//if (gameOver) { graphics.DrawString(400, 300, "Game Over"); }

	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	//DWORD ticks = GetTickCount(); // how many ticks in a second
	//std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	player.Load("player.actor");
	enemy.Load("enemy.actor");
	enemy.SetTarget(&player);

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
