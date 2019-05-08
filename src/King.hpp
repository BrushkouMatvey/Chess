#pragma once
#include "Piece.hpp"
class King : public Piece
{
public:
	King(bool isWhite, std::string fileName, Tile& tile);
	~King();	
	bool canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow) override;
	void display(sf::RenderWindow &window) override;
	states::Type getTypeOfPiece() override;
};

