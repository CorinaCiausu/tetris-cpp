#pragma once
#include "Entity.h"
#include "Screen.h"
#include "Texture.h"
#include "BoardCell.h"
#include "Shape.h"
#include <vector>
#include <SDL_mixer.h>
#define MAX_WIDTH 50

class Board : public Entity
{
public:
	Board(int x, int y, int xCells, int yCells, int cellWidth);
	Board();
	~Board();
	void update();
	void render(Screen *screen);

private:
	int x, y, w, h, cellWidth, xCells, yCells, currentX, currentY, currentShapeNumber, nextShapeNumber, score = 0;
	int twoSeconds = 120;
	bool isGameOver = false, left = false, right = false, up = false, down = false;
	// add + -
	bool plusSpeedUp = false, minusSpeedDown = false, isNormalSpeed = true;
	int standardSpeed = 40;
	// end add
	bool moveLeft = false, moveRight = false, rotateShape = false, speedUp = false;
	Mix_Chunk *click = NULL;
	vector<BoardCell*> cells;
	SDL_Rect nextShapeRect;
	Texture *nextShapeTexture;
	void hollowRotate(int mat[4][4], int res[4][4]);
	void clearLines();
	void clearLine(int line);
	void setNextShapeTexture();
	void initDrawBoard();
	void placeShape();
	void clearShape(int boardInfo[MAX_WIDTH][MAX_WIDTH]);
	void shallowClearShape(int shallowBoard[MAX_WIDTH][MAX_WIDTH]);
	void displayScore();
	void handleInput();

	TTF_Font *font = NULL;
	SDL_Surface *message = NULL;
	SDL_Rect textRect;
	SDL_Texture *messageTexture = NULL;
	SDL_Color textColor = { 0, 0, 100 };
	string text;

	SDL_Surface *gameOverMessage = NULL;
	SDL_Rect gameOverRect;
	SDL_Texture *gameOverMessageTexture = NULL;
	SDL_Color gameOverColor = { 255, 160, 160 };

	void updateCells();
	void gameOver();
	bool isMovePossible(int nextX, int nextY, int nextShape[4][4]);
	int normalSpeed = 30;
	void generateRandomShape();
	Shape *shape;
	void initCells();
	int boardInfo[MAX_WIDTH][MAX_WIDTH];

};


