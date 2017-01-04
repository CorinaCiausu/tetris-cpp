#pragma once
class Screen;

class Entity
{
public:
	Entity();
	~Entity();
private:
	int x, y, w, h;
	virtual void update() = 0;
	virtual void render(Screen* screen) = 0;
};

