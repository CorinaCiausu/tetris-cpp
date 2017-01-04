#include "Button.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Screen.h"
#include <iostream>
#include "Game.h"
#include <string>

Button::Button(Screen *screen, int x, int y, int w, int h)
{
	TTF_Init();

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->screen = screen;


	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	textRect.x = x + 20;
	textRect.y = y + 10;
	textRect.w = w - 40;
	textRect.h = h - 20;

	font = TTF_OpenFont("fonts/gnuolane.ttf", 100);
	std::cout << SDL_GetError() << "!";

	message = TTF_RenderText_Blended(font, name.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), message);
}

Button::Button(Screen *screen, int x, int y, int w, int h, const char* textureName) : Button(screen, x, y, w, h)
{
	surface = IMG_Load(textureName);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
}

Button::Button(Screen* screen)
{
	x = 0;
	y = 0;
}

Button::Button()
{
}

void Button::setName(const char* name)
{
	this->name = name;
	message = TTF_RenderText_Blended(font, this->name.c_str(), textColor);
	messageTexture = SDL_CreateTextureFromSurface(screen->getRenderer(), message);
}

void Button::update()
{
	SDL_Event *gameMainEvent = &Game::getMainEvent();
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > x && mouseX < x + w)
	{
		if (mouseY > y && mouseY < y + h)
		{
			if (!focused)
				handleFocus();
			if (gameMainEvent->type == SDL_MOUSEBUTTONDOWN)
			{
				if (gameMainEvent->button.button == SDL_BUTTON_LEFT)
				{
					handleClick();
				}
			}
		}
		else
		{
			if (focused)
				handleFocusExit();
		}
	}
	else 
	{
		if (focused)
			handleFocusExit();
	}
}

void Button::handleFocus()
{
	focused = true;
	textColor = { 255, 10, 20 };
	message = TTF_RenderText_Blended(font, this->name.c_str(), textColor);
	messageTexture = SDL_CreateTextureFromSurface(screen->getRenderer(), message);
}
void Button::handleFocusExit()
{
	focused = false;
	textColor = { 255, 255, 255 };
	message = TTF_RenderText_Blended(font, this->name.c_str(), textColor);
	messageTexture = SDL_CreateTextureFromSurface(screen->getRenderer(), message);
}

void Button::handleClick()
{
	if(name.compare("Quit game")==0)
	{
		Game::quit();
	}
	else
		if (name.compare("Start game") == 0)
		{
			Game::changeScene("Game");
		}
		else
			if(name.compare("High scores")==0)
			{
				Game::changeScene("Scores");
			}
}
void Button::render(Screen* screen)
{
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, &rect);
	SDL_RenderCopy(screen->getRenderer(), messageTexture, NULL, &textRect);
}
Button::~Button()
{
}
