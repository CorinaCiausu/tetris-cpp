#pragma once
#include <SDL.h>
class Screen
{
public:
	Screen(int, int);
	Screen();
	~Screen();
	bool init();
	bool loadMedia();
	void close();
	void update();

private:
	int x;
	int y;
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = NULL;
};

