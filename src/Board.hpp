#pragma once
#include <vector>
#include "Tile.hpp"

class Rook;
class Queen;
class Pawn;
class Bishop;
class King;
class Knight;


class Board
{
public:
	Board(sf::RenderWindow& window);
	~Board();
	Tile* getTile(int i, int j);
	void drawBoard(sf::RenderWindow &window);
	bool isClearVertical(Tile& from, Tile& to);
	bool isClearHorizontal(Tile& from, Tile& to);
	bool isClearDiagonal(Tile& from, Tile& to);
	bool isEndRow(Tile& location);
	Piece* getKingWhite();
	Piece* getKingBlack();
	King* kingW;
	King* kingB;
	bool isCheck(sf::RenderWindow & mainWindow, states::Color who_has_check);
	bool isCheckMate(sf::RenderWindow & mainWindow, states::Color who_has_check);
private:
	Piece *piece;
	static const int DIMENSION = 8;
	Tile * board[8][8];
};
extern Board* b;


