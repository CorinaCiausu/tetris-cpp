#pragma once
#include "Screen.h"
#include "Scene.h"
#include <string>
#include <SDL_mixer.h>

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
	static Screen *getScreen();
	static void playMusic();
	static void pauseMusic();

private:
	int width, height;
	static bool running;
	static Screen screen;
	static Scene *currentScene;
	static Scene menuScene, scoresScene, gameScene, soundScene;
	static SDL_Event mainEvent;
	static Mix_Music *music;
	void update();
	void render(Screen);
	void initMenu();
	static void initScores();
	static void initGame();
	void initSound();
	void exit();
};

