#pragma once
#include <SDL.h>
#include "Screen.h"

class Texture
{
public:
	Texture(int x, int y, int w, int h, const char* textureName);
	Texture(const char* textureName);
	Texture();
	~Texture();
	static Texture *L_Texture;
	static Texture *T_Texture;
	static Texture *I_Texture;
	static Texture *O_Texture;
	static Texture *S_Texture;
	static Texture *Z_Texture;
	static Texture *J_Texture;
	static Texture *emptyCell;
	static Texture *basicButtonTexture;
	void render(Screen *screen, SDL_Rect *rect);
	static void init();
private:
	static Screen *screen;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
};

