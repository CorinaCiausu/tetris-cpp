#pragma once
#include <SDL.h>
class Screen
{
public:
	Screen(int, int);
	~Screen();
	void close();
	void update();
	SDL_Event* quitEvent = new SDL_Event();

private:
	int width;
	int height;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Surface* suprafata = NULL;
	SDL_Texture* textura = NULL; 
	SDL_Rect dreptunghi;
	

	//The renderer
	SDL_Renderer* renderer = NULL;

};

