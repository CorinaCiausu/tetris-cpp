#pragma once
#include <SDL.h>
#include "Entity.h"
#include <SDL_ttf.h>
#include <string>

class Screen;
class Texture;

using namespace std;
class Button: public Entity
{
public:
	Button(int x, int y, int w, int h);
	Button(int x, int y, int w, int h, Texture *texture);
	Button();
	void render(Screen* screen);
	void update();
	void setName(const char* name);
	~Button();

private:
	int x, y, w, h;
	void handleClick();
	bool focused = false;
	void handleFocus();
	void handleFocusExit();
	Screen *screen;
	SDL_Rect rect;
	SDL_Rect textRect;
	Texture *texture;
	TTF_Font *font = NULL;
	SDL_Surface *message = NULL;
	string name = " ";
	SDL_Texture *messageTexture = NULL;
	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
};

