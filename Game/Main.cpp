#include "core.h"
#include "Game.h"
#include <time.h>

Game game;

bool Update(float dt)
{
	return game.Update(dt);
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	game.Startup();
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
	game.Shutdown();
}
