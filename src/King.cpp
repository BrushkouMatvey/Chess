#include "King.hpp"

King::King(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::KING;
}

King::~King()
{
}

void King::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type King::getTypeOfPiece()
{
	return states::Type::KING;
}

bool King::canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;
	int translationX = location.getValueOfTile().x - this->tile->getValueOfTile().x;
	int translationY = location.getValueOfTile().y - this->tile->getValueOfTile().y;

	// valid move if moving 1 square forward/backwards
	if (abs(translationY) == 1 && translationX == 0)
	{
		validMove = true;
	}

	// valid move if moving 1 square sideways
	else if (abs(translationX) == 1 && translationY == 0)
	{
		validMove = true;
	}

	// valid move if moving 1 square diagonally
	else if (abs(translationX) == 1 && abs(translationY) == 1)
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

