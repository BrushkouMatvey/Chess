#pragma once
#include "Piece.hpp"
class Knight : public Piece
{
public:
	Knight(bool isWhite, std::string fileName, Tile& tile);
	~Knight();
	bool canMoveTo(Board* board, Tile& tile, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window)override;
	states::Type getTypeOfPiece() override;
};

