#include <random>
#include <ctime>
#include <SDL_ttf.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "BoardCell.h"
#include "Shape.h"
#include "Texture.h"
#include "Game.h"


using namespace std;

Board::Board(int x, int y, int xCells, int yCells, int cellWidth)
{
	TTF_Init();
	font = TTF_OpenFont("./fonts/gnuolane.ttf", 100);

	textRect.x = 1050;
	textRect.y = 70;
	textRect.w = 200;
	textRect.h = 100;

	gameOverRect.x = 300;
	gameOverRect.y = 200;
	gameOverRect.w = 500;
	gameOverRect.h = 150;

	text = "Score: " + std::to_string(score);
	message = TTF_RenderText_Blended(font, text.c_str(), textColor);
	messageTexture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), message);

	gameOverMessage = TTF_RenderText_Blended(font, "Game over!", textColor);
	gameOverMessageTexture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), gameOverMessage);

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

	click = Mix_LoadWAV("sounds/click.wav");
	if (click == NULL)
		cout << "Failed to load beat music! SDL_mixer Error: %s\n" << Mix_GetError();
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

void Board::displayScore()
{
	text = "Score: " + std::to_string(score);
	message = TTF_RenderText_Blended(font, text.c_str(), textColor);
	messageTexture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), message);
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
	if (!isGameOver)
	{
		isGameOver = true;
		string goMessage = "Game over! Score: " + to_string(score);
		gameOverMessage = TTF_RenderText_Blended(font, goMessage.c_str(), gameOverColor);
		gameOverMessageTexture = SDL_CreateTextureFromSurface(Game::getScreen()->getRenderer(), gameOverMessage);
		ofstream out;
		out.open("scores.txt", std::ios::app);
		out << score << "\n";
		out.close();
	}
}


Board::Board()
{
}

void Board::handleInput()
{
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
}

void Board::update()
{
	normalSpeed--;
	handleInput();

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
			Mix_PlayChannel(-1, click, 0);
		}
		normalSpeed = 40;
	}
	else if (isGameOver)
	{
		twoSeconds--;
		if (twoSeconds <= 0)
			Game::changeScene("Scores");
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
	displayScore();
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
	if (isGameOver)
	{
		SDL_RenderCopy(screen->getRenderer(), gameOverMessageTexture, NULL, &gameOverRect);
		SDL_RenderCopy(screen->getRenderer(), messageTexture, NULL, &textRect);
	}
	SDL_RenderCopy(screen->getRenderer(), messageTexture, NULL, &textRect);
}

Board::~Board()
{
	Mix_FreeChunk(click);
}

