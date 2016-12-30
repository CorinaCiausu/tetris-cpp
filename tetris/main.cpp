#include <SDL.h>
#include "Game.h"
#include <iostream>

int main(int argc, char* args[])
{
	std::cout << "ayy";
	const int x = 800, y = 600;
	Game game = Game(x, y);
	
	game.init(); // initialize game - load data, open window
	game.run(); // start updating and rendering
	
	
	return 0;
}