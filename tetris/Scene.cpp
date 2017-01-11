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

void Scene::addBoard(Board *board)
{
	this->board = board;
}

void Scene::setBackground(Background *background)
{
	this->background = background;
}

void Scene::addScoresBoard(ScoresBoard *scoresBoard)
{
	this->scoresBoard = scoresBoard;
}

void Scene::update()
{
	for (Button *button : buttons)
	{
		button->update();
	}
	if (board)
		board->update();
}

void Scene::render(Screen *screen)
{
	background->render(screen);
	for (Button *button : buttons)
	{
		button->render(screen);
	}
	if (board)
		board->render(screen);
	if (scoresBoard)
	{
		scoresBoard->render(screen);
	}
}
Scene::~Scene()
{
}
