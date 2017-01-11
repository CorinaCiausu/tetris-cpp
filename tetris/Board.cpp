#include "Board.h"
#include "BoardCell.h"
#include <iostream>
#include "Shape.h"
#include "Texture.h"
#include <SDL.h>
#include "Game.h"
#include <random>
#include <ctime>

using namespace std;

Board::Board(int x, int y, int xCells, int yCells, int cellWidth)
{
	srand(time(0));
	shape = new Shape("L");
	this->x = x;
	this->y = y;
	this->xCells = xCells;
	this->yCells = yCells;
	this->cellWidth = cellWidth;
	this->currentX = 4;
	this->currentY = 0;
	initCells();
	nextShapeRect.x = 980;
	nextShapeRect.y = 345;
	nextShapeRect.w = 195;
	nextShapeRect.h = 200;
	nextShapeTexture = NULL;
	nextShapeNumber = rand() % 7;
	generateRandomShape();
	initDrawBoard();
	placeShape();
	updateCells();
}

void Board::initCells()
{
	for (int i = 0; i < yCells; i++)
		for (int j = 0; j < xCells; j++)
			boardInfo[j][i] = 0;
	currentX = 3;
	currentY = -4;
}

void Board::placeShape()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (shape->info[i][j] && currentX + j >= 0 && currentX + j < xCells && currentY + i >= 0)
				boardInfo[currentX + j][currentY + i] = shape->info[i][j];
}

void Board::clearShape(int boardInfo[50][50])
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (shape->info[i][j] != 0)
				if (currentY + i >= 0 && currentX + j >= 0)
					boardInfo[currentX + j][currentY + i] = 0;
		}
	}
}

void Board::shallowClearShape(int shallowBoard[50][50])
{
	for (int j = 0; j < xCells; j++)
		for (int i = 0; i < yCells; i++)
			shallowBoard[j][i] = boardInfo[j][i];
	clearShape(shallowBoard);
}

void Board::setNextShapeTexture()
{
	switch (nextShapeNumber)
	{
	case 0:
		nextShapeTexture = Texture::I_DisplayTexture;
		break;
	case 1:
		nextShapeTexture = Texture::L_DisplayTexture;
		break;
	case 2:
		nextShapeTexture = Texture::J_DisplayTexture;
		break;
	case 3:
		nextShapeTexture = Texture::O_DisplayTexture;
		break;
	case 4:
		nextShapeTexture = Texture::S_DisplayTexture;
		break;
	case 5:
		nextShapeTexture = Texture::T_DisplayTexture;
		break;
	case 6:
		nextShapeTexture = Texture::Z_DisplayTexture;
		break;
	default:
		break;
	}
}
bool Board::isMovePossible(int nextX, int nextY, int nextShape[4][4])
{
	int shallowBoard[50][50];
	shallowClearShape(shallowBoard);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (nextShape[i][j])
			{
				if (nextX + j < 0 || nextX + j > xCells - 1) // sides of board
				{
					cout << nextX << "X\n";
					return false;
				}

				if (nextY + i > yCells - 1)
				{
					cout << nextY + i << "Y\n";
					return false; // bottom of board
				}

				if (nextY + i >= 0 && shallowBoard[nextX + j][nextY + i])
				{
					cout << nextX + j << " " << nextY + i << "\n";
					return false;
				}
			}

	return true;
}

void Board::updateCells()
{
	for (int i = 0; i<yCells; i++)
		for (int j = 0; j<xCells; j++)
			switch (boardInfo[j][i])
			{
			case 1:
				cells[j + i * xCells]->setTexture(Texture::I_Texture);
				break;
			case 2:
				cells[j + i * xCells]->setTexture(Texture::L_Texture);
				break;
			case 3:
				cells[j + i * xCells]->setTexture(Texture::J_Texture);
				break;
			case 4:
				cells[j + i * xCells]->setTexture(Texture::O_Texture);
				break;
			case 5:
				cells[j + i * xCells]->setTexture(Texture::S_Texture);
				break;
			case 6:
				cells[j + i * xCells]->setTexture(Texture::T_Texture);
				break;
			case 7:
				cells[j + i * xCells]->setTexture(Texture::Z_Texture);
				break;
			default:
				cells[j + i*xCells]->setTexture(Texture::emptyCell);
				break;
			}
}

void Board::initDrawBoard()
{
	for (int i = 0; i < yCells; i++)
		for (int j = 0; j < xCells; j++)
			cells.push_back(new BoardCell(x + j*cellWidth, y + i * cellWidth, cellWidth, Texture::emptyCell));
}

void Board::generateRandomShape()
{
	currentShapeNumber = nextShapeNumber;
	nextShapeNumber = rand() % 7;
	char shapes[] = "ILJOSTZ";
	string shapeLetter = { shapes[currentShapeNumber] };
	shape->setShape(shapeLetter.c_str());
	setNextShapeTexture();
}

void Board::gameOver()
{
	isGameOver = true;
}
Board::Board()
{
}

void Board::update()
{
	normalSpeed--;
	if (Game::getMainEvent().type == SDL_KEYDOWN)
	{
		SDL_Keycode keyPressed = Game::getMainEvent().key.keysym.sym;
		switch (keyPressed)
		{
		case SDLK_RIGHT:
			moveRight = !right;
			right = true;
			break;
		case SDLK_LEFT:
			moveLeft = !left;
			left = true;
			break;
		case SDLK_DOWN:
			down = true;
			break;
		case SDLK_UP:
			rotateShape = !up;
			up = true;
			break;
		}
		if (moveRight && isMovePossible(currentX + 1, currentY, shape->info))
		{
			clearShape(this->boardInfo);
			currentX++;
			placeShape();
			updateCells();
		}
		else if (moveLeft && isMovePossible(currentX - 1, currentY, shape->info))
		{
			clearShape(this->boardInfo);
			currentX--;
			placeShape();
			updateCells();
		}
		if (down)
			normalSpeed -= 6;
		if (rotateShape)
		{
			int rotatedShape[4][4];
			hollowRotate(shape->info, rotatedShape);
			if (isMovePossible(currentX, currentY, rotatedShape))
			{
				clearShape(this->boardInfo);
				shape->rotateShape();
				placeShape();
				updateCells();

			}
		}
	}
	else
		if (Game::getMainEvent().type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = Game::getMainEvent().key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_RIGHT:
				right = false;
				moveRight = false;
				break;
			case SDLK_LEFT:
				left = false;
				moveLeft = false;
				break;
			case SDLK_DOWN:
				down = false;
				speedUp = false;
				break;
			case SDLK_UP:
				up = false;
				rotateShape = false;
				break;
			}
		}

	if (normalSpeed <= 0 && !isGameOver)
	{

		if (isMovePossible(currentX, currentY + 1, shape->info))
		{
			clearShape(this->boardInfo);
			currentY++;
			placeShape();
			updateCells();
		}
		else
		{
			clearLines();
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (shape->info[i][j] && currentY + i < 0)
						gameOver();
			currentY = -4;
			currentX = 3;
			generateRandomShape();
		}
		normalSpeed = 40;
	}
}

void Board::clearLines()
{
	int linesCleared = 0;
	for (int i = 0; i < yCells; i++)
	{
		bool isFull = true;
		for (int j = 0; j < xCells; j++)
			if (boardInfo[j][i] == 0)
				isFull = false;

		if (isFull)
		{
			linesCleared++;
			clearLine(i);
			i--;
		}

	}
	if (linesCleared == 1)
		score += 100;
	else if (linesCleared == 2)
		score += 250;
	else if (linesCleared == 3)
		score += 400;
	else if (linesCleared == 4)
		score += 600;
	cout << "score: " << score << "\n";
	updateCells();
}

void Board::clearLine(int line)
{
	for (int i = line; i > 0; i--)
		for (int j = 0; j < xCells; j++)
			boardInfo[j][i] = boardInfo[j][i - 1];
}

void Board::hollowRotate(int mat[4][4], int res[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res[i][j] = mat[4 - j - 1][i];
			cout << res[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Board::render(Screen *screen)
{
	for (BoardCell *boardCell : cells)
		boardCell->render(screen);
	nextShapeTexture->render(screen, &nextShapeRect);
}

Board::~Board()
{
}

