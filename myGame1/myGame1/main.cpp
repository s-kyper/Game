/////////////////////////////////////
// Include
#include "game.h"

/////////////////////////////////////
// Pragma
#ifndef _DEBUG
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/////////////////////////////////////
// Entry point
int main()
{
	Game* game = new Game();

	game->setupSystem();
	game->initialize();

	while(game->frame());

	game->shutdown();

	delete game;

	return 0;
}