#include "ScoresBoard.h"
#include <fstream>
#include <SDL_ttf.h>
#include "Game.h"
#include <iostream>

using namespace std;
ScoresBoard::ScoresBoard()
{
	TTF_Init();

	int k = 0;
	ifstream fin("scores.txt");
	while (!fin.eof())
		fin >> scores[k++];
	bool ok;
	do
	{
		ok = 1;
		for (int i = 0; i < k - 1; i++)
			if (scores[i] < scores[i + 1])
			{
				swap(scores[i], scores[i + 1]);
				ok = 0;
			}
	} while (!ok);

	int scoreHeight = 70;

	rect1.x = 450;
	rect1.y = 150;
	rect1.h = scoreHeight;
	rect1.w = 180;

	rect2.x = 450;
	rect2.y = rect1.y + scoreHeight + 30;
	rect2.w = 180;
	rect2.h = scoreHeight;

	rect3.x = 450;
	rect3.y = rect2.y + scoreHeight + 30;
	rect3.w = 180;
	rect3.h = scoreHeight;

	font = TTF_OpenFont("fonts/gnuolane.ttf", 100);
	score = "1. " + to_string(scores[0]);
	message = TTF_RenderText_Blended(font, score.c_str(), textColor);
	score1Texture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), message);
	score = "2. " + to_string(scores[1]);
	message = TTF_RenderText_Blended(font, score.c_str(), textColor);
	score2Texture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), message);
	score = "3. " + to_string(scores[2]);
	message = TTF_RenderText_Blended(font, score.c_str(), textColor);
	score3Texture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), message);
}


ScoresBoard::~ScoresBoard()
{
}

void ScoresBoard::update()
{

}

void ScoresBoard::render(Screen *screen)
{
	SDL_RenderCopy(screen->getRenderer(), score1Texture, NULL, &rect1);
	SDL_RenderCopy(screen->getRenderer(), score2Texture, NULL, &rect2);
	SDL_RenderCopy(screen->getRenderer(), score3Texture, NULL, &rect3);
}