#pragma once
#include "Entity.h"
#include "Screen.h"

class ScoresBoard : public Entity
{
public:
	ScoresBoard();
	~ScoresBoard();
	void update();
	void render(Screen *screen);

private:
	int scores[100];
	TTF_Font *font;
	SDL_Texture *score1Texture = NULL;
	SDL_Texture *score2Texture = NULL;
	SDL_Texture *score3Texture = NULL;
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect rect3;
	SDL_Surface *message = NULL;
	string score = "0";
	SDL_Color textColor = { 255, 255, 255 };
};

