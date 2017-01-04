#pragma once
#include <SDL.h>
#include "Button.h"

class Scene;

class Screen
{
public:
	Screen(int, int);
	~Screen();
	void close();
	void update();
	void render(Scene *scene);
	SDL_Renderer* getRenderer();
	int getWidth();
	int getHeight();

private:
	int width;
	int height;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

};

