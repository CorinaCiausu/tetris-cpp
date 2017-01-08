#pragma once
#include "Entity.h"
#include "Screen.h"
#include "Texture.h"
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
	int x, y, w, h, cellWidth, xCells, yCells, currentX, currentY, currentShapeNumber, nextShapeNumber;
	bool isGameOver = false;
	vector<BoardCell*> cells;
	SDL_Rect nextShapeRect;
	Texture *nextShapeTexture;
	void setNextShapeTexture();
	void initDrawBoard();
	void placeShape();
	void clearShape(int boardInfo[MAX_WIDTH][MAX_WIDTH]);
	void shallowClearShape(int shallowBoard[MAX_WIDTH][MAX_WIDTH]);
	void updateCells();
	void gameOver();
	bool isMovePossible(int nextX, int nextY, int nextShape[4][4]);
	int normalSpeed = 30;
	void generateRandomShape();
	Shape *shape;
	void initCells();
	int boardInfo[MAX_WIDTH][MAX_WIDTH];

};

