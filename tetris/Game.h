#pragma once
#include "Screen.h"

class Game
{
public:
	Game(int, int);
	~Game();
	void run();
	void init();

private:
	int x, y;
	bool running;
	Screen screen;
	void update();
	void render();
	void exit();
};

