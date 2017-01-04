#include "Screen.h"
#include <cstdio>
#include <SDL_image.h>
#include<iostream>
#include"Button.h"
#include"Scene.h"
#include"Game.h"

Screen::Screen(int width, int height)
{
	this -> width = width;
	this -> height = height;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		}
	}
}

int Screen::getWidth()
{
	return width;
}

SDL_Renderer *Screen::getRenderer()
{
	return this->renderer;
}

int Screen::getHeight()
{
	return height;
}

void Screen::update()
{

}

void Screen::render(Scene *scene)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	scene->render(this);
	SDL_RenderPresent(renderer);
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
