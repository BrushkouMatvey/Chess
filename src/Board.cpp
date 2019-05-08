#include "Board.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

extern Board* b;

Board::Board(sf::RenderWindow& window)
{
	b = this;
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			if ((i + j) % 2 == 0)
			{
				board[i][j] = new Tile(sf::Vector2f(j, i), states::Color::WHITE);
			}
			else
			{
				board[i][j] = new Tile(sf::Vector2f(j, i), states::Color::BLACK);
			}
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					if (j == 0 || j == 7)
					{
						piece = new Rook(false, "piecesPNG/RookBlack.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 1 || j == 6)
					{
						piece = new Knight(false, "piecesPNG/KnightBlack.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 2 || j == 5)
					{
						piece = new Bishop(false, "piecesPNG/BishopBlack.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 3)
					{
						piece = new Queen(false, "piecesPNG/QueenBlack.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 4)
					{
						piece = new King(false, "piecesPNG/KingBlack.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
				}
				else
				{
					piece = new Pawn(false, "piecesPNG/PawnBlack.png", *board[i][j]);
					board[i][j]->setOccupier(piece);
				}
			}
			if (i == 6 || i == 7)
			{
				if (i == 7)
				{
					if (j == 0 || j == 7)
					{
						piece = new Rook(true, "piecesPNG/RookWhite.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 1 || j == 6)
					{
						piece = new Knight(true, "piecesPNG/KnightWhite.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 2 || j == 5)
					{
						piece = new Bishop(true, "piecesPNG/BishopWhite.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 3)
					{
						piece = new Queen(true, "piecesPNG/QueenWhite.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
					if (j == 4)
					{
						piece = new King(true, "piecesPNG/KingWhite.png", *board[i][j]);
						board[i][j]->setOccupier(piece);
					}
				}
				else
				{
					piece = new Pawn(true, "piecesPNG/PawnWhite.png", *board[i][j]);
					board[i][j]->setOccupier(piece);
				}
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			delete[] board[i][j];
		}
	}
}

bool Board::isClearVertical(Tile& from, Tile& to)
{
	Tile* start = NULL;
	Tile* end = NULL;
	bool valid = true;

	if (from.getValueOfTile().y <= to.getValueOfTile().y)
	{
		start = &from;
		end = &to;
	}
	else
	{
		start = &to;
		end = &from;
	}

	// check that there is no horizontal movement
	if (start->getValueOfTile().x != end->getValueOfTile().x)
	{
		valid = false;
	}
	else
	{
		// iterate over vertical interval between squares
		for (int i = start->getValueOfTile().y + 1; i < end->getValueOfTile().y; i++)
		{
			// if a square is occupied, the vertical is not clear
			getTile(start->getValueOfTile().x, i);
			if (getTile(start->getValueOfTile().x, i)->occupied())
			{
				valid = false;
				return valid;
			}
		}
	}
	return valid;
}

bool Board::isClearHorizontal(Tile& from, Tile& to)
{
	Tile* start = NULL;
	Tile* end = NULL;
	bool valid = true;

	if (from.getValueOfTile().x <= to.getValueOfTile().x)
	{
		start = &from;
		end = &to;
	}
	else
	{
		start = &to;
		end = &from;
	}

	// check that there is no vertical movement
	if (start->getValueOfTile().y != end->getValueOfTile().y)
	{
		valid = false;
	}
	else
	{
		// iterate over horizontal interval between squares
		for (int i = start->getValueOfTile().x + 1; i < end->getValueOfTile().x; i++)
		{
			// if a square is occupied, the vertical is not clear
			if (getTile(i, start->getValueOfTile().y)->occupied())
			{
				valid = false;
			}
		}
	}
	return valid;
}

bool Board::isClearDiagonal(Tile& from, Tile& to)
{
	bool valid = true;
	int translationX = to.getValueOfTile().x - from.getValueOfTile().x;
	int translationY = to.getValueOfTile().y - from.getValueOfTile().y;
	int xDir = 1;
	int yDir = 1;

	if (translationX < 0)
	{
		xDir = -1;
	}

	if (translationY < 0)
	{
		yDir = -1;
	}

	// not a diagonal if absolute value of x and y translations don't match
	if (abs(translationX) != abs(translationY))
	{
		valid = false;
	}
	else
	{
		// iterate over diagonal interval between squares
		for (int i = 1; i < abs(translationX); i++)
		{
			// if a square is occupied, the diagonal is not clear
			if (getTile(from.getValueOfTile().x + (i * xDir), from.getValueOfTile().y + (i * yDir))->occupied())
			{
				valid = false;
			}
		}
	}
	return valid;
}

bool Board::isEndRow(Tile & location)
{
	return (location.getValueOfTile().y == 0 || location.getValueOfTile().y == (DIMENSION - 1));
}

Tile* Board::getTile(int i, int j)
{
	return board[j][i];
}

void Board::drawBoard(sf::RenderWindow &window)
{
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			window.draw(*board[i][j]);
			if (board[i][j]->occupied())
			{
				Piece *piece1 = board[i][j]->occupiedBy();
				piece1->display(window);
			}
		}
	}
}

Piece* Board::getKingWhite()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (getTile(i,j)->occupied() && 
				getTile(i, j)->occupiedBy()->getTypeOfPiece() == states::Type::KING &&
				getTile(i, j)->occupiedBy()->getColor() == states::WHITE)
				return getTile(i, j)->occupiedBy();
		}
	}
}

Piece* Board::getKingBlack()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (getTile(i, j)->occupiedBy() &&
				getTile(i, j)->occupiedBy()->getTypeOfPiece() == states::Type::KING &&
				getTile(i, j)->occupiedBy()->getColor() == states::BLACK)
				return getTile(i, j)->occupiedBy();
		}
	}
}

bool Board::isCheck(sf::RenderWindow & mainWindow, states::Color who_has_check)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (who_has_check == states::Color::WHITE &&
				this->getTile(i, j)->occupied() &&
				this->getTile(i, j)->occupiedBy()->getColor() == states::Color::BLACK &&
				this->getTile(i, j)->occupiedBy()->canMoveTo(this,
					*this->getKingWhite()->tile, mainWindow))
				return true;

			if (who_has_check == states::Color::BLACK &&
				this->getTile(i, j)->occupied() &&
				this->getTile(i, j)->occupiedBy()->getColor() == states::Color::WHITE &&
				this->getTile(i, j)->occupiedBy()->canMoveTo(this,
					*this->getKingBlack()->tile, mainWindow))
				return true;
		}
	}
	return false;
}

bool Board::isCheckMate(sf::RenderWindow & mainWindow, states::Color who_has_check)
{
	bool validMate = false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (who_has_check == states::Color::BLACK &&
				this->getTile(i, j)->occupied() &&
				this->getTile(i, j)->occupiedBy()->getColor() == states::Color::BLACK)
			{
				for (int k = 0; k < 8; k++)
					for (int m = 0; m < 8; m++)
					{
						if (this->getTile(i, j)->occupiedBy()->canMoveTo(this, *this->getTile(m, k), mainWindow) && i != k && j != m)
							return false;
					}
							
			}

			if (who_has_check == states::Color::WHITE &&
				this->getTile(i, j)->occupied() &&
				this->getTile(i, j)->occupiedBy()->getColor() == states::Color::WHITE)
			{
					for (int k = 7; k >=0; k--)
						for (int m = 7; m >=0; m--)
						{

							if (this->getTile(i, j)->occupiedBy()->canMoveTo(this, *this->getTile(m, k), mainWindow) && i != k && j != m)
								return false;
						}
			}
		}
	return true;
}