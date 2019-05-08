#include "Knight.hpp"

Knight::Knight(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::KNIGHT;
}

Knight::~Knight()
{
}

bool Knight::canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;
	int translationX = location.getValueOfTile().x - this->tile->getValueOfTile().x;
	int translationY = location.getValueOfTile().y - this->tile->getValueOfTile().y;

	if (abs(translationY) == 1 && abs(translationX) == 2)
	{
		validMove = true;
	}

	else if (abs(translationX) == 1 && abs(translationY) == 2)
	{
		validMove = true;
	}

	if (validMove)
	{
		auto temp = this->tile;

		auto tempPiece = location.getOccupier();

		this->tile->moveTo(&location);

		if (b->isCheck(mainWindow, this->getColor()))
			validMove = false;
		if (tempPiece)
			tempPiece->tile = &location;

		this->tile->moveTo(temp);

		location.setOccupier(tempPiece);
	}
	return validMove;
}

void Knight::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type Knight::getTypeOfPiece()
{
	return states::Type::KNIGHT;
}
