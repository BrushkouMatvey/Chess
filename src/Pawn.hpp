#pragma once
#include "Piece.hpp"
class Pawn : public Piece
{
public:
	Pawn(bool isWhite, std::string fileName, Tile& tile);
	~Pawn();
	bool canMoveTo(Board* board, Tile& tile, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window) override;
	states::Type getTypeOfPiece() override;
	bool isWhite();
private:
	bool firstStep;
};

