#include "Board.h"
#include "BoardCell.h"
#include <iostream>
#include "Shape.h"
#include "Texture.h"
#include <random>
#include <ctime>

using namespace std;

Board::Board(int x, int y, int xCells, int yCells, int cellWidth)
{
	srand(time(0));
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
			if(shape->info[i][j])
			boardInfo[currentX + j][currentY + i] = shape->info[i][j];
}

void Board::clearShape(int boardInfo[50][50])
{
	for(int i=0;i<4;i++)
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
			if (nextY + i >= 0)
				if (nextX + j > xCells || nextY + i > yCells || nextShape[i][j] && shallowBoard[nextX + j][nextY + i])
				{
					if (nextShape[i][j] && shallowBoard[nextX + j][nextY + i] && nextY + i == 0)
						gameOver();
					return false;
				}
	return true;
}

void Board::updateCells()
{
	for(int i=0;i<yCells;i++)
		for(int j=0;j<xCells;j++)
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
	delete shape;
	shape = new Shape(shapeLetter.c_str());
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
	//add control
	if (normalSpeed <= 0&&!isGameOver)
	{
		if(isMovePossible(currentX, currentY+1,shape->info))
		{
			clearShape(this->boardInfo);
			currentY++;
			placeShape();
			updateCells();
		}
		else
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (shape->info[i][j] && currentY + i < 0)
						gameOver();
			if (currentY != 0)
			{
				currentY = -4;
				generateRandomShape();
			}
		}
		normalSpeed = 10;
	}
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
