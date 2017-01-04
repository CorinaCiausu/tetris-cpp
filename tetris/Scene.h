#pragma once
#include <list>
#include "Entity.h"
#include "Button.h"
#include "Background.h"

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

private:
	list<Button*> buttons;
	Background *background;
	string name;
};

