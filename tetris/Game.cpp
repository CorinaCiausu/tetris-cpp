#include "Game.h"
#include <SDL.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Scene.h"
#include <SDL_ttf.h>
#include "Texture.h"

SDL_Event Game::mainEvent;
bool Game::running = false;
Scene *Game::currentScene = NULL;
Scene Game::gameScene;
Scene Game::menuScene;
Scene Game::scoresScene;
Screen Game::screen;
Scene Game::soundScene;

Game::Game(int x, int y)
{
	this->screen = Screen(x, y);
	Texture::init();
	this->width = x;
	this->height = y;
	this->running = false;
	menuScene = Scene("Menu");
	gameScene = Scene("Game");
	scoresScene = Scene("Scores");
	soundScene = Scene("Sound");
	currentScene = &menuScene;
}

Screen* Game::getScreen()
{
	return &screen;
}

void Game::run()
{
	using namespace std::chrono;
	// starts the game
	long long timer = SDL_GetTicks(); // number of milliseconds since the SDL library initialization
	high_resolution_clock::time_point lastTime = high_resolution_clock::now();
	double ns = 1000000000.0 / 60.0;

	double delta = 0;
	int frames = 0;
	int updates = 0;

	while (this->running && mainEvent.type != SDL_QUIT)
	{
		high_resolution_clock::time_point now = high_resolution_clock::now();
		delta += (now.time_since_epoch().count() - lastTime.time_since_epoch().count())/ns;
		lastTime = now;
		SDL_PollEvent(&mainEvent);

		while (delta >= 1)
		{
			update();
			updates++;
			delta--;
		}

		render(screen);
		frames++;

		if (SDL_GetTicks() - timer > 1000)
		{
			timer += 1000;
			std::cout << updates << "ups, " << frames << "fps" << '\n';
			updates = 0;
			frames = 0;
		}
	}

}

void Game::init()
{
	this->running = true;
	initMenu();
	initGame();
	initScores();
	initSound();
}

void Game::initGame()
{
	gameScene.setBackground(new Background("textures/joc.png"));
	gameScene.addBoard(new Board(300, 50, 10, 13, 50));
	Button *back = new Button(970, 615, 200, 70, Texture::basicButtonTexture);
	gameScene.addButton(back);
	back->setName("Back");
}

void Game::initScores()
{
	scoresScene.setBackground(new Background("textures/highscores.png"));
	Button *back = new Button(980, 535, 200, 70, Texture::basicButtonTexture);
	scoresScene.addButton(back);
	back->setName("Back");
}

void Game::initSound()
{
	soundScene.setBackground(new Background("textures/sound.png"));
	Button *back = new Button(40, 50, 200, 70, Texture::basicButtonTexture);
	soundScene.addButton(back);
	back->setName("Back");
	Button *off = new Button(150, 580, 200, 70, Texture::basicButtonTexture);
	soundScene.addButton(off);
	off->setName("Turn off");
	Button *on = new Button(830, 580, 200, 70, Texture::basicButtonTexture);
	soundScene.addButton(on);
	on->setName("Turn on");
}
void Game::initMenu()
{
	Button *b1 = new Button(screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2, 270, 70, Texture::basicButtonTexture);
	menuScene.addButton(b1);
	b1->setName("Start game");

	Button *b2 = new Button(screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 100, 270, 70, Texture::basicButtonTexture);
	menuScene.addButton(b2);
	b2->setName("High scores");

	Button *b3 = new Button(screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 200, 270, 70, Texture::basicButtonTexture);
	menuScene.addButton(b3);
	b3->setName("Sound settings");

	Button *b4 = new Button(screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 300, 270, 70, Texture::basicButtonTexture);
	menuScene.addButton(b4);
	b4->setName("Quit game");

	menuScene.setBackground(new Background("textures/meniu.png"));
}

SDL_Event Game::getMainEvent()
{
	return mainEvent;
}

void Game::update()
{
	currentScene->update();
	screen.update();
}

Game::~Game()
{

}

void Game::quit()
{
	running = false;
}

void Game::changeScene(string sceneName)
{
	if (sceneName.compare("Game") == 0)
		currentScene = &gameScene;
	else
		if (sceneName.compare("Scores") == 0)
			currentScene = &scoresScene;
		else
			if (sceneName.compare("Menu") == 0)
				currentScene = &menuScene;
			else
				if (sceneName.compare("Sound") == 0)
					currentScene = &soundScene;
}

void Game::render(Screen screen)
{
	screen.render(currentScene);
}