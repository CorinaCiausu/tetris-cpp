#include "Screen.h"
#include <cstdio>
#include <SDL_image.h>
Screen::Screen(int width, int height)
{
	this -> width = width;
	this -> height = height;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		suprafata = IMG_Load("ayy.bmp");
		textura = SDL_CreateTextureFromSurface(renderer, suprafata);
	}
	
	dreptunghi.x = 20;
	dreptunghi.y=50; 
	dreptunghi.w = 360;
	dreptunghi.h = 280;
}


void Screen::update()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textura, NULL, &dreptunghi);
	SDL_RenderPresent(renderer);
	SDL_PollEvent(quitEvent);
}

void Screen::close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Screen::~Screen()
{
}
