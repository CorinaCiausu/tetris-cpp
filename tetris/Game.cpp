#include "Game.h"
#include <SDL.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Scene.h"
#include <SDL_ttf.h>

SDL_Event Game::mainEvent;
bool Game::running = false;
Scene *Game::currentScene = NULL;
Scene Game::gameScene;
Scene Game::menuScene;
Scene Game::scoresScene;

Game::Game(int width, int height) : screen(width, height)
{
	this->width = width;
	this->height = height;
	this->running = false;
	menuScene = Scene("Menu");
	gameScene = Scene("Game");
	scoresScene = Scene("Scores");
	currentScene = &menuScene;
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
}

void Game::initGame()
{
	gameScene.setBackground(new Background(&screen, "textures/joc.png"));
}

void Game::initScores()
{
	scoresScene.setBackground(new Background(&screen, "textures/highscores.png"));
}

void Game::initMenu()
{
	Button *b1 = new Button(&screen, screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2, 270, 70, "textures/butonel.png");
	menuScene.addButton(b1);
	b1->setName("Start game");

	Button *b2 = new Button(&screen, screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 100, 270, 70, "textures/butonel.png");
	menuScene.addButton(b2);
	b2->setName("High scores");

	Button *b3 = new Button(&screen, screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 200, 270, 70, "textures/butonel.png");
	menuScene.addButton(b3);
	b3->setName("Sound settings");

	Button *b4 = new Button(&screen, screen.getWidth() / 2 - 270 / 2 - 30, screen.getHeight() / 2 - 70 / 2 + 300, 270, 70, "textures/butonel.png");
	menuScene.addButton(b4);
	b4->setName(" Quit game");

	menuScene.setBackground(new Background(&screen, "textures/meniu.png"));
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
}

void Game::render(Screen screen)
{
	screen.render(currentScene);
}