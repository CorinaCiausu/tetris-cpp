#pragma once
#include <SDL.h>
#include "Entity.h"
#include <SDL_ttf.h>
#include <string>
#include "Screen.h"

class Screen;
using namespace std;
class Button: public Entity
{
public:
	Button(Screen *screen, int x, int y, int w, int h);
	Button(Screen *screen, int x, int y, int w, int h, const char* textureName);
	Button(Screen*);
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
	SDL_Rect rect;
	SDL_Rect textRect;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font *font = NULL;
	SDL_Surface *message = NULL;
	string name = " ";
	Screen *screen;
	SDL_Texture *messageTexture = NULL;
	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
};

