#include "Game.h"
#include <SDL.h>
#include <chrono>
#include <ctime>
#include <iostream>

Game::Game(int x, int y)
{
	this->x = x;
	this->y = y;
	this->screen = Screen(x, y);
	this->running = false;
}


void Game::run()
{
	using namespace std::chrono;
	// starts the game
	long long timer = SDL_GetTicks(); // number of milliseconds since the SDL library initialization
	high_resolution_clock::time_point lastTime = high_resolution_clock::now();
	double ns = 1000000000.0 / 60.0;

	double delta = 0;
	int frames = 0;
	int updates = 0;

	while (this->running)
	{
		high_resolution_clock::time_point now = high_resolution_clock::now();
		delta += (now.time_since_epoch().count() - lastTime.time_since_epoch().count())/ns;
		lastTime = now;

		while (delta >= 1)
		{
			update();
			updates++;
			delta--;
		}

		render();
		frames++;

		if (SDL_GetTicks() - timer > 1000)
		{
			timer += 1000;
			std::cout << updates << "ups, " << frames << "fps" << '\n';
			updates = 0;
			frames = 0;
		}
	}

}

void Game::init()
{
	this->running = true;
}

void Game::update()
{
	screen.update();
}

Game::~Game()
{

}

void Game::render()
{

}