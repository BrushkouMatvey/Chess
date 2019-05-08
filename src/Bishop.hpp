#pragma once
#include "Piece.hpp"
class Bishop : public Piece
{
public:
	Bishop(bool isWhite, std::string fileName, Tile& tile);
	~Bishop();
	bool canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window) override;
	states::Type getTypeOfPiece() override;
};

