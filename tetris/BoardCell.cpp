#include "BoardCell.h"
#include "Game.h"
#include "Texture.h"
#include<SDL_image.h>

BoardCell::BoardCell(int x, int y, int w, Texture *texture)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = w;
	this->isActive = true;
	screen = Game::getScreen();
	this->texture = texture;
	rect.x = this->x;
	rect.y = this->y;
	rect.w = this->w;
	rect.h = this->w;
}

void BoardCell::update()
{

}

void BoardCell::setTexture(Texture *texture)
{
	this->texture = texture;
}

void BoardCell::render(Screen *screen)
{
	if (isActive)
		texture->render(screen, &rect);
}

BoardCell::BoardCell()
{
}


BoardCell::~BoardCell()
{
}
