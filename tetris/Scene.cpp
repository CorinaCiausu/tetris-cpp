#include "Scene.h"



Scene::Scene(const char* name)
{
	this->name = name;
}

Scene::Scene()
{

}

void Scene::addButton(Button *button)
{
	buttons.push_back(button);
}

void Scene::setBackground(Background *background)
{
	this->background = background;
}

void Scene::update()
{
	for (Button *button : buttons)
	{
		button->update();
	}
}

void Scene::render(Screen *screen)
{
	background->render(screen);
	for (Button *button : buttons)
	{
		button->render(screen);
	}
}
Scene::~Scene()
{
}
