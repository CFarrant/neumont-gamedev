// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2D.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0;
std::vector<nc::Vector2D> points;
nc::Vector2D position{ 400, 300 };

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { position += nc::Vector2D{ -1.0f, 0.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { position += nc::Vector2D{ 1.0f, 0.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { position += nc::Vector2D{ 0.0f, 1.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { position += nc::Vector2D{ 0.0f, -1.0f } * speed; }

	int x, y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2D target = nc::Vector2D{ x,y };
	nc::Vector2D direction = target - position; // (head <- tail)

	position = position + direction.Normalized() * 5.0f;

	for (nc::Vector2D& point : points) {
		point = nc::Vector2D{ nc::Random(-10.0f, 10.0f), nc::Random(-10.0f, 10.0f) };
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < NUM_POINTS - 1; i++)
	{
		nc::Vector2D p1 = position + points[i];
		nc::Vector2D p2 = position + points[i + 1];
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points.push_back(nc::Vector2D{ nc::Random(0.0f, 800.0f), nc::Random(0.0f, 600.0f) });
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
