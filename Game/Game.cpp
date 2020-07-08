// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2D.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"

const size_t NUM_POINTS = 40;
float speed = 300.0;

//std::vector<nc::Vector2D> points = { {0, 0}, {0, -3}, {1, -4}, {2, -3}, {3, -6}, {4, -3}, {5, -4}, {6, -3}, {6, 0}, {5, -2}, {3, -1}, {1, -2}, {0, 0} };
//nc::Color color = { 0.75f, 0.0f, 0.0f };
//nc::Shape ship(points, color);
nc::Shape ship;

nc::Vector2D position{ 400, 300 };
float scale = 4.0f;
float angle = 0.0f;

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

	frameTime = dt;
	roundTime += dt;
	//if (roundTime >= 5) { gameOver = true; }

	//dt = dt * 0.25f;
	if (gameOver) { dt = 0; }

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	nc::Vector2D force{0,0};
	if (Core::Input::IsPressed('W')) { force = nc::Vector2D::up * speed * dt; }
	nc::Vector2D direction = force;
	direction = nc::Vector2D::Rotate(direction, angle);
	position = position + direction;
	
	//rotate
	if (Core::Input::IsPressed('A')) { angle = angle - (dt * 3.0f); }
	if (Core::Input::IsPressed('D')) { angle = angle + (dt * 3.0f); }

	//translate
	//if (Core::Input::IsPressed('A')) { position += nc::Vector2D::left * speed * dt; }
	//if (Core::Input::IsPressed('D')) { position += nc::Vector2D::right * speed * dt; }

	int x, y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2D target = nc::Vector2D{ x,y };
	//nc::Vector2D direction = target - position; // (head <- tail)

	//position = position + direction.Normalized() * 5.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000).c_str());

	if (gameOver) { graphics.DrawString(400, 300, "Game Over"); }

	ship.Draw(graphics, position, scale, angle);
}

int main()
{
	//DWORD ticks = GetTickCount(); // how many ticks in a second
	//std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	ship.Load("ship.txt");

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
