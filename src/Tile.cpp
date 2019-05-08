#include "Tile.hpp"
#include "Piece.hpp"

Tile::Tile() : piece(NULL)
{
}

Tile::Tile(sf::Vector2f coordinate, states::Color color) : piece(NULL)
{
	if (color == states::Color::WHITE)
	{
		this->color = states::Color::WHITE;
		textureTileUnselected.loadFromFile("colorBoard/light90.jpg");
		textureTileSelected.loadFromFile("colorBoard/lightMove.jpg");
		textureCheckPossibility.loadFromFile("colorBoard/lightMoveCheck.jpg");
		spriteTile.setTexture(textureTileUnselected);
	}
	else if (color == states::Color::BLACK)
	{
		this->color = states::Color::BLACK;
		textureTileUnselected.loadFromFile("colorBoard/dark90.jpg");
		textureTileSelected.loadFromFile("colorBoard/darkMove.jpg");
		textureCheckPossibility.loadFromFile("colorBoard/darkMoveCheck.jpg");
		spriteTile.setTexture(textureTileUnselected);
	}
	isSelected = false;
	sf::Vector2f sizeOfSprite(spriteTile.getTexture()->getSize().x, spriteTile.getTexture()->getSize().y);

	spriteTile.setPosition(sf::Vector2f(coordinate.x*sizeOfSprite.x, coordinate.y*sizeOfSprite.y));

	this->tileValueOnBoard.x = coordinate.x;
	this->tileValueOnBoard.y = coordinate.y;
	this->coordinateOfTileSprite.x = coordinate.x*sizeOfSprite.x;
	this->coordinateOfTileSprite.y = coordinate.y*sizeOfSprite.y;
	this->coordinateMiddleOfTileSprite.x = coordinate.x*sizeOfSprite.x + sizeOfSprite.x / 2;
	this->coordinateMiddleOfTileSprite.y = coordinate.y*sizeOfSprite.y + sizeOfSprite.y / 2;
}

void Tile::moveTo(Tile * toTile)
{
	Piece* tmp = this->piece;
	Tile *tmpT = this->piece->tile;
	if (this->piece == NULL && toTile->piece == NULL || this->piece == NULL)
	{
		return;
	}
	else if (toTile->piece == NULL)
	{
		this->piece->getSprite().setPosition(toTile->coordinateMiddleOfTileSprite);
	}
	else
	{
		if (this->piece->getColor() == toTile->piece->getColor())
			return;
		this->piece->getSprite().setPosition(toTile->coordinateMiddleOfTileSprite);
		toTile->piece = this->piece;
		toTile->piece->tile = toTile;
		this->piece = NULL;
		return;
	}
	this->piece = toTile->piece;
	toTile->piece = tmp;
	toTile->piece->tile = toTile;
}

Tile::~Tile()
{
	delete piece;
}

void Tile::setOccupier(Piece * piece)
{
	this->piece = piece;
}

bool Tile::occupied() const
{
	return piece;
}

Piece * Tile::occupiedBy()
{
	return piece;
}

bool & Tile::isSelectedByMouse()
{
	return this->isSelected;
}

sf::Vector2i Tile::getValueOfTile() const
{
	return this->tileValueOnBoard;
}

int Tile::getValueOfTileX() const
{
	return this->tileValueOnBoard.x;
}

int Tile::getValueOfTileY() const
{
	return this->tileValueOnBoard.y;
}

sf::Vector2f Tile::getMiddleCoordinateOfSpriteMid() const
{
	return this->coordinateMiddleOfTileSprite;
}

void Tile::setTextureSelected()
{
	this->spriteTile.setTexture(textureTileSelected);
}

void Tile::setTexture()
{
	this->spriteTile.setTexture(textureTileUnselected);
}

void Tile::setTextureCheckPossibility()
{
	this->spriteTile.setTexture(textureCheckPossibility);
}

sf::Sprite& Tile::getSprite()
{
	return this->spriteTile;
}

int Tile::getMiddleCoordinateOfSpriteMidX() const
{
	return this->coordinateMiddleOfTileSprite.x;
}

int Tile::getMiddleCoordinateOfSpriteMidY() const
{
	return this->coordinateMiddleOfTileSprite.y;
}

int Tile::getXOfTileSprite() const
{
	return this->coordinateOfTileSprite.x;
}

int Tile::getYOfTileSprite() const
{
	return this->coordinateOfTileSprite.y;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->spriteTile, states);
}

states::Color Tile::getColor()
{
	return this->color;
}

Piece* Tile::getOccupier() const
{
	return this->piece;
}