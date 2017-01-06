#pragma once
#include "Entity.h"
#include "Screen.h"
#include "Texture.h"
#include <vector>

class BoardCell : public Entity
{
public:
	BoardCell(int x, int y, int w, Texture *texture);
	bool isActive;
	BoardCell();
	~BoardCell();
	void update();
	void render(Screen *screen);
	void setTexture(Texture *texture);

private:
	int x, y, w, h;
	Screen *screen;
	SDL_Rect rect;
	Texture *texture;
};

