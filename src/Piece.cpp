#include "Piece.hpp"
#include "Tile.hpp"

Piece::Piece(bool isWhite, std::string fileName, Tile& tile)
{
	if (isWhite)
		color = states::Color::WHITE;
	else
		color = states::Color::BLACK;

	texturePiece.loadFromFile(fileName);
	spritePiece.setTexture(texturePiece);
	spritePiece.setOrigin(texturePiece.getSize().x / 2, texturePiece.getSize().y / 2);
	spritePiece.setPosition(tile.getMiddleCoordinateOfSpriteMid());
	this->tile = &tile;
}

Piece::~Piece()
{
	delete tile;
}

states::Color Piece::getColor() const
{
	return this->color;
}

bool Piece::isOnSquare() const
{
	return this->tile;
}

sf::Sprite & Piece::getSprite()
{
	return this->spritePiece;
}



