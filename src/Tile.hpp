#pragma once
#include <SFML/Graphics.hpp>
#include "States.hpp"
#include <string>

class Piece;
class Tile : public sf::Drawable
{
public:
	Piece* getOccupier() const;
	Tile();
	Tile(sf::Vector2f coordinate, states::Color color);
	~Tile();
	void moveTo(Tile * toTile);
	void setOccupier(Piece* piece);
	bool occupied() const;
	Piece *occupiedBy();
	bool& isSelectedByMouse();
	sf::Vector2i getValueOfTile() const;
	int getValueOfTileX() const;
	int getValueOfTileY() const;
	sf::Vector2f getMiddleCoordinateOfSpriteMid() const;
	void setTextureSelected();
	void setTexture();
	void setTextureCheckPossibility();
	sf::Sprite& getSprite();
	int getMiddleCoordinateOfSpriteMidX() const;
	int getMiddleCoordinateOfSpriteMidY() const;
	int getXOfTileSprite() const;
	int getYOfTileSprite() const;
	states::Color getColor();
private:
	Piece *piece;
	states::Color color;
	bool isSelected;
	sf::Texture textureTileUnselected;
	sf::Texture textureTileSelected;
	sf::Texture textureTilePoint;
	sf::Texture textureCheckPossibility;
	sf::Sprite spriteTile;
	sf::Vector2i tileValueOnBoard;
	sf::Vector2i coordinateOfTileSprite;
	sf::Vector2f coordinateMiddleOfTileSprite;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

