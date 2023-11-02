#include <zpch.h>
#include "Game.h"
#include <Zewada.h>

// game build:
// remove entityID in engine

//pointers are bad
//never nest

int main()
{
	ApplicationSpecs settings;
	settings.name = "Game";
    settings.resizeable = false;
	Game::Game app = Game::Game(settings);
	app.Run();
	return 0;
}