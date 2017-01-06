#pragma once
#include "Entity.h"
#include "Screen.h"
#include "BoardCell.h"
#include "Shape.h"
#include <vector>
#define MAX_WIDTH 50

class Board: public Entity
{
public:
	Board(int x, int y, int xCells, int yCells, int cellWidth);
	Board();
	~Board();
	void update();
	void render(Screen *screen);

private:
	int x, y, w, h, cellWidth, xCells, yCells, currentX, currentY;
	vector<BoardCell*> cells;
	void initDrawBoard();
	void placeShape();
	void clearShape();
	void updateCells();
	int normalSpeed = 10;
	void generateRandomShape();
	Shape *shape;
	void initCells();
	int boardInfo[MAX_WIDTH][MAX_WIDTH];

};

