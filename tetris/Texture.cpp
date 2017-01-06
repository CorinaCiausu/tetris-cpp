#include "Texture.h"
#include <SDL_image.h>
#include "Game.h"
#include <iostream>

Texture *Texture::L_Texture;
Texture *Texture::T_Texture;
Texture *Texture::S_Texture;
Texture *Texture::Z_Texture;
Texture *Texture::I_Texture;
Texture *Texture::J_Texture;
Texture *Texture::O_Texture;
Texture *Texture::basicButtonTexture;
Screen *Texture::screen;
Texture *Texture::emptyCell;

Texture::Texture(const char*textureName)
{
	screen = Game::getScreen();
	surface = IMG_Load(textureName);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
	cout << IMG_GetError() << textureName << '\n';
}

void Texture::init()
{
	L_Texture = new Texture("textures/piese/L-simplu.png");
	T_Texture = new Texture("textures/piese/T-simplu.png");
	S_Texture = new Texture("textures/piese/S-simplu.png");
	Z_Texture = new Texture("textures/piese/Z-simplu.png");
	I_Texture = new Texture("textures/piese/I-simplu.png");
	J_Texture = new Texture("textures/piese/J-simplu.png");
	O_Texture = new Texture("textures/piese/O-simplu.png");
	emptyCell = new Texture("textures/boardCell.png");
	basicButtonTexture = new Texture("textures/butonel.png");
}

void Texture::render(Screen *screen, SDL_Rect *rect)
{
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, rect);
}

Texture::Texture()
{
}


Texture::~Texture()
{
}
