#include "Button.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Screen.h"
#include "Texture.h"
#include <iostream>
#include "Game.h"
#include <string>

Button::Button(int x, int y, int w, int h)
{
	TTF_Init();
	this->screen = Game::getScreen();
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

	font = TTF_OpenFont("./fonts/gnuolane.ttf", 100);
	message = TTF_RenderText_Blended(font, name.c_str(), textColor);
	texture = Texture::basicButtonTexture;
	messageTexture = SDL_CreateTextureFromSurface(screen->getRenderer(), message);
}

Button::Button(int x, int y, int w, int h, Texture *texture) : Button(x, y, w, h)
{
	this->texture = texture;
}

Button::Button()
{
	x = 0;
	y = 0;
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
	cout << name << " ";
	if (name.compare("Quit game") == 0)
	{
		Game::quit();
	}
	else
		if (name.compare("Start game") == 0)
		{
			Game::changeScene("Game");
		}
		else
			if (name.compare("High scores") == 0)
			{
				Game::changeScene("Scores");
			}
			else
				if (name.compare("Back") == 0)
					Game::changeScene("Menu");
				else
					if (name.compare("Sound settings") == 0)
						Game::changeScene("Sound");
					else
						if (name.compare("Turn off") == 0)
							Game::pauseMusic();
						else
							if (name.compare("Turn on") == 0)
								Game::playMusic();

}
void Button::render(Screen* screen)
{
	texture->render(this->screen, &rect);
	SDL_RenderCopy(screen->getRenderer(), messageTexture, NULL, &textRect);
}
Button::~Button()
{
}
