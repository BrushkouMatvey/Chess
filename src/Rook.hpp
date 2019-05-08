#pragma once
#include "Piece.hpp"
class Rook : public Piece
{
public:
	Rook(bool isWhite, std::string fileName, Tile& tile);
	~Rook();
	bool canMoveTo(Board* board, Tile& tile, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window) override;
	states::Type getTypeOfPiece() override;
};

