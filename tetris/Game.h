#pragma once
#include "Screen.h"
#include "Scene.h"
#include <string>

class Game
{
public:
	Game(int, int);
	~Game();
	void run();
	void init();
	static SDL_Event getMainEvent();
	static void quit();
	static void changeScene(string sceneName);

private:
	int width, height;
	static bool running;
	Screen screen;
	static Scene *currentScene;
	static Scene menuScene, scoresScene, gameScene;
	static SDL_Event mainEvent;
	void update();
	void render(Screen);
	void initMenu();
	void initScores();
	void initGame();
	void exit();
};

