#pragma once
#include "Board.hpp"


class Piece
{
public:
	Piece(bool isWhite, std::string fileName, Tile& tile);
	virtual ~Piece();
	states::Color getColor() const;
	virtual states::Type getTypeOfPiece() = 0;
	virtual void display(sf::RenderWindow &window) = 0;
	virtual bool canMoveTo(Board* board, Tile& tile, sf::RenderWindow& mainWindow) = 0;
	bool isOnSquare() const;
	sf::Sprite& getSprite();
	Tile *tile;
protected:
	states::Color color;
	states::Type type;
	sf::Texture texturePiece;
	sf::Sprite spritePiece;
};



