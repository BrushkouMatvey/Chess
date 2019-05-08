#pragma once
#include "Piece.hpp"
class Queen : public Piece
{
public:
	Queen(bool isWhite, std::string fileName, Tile& tile);
	~Queen();
	bool canMoveTo(Board* board, Tile& tile, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window) override;
	states::Type getTypeOfPiece() override;
};

