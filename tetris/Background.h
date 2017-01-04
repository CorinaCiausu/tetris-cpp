#pragma once
#include "Entity.h"
#include <SDL.h>

class Screen;

class Background: public Entity
{
public:
	Background(Screen *screen, const char* textureName);
	Background();
	~Background();
	void update();
	void render(Screen *screen);

private:
	int x, y, w, h;
	SDL_Rect rect;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

};

