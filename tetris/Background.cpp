#include "Background.h"
#include "Screen.h"
#include <SDL_image.h>
#include <iostream>
Background::Background(Screen *screen, const char* textureName)
{
	x = 0;
	y = 0;
	w = screen->getWidth();
	h = screen->getHeight();
	surface = IMG_Load(textureName);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
Background::Background()
{
}

void Background::render(Screen *screen)
{
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, &rect);
}

void Background::update()
{

}

Background::~Background()
{
}
