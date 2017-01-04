#include <SDL.h>
#include "Game.h"
#include <iostream>

int main(int argc, char* args[])
{
	const int x = 1280, y = 720;
	Game game = Game(x, y);
	
	game.init(); // initialize game - load data, open window
	game.run(); // start updating and rendering
	
	
	return 0;
}