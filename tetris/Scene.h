#pragma once
#include <list>
#include "Entity.h"
#include "Button.h"
#include "Background.h"
#include "Board.h"

class Screen;
using namespace std;

class Scene
{
public:
	Scene(const char* name);
	Scene();
	~Scene();
	void update();
	void render(Screen *screen);
	void addButton(Button *button);
	void setBackground(Background *background);
	void addBoard(Board *board);

private:
	list<Button*> buttons;
	Background *background;
	Board *board = NULL;
	string name;
};

