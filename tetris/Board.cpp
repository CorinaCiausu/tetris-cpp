#include "Board.h"
#include "BoardCell.h"
#include <iostream>
#include "Shape.h"
#include <random>

Board::Board(int x, int y, int xCells, int yCells, int cellWidth)
{
	this->x = x;
	this->y = y;
	this->xCells = xCells;
	this->yCells = yCells;
	this->cellWidth = cellWidth;
	this->currentX = 4;
	this->currentY = 0;
	initCells();
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
			boardInfo[currentX + j][currentY + i] = shape->info[i][j];
}

void Board::clearShape()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (boardInfo[currentX + j][currentY + i] == shape->info[i][j])
				boardInfo[currentX + j][currentY + i] = 0;
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
	int shapeNumber = rand() % 7;
	char shapes[] = "ILJOSTZ";
	string shapeLetter = { shapes[shapeNumber] };
	delete shape;
	shape = new Shape(shapeLetter.c_str());
}
Board::Board()
{
}

void Board::update()
{
	normalSpeed--;
	//add control
	if (normalSpeed <= 0)
	{
		//check if it can move
		if (currentY < yCells - 4)
		{
			clearShape();
			currentY++;
			placeShape();
			updateCells();
		}
		else
		{
			currentY = -4;
			generateRandomShape();
		}
		normalSpeed = 10;
	}
}

void Board::render(Screen *screen)
{
	for (BoardCell *boardCell : cells)
		boardCell->render(screen);
	//shape->render(screen);
}

Board::~Board()
{
}
