// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2D.h"
#include "Math/Color.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0;
std::vector<nc::Vector2D> points = { {0,-3}, {3,3}, {0,1}, {-3,3}, {0,-3} };
nc::Color color{ 0,1,1 };

nc::Vector2D position{ 400, 300 };
float scale = 4.0f;
float angle = 0.0f;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { angle = angle - dt * 3.0f; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { angle = angle + dt * 3.0f; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { position += nc::Vector2D{ 0.0f, 1.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { position += nc::Vector2D{ 0.0f, -1.0f } * speed; }

	int x, y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2D target = nc::Vector2D{ x,y };
	nc::Vector2D direction = target - position; // (head <- tail)

	//position = position + direction.Normalized() * 5.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	// rgb (8-bits/1-byte, 8, 8) (0-255, 0-255, 0-255)
	// 0-1.0 Range
	// rgb
	graphics.SetColor(color);
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		// local / object space points
		nc::Vector2D p1 = points[i];
		nc::Vector2D p2 = points[i + 1];

		// transform
		// scale
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotation
		p1 = nc::Vector2D::Rotate(p1, angle);
		p2 = nc::Vector2D::Rotate(p2, angle);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
